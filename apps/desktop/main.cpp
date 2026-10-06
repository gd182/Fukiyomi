#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "reader_controller.h"
#include "page_image_provider.h"

#include <fukiyomi/core/reading_session.h>
#include <fukiyomi/sources/folder_page_source.h>

#include <filesystem>

int main(int argc, char *argv[])
{
    namespace fd = fukiyomi::desktop;
    namespace fc = fukiyomi::core;
    namespace fsrc = fukiyomi::sources;

    QGuiApplication app(argc, argv);
    const QStringList args = app.arguments();
    if (args.size() < 2) {
        qCritical().noquote() << "Usage:" << args.at(0) << "<folder>";
        return 1;
    }
    std::filesystem::path folder(args.at(1).toStdU16String());
    auto source = fukiyomi::sources::FolderPageSource::open(folder);
    if (!source)
    {
        qCritical().noquote() << "Error:" << fc::toString(source.error());
        return 1;
    }

    fc::ReadingSession session(
        std::make_unique<fsrc::FolderPageSource>(std::move(*source)));
    fd::ReaderController controller(std::move(session));
    QQmlApplicationEngine engine;
    
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() {
            QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection
    );

    engine.setInitialProperties({{"controller", QVariant::fromValue(&controller)}});
    engine.addImageProvider("pages", new fd::PageImageProvider(&controller));
    engine.loadFromModule("FukiyomiApp", "Main");

    return app.exec();
}