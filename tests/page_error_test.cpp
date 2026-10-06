#include <gtest/gtest.h>
#include <fukiyomi/core/page_error.h>

TEST(PageErrorTest, ToStringReturnsShortDescription)
{
    EXPECT_EQ("Index out of range", fukiyomi::core::toString(fukiyomi::core::PageError::IndexOutOfRange));
    EXPECT_EQ("Read failed", fukiyomi::core::toString(fukiyomi::core::PageError::ReadFailed));
    EXPECT_EQ("Source not found", fukiyomi::core::toString(fukiyomi::core::PageError::SourceNotFound));
}