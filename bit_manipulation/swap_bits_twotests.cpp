/**
 * @file swap_bits_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=SwapBitsII
 * @version 0.1
 * @date 2025-03-13
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
#include "swap_bits_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::swap_bits_two;

// Test Fixture Data Class
class SwapBitsTwoData {
    int m_n, m_p, m_q, m_b, m_expected;
public:
    SwapBitsTwoData() = default;

    int get_n() { return m_n; }
    int get_p() { return m_p; }
    int get_q() { return m_q; }
    int get_b() { return m_b; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SwapBitsTwoData &);
    friend std::istream& operator>>(std::istream&, SwapBitsTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const SwapBitsTwoData & data) {
    return out << "SwapBitsTwoData [ n=" << data.m_n << " p=" << data.m_p << " q=" << data.m_q
        << " b=" << data.m_b << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, SwapBitsTwoData & data, int state) {
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
                in >> data.m_b;
                break;
            case 4:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, SwapBitsTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        SwapBitsTwoData,
        char,
        CombinedReader,
        5,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class SwapBitsTwoFixture :
    public testing::TestWithParam<SwapBitsTwoData> {
};

// Parameterized Test Definition
TEST_P(SwapBitsTwoFixture, SwapBitsTwoTests) {
    SwapBitsTwoData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.swapBits(data.get_n(), data.get_p(), data.get_q(), data.get_b()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SwapBitsTwoTests, SwapBitsTwoFixture, testing::ValuesIn(
    Loader<SwapBitsTwoData>()(find_path("bit_manipulation/data/swap_bits_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
