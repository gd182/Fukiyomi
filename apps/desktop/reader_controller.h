#pragma once

#include <fukiyomi/core/reading_session.h>

#include <QObject>
#include <QtQml/qqmlregistration.h>

namespace fukiyomi::desktop
{
    class ReaderController : public QObject
    {
        Q_OBJECT
        QML_ELEMENT
        QML_UNCREATABLE("Created in C++")

        Q_PROPERTY(int currentIndex READ currentIndex NOTIFY currentIndexChanged)
        Q_PROPERTY(int pageCount READ pageCount CONSTANT)
    public:
        explicit ReaderController(core::ReadingSession session, QObject* parent = nullptr);

        int currentIndex() const;
        int pageCount() const;
        std::expected<core::PageBytes, core::PageError>  currentPage();
        Q_INVOKABLE void next();
        Q_INVOKABLE void previous();
    signals:
        void currentIndexChanged();
    private:
        core::ReadingSession session_;
    };
}