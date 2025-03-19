/**
 * @file swap_adjacent_bitstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SwapAdjacentBits
 * @version 0.1
 * @date 2025-03-18
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "swap_adjacent_bits.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::swap_adjacent_bits;

// Test Fixture Data Class
class SwapAdjacentBitsData {
    int m_n, m_expected;
public:
    SwapAdjacentBitsData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SwapAdjacentBitsData &);
    friend std::istream& operator>>(std::istream&, SwapAdjacentBitsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const SwapAdjacentBitsData & data) {
    return out << "SwapAdjacentBitsData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, SwapAdjacentBitsData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, SwapAdjacentBitsData &data) {
    ::loaders::loader::v6::dataLoader<
        SwapAdjacentBitsData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class SwapAdjacentBitsFixture :
    public testing::TestWithParam<SwapAdjacentBitsData> {
};

// Parameterized Test Definition
TEST_P(SwapAdjacentBitsFixture, SwapAdjacentBitsTests) {
    SwapAdjacentBitsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.swapAdjacentBits(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SwapAdjacentBitsTests, SwapAdjacentBitsFixture, testing::ValuesIn(
    Loader<SwapAdjacentBitsData>()(find_path("bit_manipulation/data/swap_adjacent_bits.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
