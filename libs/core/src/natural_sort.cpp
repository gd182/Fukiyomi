#include <fukiyomi/core/natural_sort.h>

#include <string_view>

namespace fukiyomi::core
{
    namespace
    {
        constexpr bool isDigit(char c) noexcept
        {
            return c >= '0' && c <= '9';
        }

        constexpr unsigned char toLower(char c) noexcept
        {
            const auto byte = static_cast<unsigned char>(c);
            if (byte >= 'A' && byte <= 'Z')
            {
                return static_cast<unsigned char>(byte + ('a' - 'A'));
            }
            return byte;
        }

        std::string_view extractNumber(std::string_view& str)
        {
            std::size_t end = 0;

            while (end < str.size() && isDigit(str[end]))
            {
                ++end;
            }

            const auto number = str.substr(0, end);
            str.remove_prefix(end);

            return number;
        }

        std::string_view trimLeadingZeros(std::string_view number)
        {
            while (number.size() > 1 && number.front() == '0')
            {
                number.remove_prefix(1);
            }

            return number;
        }

        int compareNumbers(std::string_view a, std::string_view b)
        {
            a = trimLeadingZeros(a);
            b = trimLeadingZeros(b);

            if (a.size() != b.size())
            {
                return a.size() < b.size() ? -1 : 1;
            }

            const int result = a.compare(b);

            if (result < 0)
            {
                return -1;
            }

            if (result > 0)
            {
                return 1;
            }

            return 0;
        }

        constexpr unsigned char toByte(char c) noexcept
        {
            return static_cast<unsigned char>(c);
        }
    }

    bool naturalLess(std::string_view a, std::string_view b)
    {
        int zeroTieBreak = 0;
        int caseTieBreak = 0;

        while (!a.empty() && !b.empty())
        {
            const bool digitA = isDigit(a.front());
            const bool digitB = isDigit(b.front());

            if (digitA && digitB)
            {
                const auto numberA = extractNumber(a);
                const auto numberB = extractNumber(b);

                const int result = compareNumbers(numberA, numberB);

                if (result != 0)
                {
                    return result < 0;
                }

                if (zeroTieBreak == 0 &&
                    numberA.size() != numberB.size())
                {
                    zeroTieBreak =
                        numberA.size() < numberB.size() ? -1 : 1;
                }

                continue;
            }

            const unsigned char charA = toLower(a.front());
            const unsigned char charB = toLower(b.front());

            if (charA != charB)
            {
                return charA < charB;
            }

            if (caseTieBreak == 0 &&
                a.front() != b.front())
            {
                caseTieBreak =
                    toByte(a.front()) < toByte(b.front()) ? -1 : 1;
            }

            a.remove_prefix(1);
            b.remove_prefix(1);
        }

        if (a.empty() != b.empty())
        {
            return a.empty();
        }

        if (zeroTieBreak != 0)
        {
            return zeroTieBreak < 0;
        }

        if (caseTieBreak != 0)
        {
            return caseTieBreak < 0;
        }
        return false;
    }
}