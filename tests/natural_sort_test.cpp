#include <gtest/gtest.h>

#include <fukiyomi/core/natural_sort.h>

#include <algorithm>
#include <string>
#include <vector>

namespace
{
    using fukiyomi::core::naturalLess;

    TEST(NaturalSortTest, ComparesNumbersNaturally)
    {
        EXPECT_TRUE(naturalLess("page2", "page10"));
        EXPECT_TRUE(naturalLess("page9", "page10"));
        EXPECT_TRUE(naturalLess("1", "2"));
        EXPECT_TRUE(naturalLess("9", "10"));
        EXPECT_TRUE(naturalLess("99", "100"));

        EXPECT_FALSE(naturalLess("page10", "page2"));
        EXPECT_FALSE(naturalLess("10", "9"));
        EXPECT_FALSE(naturalLess("100", "99"));
    }

    TEST(NaturalSortTest, CaseDoesNotAffectNaturalOrder)
    {
        EXPECT_TRUE(naturalLess("Page2", "page10"));
        EXPECT_TRUE(naturalLess("page2", "Page10"));

        EXPECT_FALSE(naturalLess("Page10", "page2"));
        EXPECT_FALSE(naturalLess("page10", "Page2"));
    }

    TEST(NaturalSortTest, ComparesTextNaturally)
    {
        EXPECT_TRUE(naturalLess("a", "b"));
        EXPECT_TRUE(naturalLess("a", "ab"));
        EXPECT_TRUE(naturalLess("abc", "abd"));

        EXPECT_FALSE(naturalLess("b", "a"));
        EXPECT_FALSE(naturalLess("ab", "a"));
        EXPECT_FALSE(naturalLess("abd", "abc"));
    }

    TEST(NaturalSortTest, ComparesTextAfterEqualNumbers)
    {
        EXPECT_TRUE(naturalLess("a1b", "a1c"));
        EXPECT_TRUE(naturalLess("file10a", "file10b"));

        EXPECT_FALSE(naturalLess("a1c", "a1b"));
        EXPECT_FALSE(naturalLess("file10b", "file10a"));
    }

    TEST(NaturalSortTest, ComparesMultipleNumericParts)
    {
        EXPECT_TRUE(naturalLess("ch1_p9", "ch1_p10"));
        EXPECT_TRUE(naturalLess("ch1_p10", "ch2_p1"));
        EXPECT_TRUE(naturalLess("ch2_p2", "ch2_p10"));

        EXPECT_FALSE(naturalLess("ch1_p10", "ch1_p9"));
        EXPECT_FALSE(naturalLess("ch2_p1", "ch1_p10"));
        EXPECT_FALSE(naturalLess("ch2_p10", "ch2_p2"));
    }

    TEST(NaturalSortTest, ComparesLaterNumericParts)
    {
        EXPECT_TRUE(naturalLess("a1b2", "a1b10"));
        EXPECT_TRUE(naturalLess("a1b2c3", "a1b2c10"));
        EXPECT_TRUE(naturalLess("a1b2c10", "a1b10c1"));

        EXPECT_FALSE(naturalLess("a1b10", "a1b2"));
        EXPECT_FALSE(naturalLess("a1b2c10", "a1b2c3"));
    }

    TEST(NaturalSortTest, HandlesLeadingZeros)
    {
        EXPECT_TRUE(naturalLess("002", "10"));
        EXPECT_TRUE(naturalLess("0009", "10"));

        EXPECT_FALSE(naturalLess("10", "002"));
        EXPECT_FALSE(naturalLess("10", "0009"));
    }

    TEST(NaturalSortTest, OrdersEquivalentNumbersByLeadingZeros)
    {
        EXPECT_TRUE(naturalLess("2", "02"));
        EXPECT_TRUE(naturalLess("02", "002"));
        EXPECT_TRUE(naturalLess("2", "002"));

        EXPECT_FALSE(naturalLess("02", "2"));
        EXPECT_FALSE(naturalLess("002", "02"));
        EXPECT_FALSE(naturalLess("002", "2"));

        EXPECT_TRUE(naturalLess("0", "00"));
        EXPECT_TRUE(naturalLess("00", "000"));

        EXPECT_FALSE(naturalLess("00", "0"));
        EXPECT_FALSE(naturalLess("000", "00"));
    }

    TEST(NaturalSortTest, EqualStringsAreNotLess)
    {
        EXPECT_FALSE(naturalLess("", ""));
        EXPECT_FALSE(naturalLess("a", "a"));
        EXPECT_FALSE(naturalLess("abc", "abc"));
        EXPECT_FALSE(naturalLess("1", "1"));
        EXPECT_FALSE(naturalLess("123", "123"));
        EXPECT_FALSE(naturalLess("page2", "page2"));
        EXPECT_FALSE(naturalLess("ch1_p10", "ch1_p10"));
    }

    TEST(NaturalSortTest, HandlesEmptyStrings)
    {
        EXPECT_TRUE(naturalLess("", "a"));
        EXPECT_TRUE(naturalLess("", "1"));

        EXPECT_FALSE(naturalLess("a", ""));
        EXPECT_FALSE(naturalLess("1", ""));
    }

    TEST(NaturalSortTest, HandlesStringsWithoutNumbers)
    {
        EXPECT_TRUE(naturalLess("file", "fileA"));
        EXPECT_TRUE(naturalLess("abc", "abd"));

        EXPECT_FALSE(naturalLess("fileA", "file"));
        EXPECT_FALSE(naturalLess("abd", "abc"));
    }

    TEST(NaturalSortTest, HandlesNumberAtBeginning)
    {
        EXPECT_TRUE(naturalLess("2file", "10file"));
        EXPECT_TRUE(naturalLess("2abc", "10abc"));

        EXPECT_FALSE(naturalLess("10file", "2file"));
        EXPECT_FALSE(naturalLess("10abc", "2abc"));
    }

    TEST(NaturalSortTest, HandlesVeryLargeNumbers)
    {
        EXPECT_TRUE(
            naturalLess(
                "file999999999999999999999999999999",
                "file1000000000000000000000000000000"
            )
        );

        EXPECT_FALSE(
            naturalLess(
                "file1000000000000000000000000000000",
                "file999999999999999999999999999999"
            )
        );
    }

    TEST(NaturalSortTest, SortsSimpleSequence)
    {
        std::vector<std::string> values{
            "page10",
            "page2",
            "page1",
            "page20",
            "page3"
        };

        std::sort(
            values.begin(),
            values.end(),
            [](const auto& a, const auto& b)
            {
                return naturalLess(a, b);
            }
        );

        const std::vector<std::string> expected{
            "page1",
            "page2",
            "page3",
            "page10",
            "page20"
        };

        EXPECT_EQ(values, expected);
    }

    TEST(NaturalSortTest, SortsMultipleNumericParts)
    {
        std::vector<std::string> values{
            "ch10_p1",
            "ch2_p10",
            "ch1_p10",
            "ch2_p2",
            "ch1_p2"
        };

        std::sort(
            values.begin(),
            values.end(),
            [](const auto& a, const auto& b)
            {
                return naturalLess(a, b);
            }
        );

        const std::vector<std::string> expected{
            "ch1_p2",
            "ch1_p10",
            "ch2_p2",
            "ch2_p10",
            "ch10_p1"
        };

        EXPECT_EQ(values, expected);
    }

    TEST(NaturalSortTest, SortsMixedTextAndNumbers)
    {
        std::vector<std::string> values{
            "file10b",
            "file2",
            "file10a",
            "file1",
            "file20",
            "file3"
        };

        std::sort(
            values.begin(),
            values.end(),
            [](const auto& a, const auto& b)
            {
                return naturalLess(a, b);
            }
        );

        const std::vector<std::string> expected{
            "file1",
            "file2",
            "file3",
            "file10a",
            "file10b",
            "file20"
        };

        EXPECT_EQ(values, expected);
    }

    TEST(NaturalSortTest, MaintainsStrictWeakOrderingWithLeadingZeros)
    {
        EXPECT_TRUE(naturalLess("file2", "file02"));
        EXPECT_FALSE(naturalLess("file02", "file2"));

        EXPECT_TRUE(naturalLess("file02", "file002"));
        EXPECT_FALSE(naturalLess("file002", "file02"));

        EXPECT_TRUE(naturalLess("file2", "file002"));
        EXPECT_FALSE(naturalLess("file002", "file2"));
    }

    TEST(NaturalSortTest, SortsLeadingZerosDeterministically)
    {
        std::vector<std::string> values{
            "page002",
            "page10",
            "page02",
            "page1",
            "page2",
            "page001"
        };

        std::sort(
            values.begin(),
            values.end(),
            [](const auto& a, const auto& b)
            {
                return naturalLess(a, b);
            }
        );

        const std::vector<std::string> expected{
            "page1",
            "page001",
            "page2",
            "page02",
            "page002",
            "page10"
        };

        EXPECT_EQ(values, expected);
    }

    TEST(NaturalSortTest, NonAsciiBytesSortAfterAscii)
    {
        // "\xE3\x81\x82" — japan «あ» in UTF-8
        EXPECT_TRUE (naturalLess("pagea", "page\xE3\x81\x82"));
        EXPECT_FALSE(naturalLess("page\xE3\x81\x82", "pagea"));
    }   
}