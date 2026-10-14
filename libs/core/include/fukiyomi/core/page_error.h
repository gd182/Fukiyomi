#pragma once

#include <string_view>

namespace fukiyomi::core
{
    enum class PageError
    {
        IndexOutOfRange,      ///< Index out of range (index >= page count) 
        ReadFailed,           ///< Failed to read the page data
        SourceNotFound        ///< The source does not exist or cannot be opened
    };

    /// Returns description of error code
    std::string_view toString(PageError error);
}