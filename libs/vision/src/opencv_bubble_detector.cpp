#include <fukiyomi/vision/opencv_bubble_detector.h>

#include <opencv2/imgcodecs.hpp>

namespace fukiyomi::vision
{
    std::expected<std::vector<core::Rect>, core::DetectError> OpenCVBubbleDetector::detect(const core::PageBytes& page)
    {
        if (page.empty())
        {
            return std::unexpected(core::DetectError::EmptyPage);
        }
        cv::Mat image = cv::imdecode(page, cv::IMREAD_GRAYSCALE);
        if (image.empty())
        {
            return std::unexpected(core::DetectError::DecodeFailed);
        }
        return {};
    }
}