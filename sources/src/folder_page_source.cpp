#include <fukiyomi/sources/folder_page_source.h>

#include <filesystem>
#include <expected>
#include <system_error>
#include <utility>
#include <algorithm>
#include <cctype>
#include <fstream>

namespace fukiyomi::sources
{
    namespace
    {
        bool isImageFile(const std::filesystem::path& path)
        {
            auto ext  = path.extension().string();
            std::ranges::transform(
                ext,
                ext.begin(),
                [](unsigned char c) {  // std::tolower with a negative char causes undefined behavior
                    return std::tolower(c);
                }
            );
            return (ext == ".jpg" || ext == ".png" || ext == ".jpeg" || ext == ".webp");
        }   
    }

    std::expected<FolderPageSource, core::PageError> FolderPageSource::open(const std::filesystem::path& folder)
    {
        namespace fs = std::filesystem;
        std::error_code ec;
        if (!fs::is_directory(folder, ec))
        {
            return std::unexpected(core::PageError::SourceNotFound);
        }
        
        std::vector<fs::path> files;
        // Use increment(ec) instead of range-for to avoid exceptions
        for (auto it = fs::directory_iterator(folder, ec); !ec && it != fs::directory_iterator(); it.increment(ec))
        {
            // To avoid erasing the value of ec, 
            // to prevent an error in a single file from breaking the entire opening process
            std::error_code fileEc;
            if (it->is_regular_file(fileEc))
            {
                if (isImageFile(it->path()))
                {
                    files.push_back(it->path());
                }
            }
        }
        if (ec)
        {
            return std::unexpected(core::PageError::SourceNotFound);
        }

        // TODO: natural sort (page2 before page10)
        std::ranges::sort(files);
        
        return FolderPageSource(std::move(files));
    }

    std::size_t FolderPageSource::pageCount() const
    {
        return paths_.size();
    }

    std::expected<core::PageBytes, core::PageError> FolderPageSource::readPage(const std::size_t pageIndex)
    {
        if (pageIndex >= paths_.size())
        {
            return std::unexpected(core::PageError::IndexOutOfRange);
        }

        std::ifstream file(paths_[pageIndex], std::ios::binary | std::ios::ate);
        if (!file)
        {
            return std::unexpected(core::PageError::ReadFailed);
        }

        const auto size = file.tellg();
        if (size < 0)
        {
            return std::unexpected(core::PageError::ReadFailed); 
        }

        core::PageBytes bytes(static_cast<std::size_t>(size));

        file.seekg(0, std::ios::beg);
        if (!file.read(
                reinterpret_cast<char*>(bytes.data()),
                static_cast<std::streamsize>(bytes.size())))
        {
            return std::unexpected(core::PageError::ReadFailed); 
        }

        return bytes;
    }

    FolderPageSource::FolderPageSource(std::vector<std::filesystem::path> paths)
    : paths_(std::move(paths))
    {
    }
}