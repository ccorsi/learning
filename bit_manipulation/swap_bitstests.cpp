/**
 * @file swap_bitstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=SwapBits
 * @version 0.1
 * @date 2025-03-12
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
#include "swap_bits.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::swap_bits;

// Test Fixture Data Class
class SwapBitsData {
    int m_n, m_p, m_q, m_expected;
public:
    SwapBitsData() = default;

    int get_n() { return m_n; }
    int get_p() { return m_p; }
    int get_q() { return m_q; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SwapBitsData &);
    friend std::istream& operator>>(std::istream&, SwapBitsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const SwapBitsData & data) {
    return out << "SwapBitsData [ n=" << data.m_n << " p=" << data.m_p
        << " q=" << data.m_q << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, SwapBitsData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                in >> data.m_p;
                break;
            case 2:
                in >> data.m_q;
                break;
            case 3:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, SwapBitsData &data) {
    ::loaders::loader::v6::dataLoader<
        SwapBitsData,
        char,
        CombinedReader,
        4,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class SwapBitsFixture :
    public testing::TestWithParam<SwapBitsData> {
};

// Parameterized Test Definition
TEST_P(SwapBitsFixture, SwapBitsTests) {
    SwapBitsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.swapBits(data.get_n(), data.get_p(), data.get_q()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SwapBitsTests, SwapBitsFixture, testing::ValuesIn(
    Loader<SwapBitsData>()(find_path("bit_manipulation/data/swap_bits.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
