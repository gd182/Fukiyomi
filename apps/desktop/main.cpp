#include <cstddef>
#include <iostream>

#include <expected>

#include <fukiyomi/core/version.h>
#include <fukiyomi/core/page_source.h>
#include <fukiyomi/sources/folder_page_source.h>
#include <fukiyomi/core/reading_session.h>

int main(int argc, char* argv[])
{
    namespace fc = fukiyomi::core;
    namespace fsrc = fukiyomi::sources;

    if (argc <= 1)
    {
        std::cerr << "Usage: fukiyomi <folder>" << std::endl;
        return 1;
    }

    std::cout << "version " << fc::getVersion() << std::endl;

    auto source = fsrc::FolderPageSource::open(argv[1]);
    if (!source)
    {
        std::cerr << "Error: " << fc::toString(source.error()) << std::endl;
        return 1;
    }
    auto session = fc::ReadingSession(std::make_unique<fsrc::FolderPageSource>(std::move(*source)));
    std::size_t pageCount = session.pageCount();
    if (pageCount == 0)
    {
        std::cerr << "No pages found" << std::endl;
        return 3;    
    }
    std::cout << "Page count: " << pageCount << std::endl;
    bool hasFailedPages = false;
    do
    {
        auto page = session.currentPage();
        if (!page)
        {
            hasFailedPages = true;
            std::cerr << "\tFailed to read page " << session.currentIndex() << ": " << fc::toString(page.error()) << std::endl;
            continue;
        }
        std::cout << "\tSize page " << session.currentIndex() << ": " << page->size() <<" bytes" <<std::endl;
    } while (session.next());
    if (hasFailedPages)
    {
        return 2;
    }
    return 0;
}