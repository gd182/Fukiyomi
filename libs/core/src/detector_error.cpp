#include <fukiyomi/core/detector_error.h>

namespace fukiyomi::core
{
    std::string_view toString(DetectError error)
    {
        switch (error)
        {
            case DetectError::DecodeFailed:
                return "Failed to decode bytes";
            case DetectError::EmptyPage:
                return "Page is empty";
        }
        return "Unknown detection error";
    }
}