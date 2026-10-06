#pragma once

#include "reader_controller.h"

#include <QQuickImageProvider>

namespace fukiyomi::desktop
{
    class PageImageProvider : public QQuickImageProvider
    {
    public:
        explicit PageImageProvider(ReaderController* controller);
        QImage requestImage(const QString& id, QSize* size, const QSize& requestedSize) override;
    private:
        ReaderController* controller_;
    };  
}