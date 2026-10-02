#pragma once 

#include <cstddef>
#include <expected>
#include <vector>
#include <cstdint>

#include <fukiyomi/core/page_error.h>

namespace fukiyomi::core
{
    /// Encoded image file contents (PNG, JPEG, etc.), not decoded pixels
    using PageBytes = std::vector<std::uint8_t>;

    /// A source of manga pages, regardless of where they are stored
    /// (a folder, an archive, memory)
    class IPageSource
    {
    public:
        virtual ~IPageSource() = default;

        /// Returns the number of pages. Valid indices are 0 to pageCount() - 1
        virtual std::size_t pageCount() const = 0;

        /// Reads the page at the given index.
        ///
        /// Not const because some sources change their internal state while
        /// reading (for example, an archive moves its read position)
        ///
        /// @param pageIndex Index of the page, from 0 to pageCount() - 1
        /// @return The encoded bytes of the page (PNG, JPEG, ...) on success
        ///         PageError::IndexOutOfRange if pageIndex >= pageCount()
        ///         PageError::ReadFailed if the page could not be read
        virtual std::expected<PageBytes, PageError> readPage(std::size_t pageIndex) = 0;
    };
}