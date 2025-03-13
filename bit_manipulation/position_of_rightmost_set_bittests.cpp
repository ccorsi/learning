/**
 * @file position_of_rightmost_set_bittests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains test for the problem https://www.techiedelight.com/?problem=PositionOfRightmostSetBit
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
#include "position_of_rightmost_set_bit.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::position_of_rightmost_set_bit;

// Test Fixture Data Class
class PositionOfRightmostSetBitData {
    int m_n, m_expected;
public:
    PositionOfRightmostSetBitData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PositionOfRightmostSetBitData &);
    friend std::istream& operator>>(std::istream&, PositionOfRightmostSetBitData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const PositionOfRightmostSetBitData & data) {
    return out << "PositionOfRightmostSetBitData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, PositionOfRightmostSetBitData & data, int state) {
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

std::istream& operator>>(std::istream& in, PositionOfRightmostSetBitData &data) {
    ::loaders::loader::v6::dataLoader<
        PositionOfRightmostSetBitData,
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
class PositionOfRightmostSetBitFixture :
    public testing::TestWithParam<PositionOfRightmostSetBitData> {
};

// Parameterized Test Definition
TEST_P(PositionOfRightmostSetBitFixture, PositionOfRightmostSetBitTests) {
    PositionOfRightmostSetBitData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.positionOfRightmostSetBit(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PositionOfRightmostSetBitTests, PositionOfRightmostSetBitFixture, testing::ValuesIn(
    Loader<PositionOfRightmostSetBitData>()(find_path("bit_manipulation/data/position_of_rightmost_set_bit.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
