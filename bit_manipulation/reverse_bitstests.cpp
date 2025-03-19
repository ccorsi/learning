/**
 * @file reverse_bitstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ReverseBits
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
#include "reverse_bits.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::reverse_bits;

// Test Fixture Data Class
class ReverseBitsData {
    int m_n, m_expected;
public:
    ReverseBitsData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ReverseBitsData &);
    friend std::istream& operator>>(std::istream&, ReverseBitsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const ReverseBitsData & data) {
    return out << "ReverseBitsData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ReverseBitsData & data, int state) {
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

std::istream& operator>>(std::istream& in, ReverseBitsData &data) {
    ::loaders::loader::v6::dataLoader<
        ReverseBitsData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class ReverseBitsFixture :
    public testing::TestWithParam<ReverseBitsData> {
};

// Parameterized Test Definition
TEST_P(ReverseBitsFixture, ReverseBitsTests) {
    ReverseBitsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.reverseBits(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReverseBitsTests, ReverseBitsFixture, testing::ValuesIn(
    Loader<ReverseBitsData>()(find_path("bit_manipulation/data/reverse_bits.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
