#include <gtest/gtest.h>

#include <fukiyomi/vision/opencv_bubble_detector.h>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include <cstdint>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    using fukiyomi::vision::OpenCVBubbleDetector;
    using fukiyomi::core::PageBytes;
    using fukiyomi::core::DetectError;

    PageBytes createEncodedImage(
        int width,
        int height,
        int type,
        const std::string& extension = ".png")
    {
        cv::Mat image(height, width, type, cv::Scalar::all(128));

        PageBytes bytes;

        if (!cv::imencode(extension, image, bytes))
        {
            throw std::runtime_error("Failed to encode test image");
        }

        return bytes;
    }
}

TEST(OpenCvBubbleDetectorTest, ReturnsErrorForEmptyPage)
{
    OpenCVBubbleDetector detector;
    PageBytes page;

    auto result = detector.detect(page);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), DetectError::EmptyPage);
}

TEST(OpenCvBubbleDetectorTest, ReturnsErrorForInvalidImageData)
{
    OpenCVBubbleDetector detector;

    PageBytes page = {
        0x01, 0x02, 0x03, 0x04,
        0x05, 0x06, 0x07, 0x08
    };

    auto result = detector.detect(page);

    ASSERT_FALSE(result.has_value());
    EXPECT_EQ(result.error(), DetectError::DecodeFailed);
}

TEST(OpenCvBubbleDetectorTest, DecodesValidPng)
{
    OpenCVBubbleDetector detector;

    PageBytes page = createEncodedImage(640, 480, CV_8UC3);

    auto result = detector.detect(page);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}

TEST(OpenCvBubbleDetectorTest, DecodesValidJpeg)
{
    OpenCVBubbleDetector detector;

    PageBytes page = createEncodedImage(640, 480, CV_8UC3, ".jpg");

    auto result = detector.detect(page);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}

TEST(OpenCvBubbleDetectorTest, DecodesGrayscaleImage)
{
    OpenCVBubbleDetector detector;

    PageBytes page = createEncodedImage(320, 240, CV_8UC1);

    auto result = detector.detect(page);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}

TEST(OpenCvBubbleDetectorTest, DecodesPngWithAlphaChannel)
{
    OpenCVBubbleDetector detector;

    PageBytes page = createEncodedImage(320, 240, CV_8UC4);

    auto result = detector.detect(page);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}

TEST(OpenCvBubbleDetectorTest, DecodesSinglePixelImage)
{
    OpenCVBubbleDetector detector;

    PageBytes page = createEncodedImage(1, 1, CV_8UC3);

    auto result = detector.detect(page);

    ASSERT_TRUE(result.has_value());
    EXPECT_TRUE(result->empty());
}