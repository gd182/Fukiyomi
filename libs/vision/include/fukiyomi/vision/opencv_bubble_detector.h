#pragma once

#include <fukiyomi/core/bubble_detector.h>

namespace fukiyomi::vision
{
    class OpenCVBubbleDetector final : public core::IBubbleDetector
    {
    public:
        std::expected<std::vector<core::Rect>, core::DetectError> detect(const core::PageBytes& page) override;
    };
}