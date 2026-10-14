#pragma once

#include <expected>
#include <filesystem>
#include <vector>

#include <fukiyomi/core/page_error.h>
#include <fukiyomi/core/page_source.h>

namespace fukiyomi::sources
{
    /// Reads image files from a folder
    class FolderPageSource final : public core::IPageSource
    {
    public:
        /// Opens folder with pages and stores their paths, sorted by name
        /// @return source of pages on success
        ///         PageError::SourceNotFound if the path does not exist,
        ///         it is not a folder, or the folder could not be read
        static std::expected<FolderPageSource, core::PageError> open(const std::filesystem::path& folder);
        std::size_t pageCount() const override;
        std::expected<core::PageBytes, core::PageError> readPage(std::size_t pageIndex) override;
    private:
        /// The object is created only via open, so it is always in a working state
        explicit FolderPageSource(std::vector<std::filesystem::path> paths);

        std::vector<std::filesystem::path> paths_;
    };
}