#include <cstddef>
#include <iostream>

#include <expected>

#include <fukiyomi/core/version.h>
#include <fukiyomi/core/page_source.h>
#include <fukiyomi/sources/folder_page_source.h>

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        std::cerr << "Usage: fukiyomi <folder>" << std::endl;
        return 1;
    }

    std::cout << "version " << fukiyomi::core::getVersion() << std::endl;

    auto source = fukiyomi::sources::FolderPageSource::open(argv[1]);
    if (!source)
    {
        std::cerr << "Error: " << fukiyomi::core::toString(source.error()) << std::endl;
        return 1;
    }
    std::size_t pageCount = source->pageCount();
    std::cout << "Page count: " << pageCount << std::endl;
    bool hasFailedPages = false;
    for (std::size_t i = 0; i < pageCount; ++i)
    {
        auto page = source->readPage(i);
        if (!page)
        {
            hasFailedPages = true;
            std::cerr << "\tFailed to read page " << i << ": " << fukiyomi::core::toString(page.error()) << std::endl;
            continue;
        }
        std::cout << "\tSize page " << i << ": " << page->size() <<" bytes" <<std::endl;
    }
    if (hasFailedPages)
    {
        return 2;
    }
    return 0;
}