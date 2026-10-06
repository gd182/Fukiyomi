#include "reader_controller.h"

namespace fukiyomi::desktop
{
    ReaderController::ReaderController(core::ReadingSession session, QObject* parent)
    : QObject(parent)
    , session_(std::move(session))
    {
    }

    int ReaderController::currentIndex() const
    {
        return static_cast<int>(session_.currentIndex());
    }

    int ReaderController::pageCount() const
    {
        return static_cast<int>(session_.pageCount());
    }

    std::expected<core::PageBytes, core::PageError> ReaderController::currentPage()
    {
        return session_.currentPage();
    }

    void ReaderController::next()
    {
        if (session_.next())
        {
            emit currentIndexChanged();
        }
    }

    void ReaderController::previous()
    {
        if (session_.previous())
        {
            emit currentIndexChanged();
        }
    }
}