#include <fukiyomi/core/reading_session.h>
#include <utility>


namespace fukiyomi::core
{
    ReadingSession::ReadingSession(std::unique_ptr<IPageSource> source) : currentIndex_(0), 
                                        source_(std::move(source))
    {
    }

    bool ReadingSession::next()
    {
        if (currentIndex_ + 1 >= source_->pageCount())
        {
            return false;
        }
        ++currentIndex_;
        return true;
    }

    bool ReadingSession::previous()
    {
        if (currentIndex_ == 0)
        {
            return false;
        }
        --currentIndex_;
        return true;
    }

    std::expected<PageBytes, PageError> ReadingSession::currentPage()
    {
        return source_->readPage(currentIndex_);
    }

    std::size_t ReadingSession::currentIndex() const
    {
        return currentIndex_;
    }

    std::size_t ReadingSession::pageCount() const
    {
        return source_->pageCount();
    }
}