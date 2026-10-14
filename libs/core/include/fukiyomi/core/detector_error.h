#pragma once

#include <string_view>

namespace fukiyomi::core
{
    enum class DetectError
    {
        DecodeFailed,      ///< Failed to decode bytes
        EmptyPage,         ///< Page is empty
    };

    /// Returns description of error code
    std::string_view toString(DetectError error);
}