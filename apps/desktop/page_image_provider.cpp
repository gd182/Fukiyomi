#include "page_image_provider.h"
#include "fukiyomi/core/page_error.h"

namespace fukiyomi::desktop
{
    PageImageProvider::PageImageProvider(ReaderController* controller)
    : QQuickImageProvider(QQuickImageProvider::Image)
    , controller_(controller)
    {
    }

    QImage PageImageProvider::requestImage(const QString& id, QSize* size, const QSize& requestedSize)
    {
        Q_UNUSED(id);
        Q_UNUSED(requestedSize);

        auto page = controller_->currentPage();
        if (!page)
        {
            qWarning().noquote() << core::toString(page.error());
            return {};
        }
        const auto& bytes = *page;
        QImage image;
        if (!image.loadFromData(bytes.data(), bytes.size()))
        {
            qWarning().noquote() << "Failed to load image from data";
            return {};
        }
        if (size)
        {
            *size = image.size();
        }
        return image;
    }
}