#pragma once

#include <fukiyomi/core/page_source.h>

#include <memory>

namespace fukiyomi::core
{
    /// Keeps track of the current page in a page source
    /// Starts at the first page and never moves past the first or the last one
    class ReadingSession
    {
    public:
        /// @param source Source of pages. It cannot be nullptr. The session takes ownership of the source
        explicit ReadingSession(std::unique_ptr<IPageSource> source);
        
        /// Moves to the next page.
        ///
        /// Stays on the last page instead of wrapping around to the first one.
        /// With an empty source there is no next page, so it always returns false.
        ///
        /// @return true if the current page changed, false if already at the end
        bool next();

        /// Moves to the previous page.
        ///
        /// Stays on the first page instead of wrapping around to the last one.
        /// With an empty source there is no previous page, so it always returns false.
        ///
        /// @return true if the current page changed, false if already at the first page
        bool previous();

        /// Reads the current page.
        ///
        /// Not const because some sources change their internal state while
        /// reading (for example, an archive moves its read position)
        ///
        /// @return The encoded bytes of the page (PNG, JPEG, ...) on success
        ///         PageError::IndexOutOfRange if the source is empty
        ///         PageError::ReadFailed if the page could not be read
        std::expected<PageBytes, PageError>  currentPage();

        /// Returns the zero-based index of the current page.
        /// Returns 0 if the source is empty, which is not a valid page index.
        std::size_t currentIndex() const;

        /// Returns the number of pages. Valid indices are 0 to pageCount() - 1
        std::size_t pageCount() const;
    private:
        std::size_t currentIndex_;
        std::unique_ptr<IPageSource> source_;
    };
}