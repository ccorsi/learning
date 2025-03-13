/**
 * @file count_flipped_bitstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=CountFlippedBits
 * @version 0.1
 * @date 2025-03-11
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
#include "count_flipped_bits.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::count_flipped_bits;

// Test Fixture Data Class
class CountFlippedBitsData {
    int m_x, m_y, m_expected;
public:
    CountFlippedBitsData() = default;

    int get_x() { return m_x; }
    int get_y() { return m_y; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CountFlippedBitsData &);
    friend std::istream& operator>>(std::istream&, CountFlippedBitsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const CountFlippedBitsData & data) {
    return out << "CountFlippedBitsData [ x=" << data.m_x << " y=" << data.m_y << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, CountFlippedBitsData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_x;
                break;
            case 1:
                in >> data.m_y;
                break;
            case 2:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, CountFlippedBitsData &data) {
    ::loaders::loader::v6::dataLoader<
        CountFlippedBitsData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class CountFlippedBitsFixture :
    public testing::TestWithParam<CountFlippedBitsData> {
};

// Parameterized Test Definition
TEST_P(CountFlippedBitsFixture, CountFlippedBitsTests) {
    CountFlippedBitsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findBits(data.get_x(), data.get_y()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CountFlippedBitsTests, CountFlippedBitsFixture, testing::ValuesIn(
    Loader<CountFlippedBitsData>()(find_path("bit_manipulation/data/count_flipped_bits.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
