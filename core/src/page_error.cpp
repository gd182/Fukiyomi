#include <fukiyomi/core/page_error.h>

namespace fukiyomi::core
{
    std::string_view toString(PageError error)
    {
        switch (error)
        {
            case PageError::IndexOutOfRange:
                return "Index out of range";
            case PageError::ReadFailed:
                return "Read failed";
            case PageError::SourceNotFound:
                return "Source not found";
        }
        return "Unknown page error";
    }
}