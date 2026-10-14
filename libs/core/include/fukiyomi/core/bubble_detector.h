#pragma once

#include <fukiyomi/core/detector_error.h>
#include <fukiyomi/core/page_source.h>

#include <expected>
#include <vector>

namespace fukiyomi::core
{

    /// A plain rectangle, so that core does not depend on any image library (such as OpenCV)
    struct Rect
    {
        int x = 0;
        int y = 0;
        int width = 0;
        int height = 0;
    };

    class IBubbleDetector
    {
    public:
        virtual ~IBubbleDetector() = default;
        virtual std::expected<std::vector<Rect>, DetectError> detect(const PageBytes& page) = 0;
    };
}