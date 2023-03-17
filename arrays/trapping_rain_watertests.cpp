/**
 * @file trapping_rain_watertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TrappingRainWater
 * @version 0.1
 * @date 2023-03-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "trapping_rain_water.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::trapping_rain_water;

// Test Fixture Data Class
class TrappingRainWaterData {
    std::vector<int> m_input;
    int m_expected;
public:
    TrappingRainWaterData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TrappingRainWaterData &);
    friend std::istream& operator>>(std::istream&, TrappingRainWaterData &);

};

std::ostream& operator<<(std::ostream& out, const TrappingRainWaterData & data) {
    out << "TrappingRainWaterData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, TrappingRainWaterData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > loader(data.m_input, '[', ']');
    in >> loader;

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class TrappingRainWaterFixture :
    public testing::TestWithParam<TrappingRainWaterData> {
};

// Parameterized Test Definition
TEST_P(TrappingRainWaterFixture, TrappingRainWaterTests) {
    TrappingRainWaterData data = GetParam();

    Solution solution;

    int actual = solution.trapWater(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TrappingRainWaterTests, TrappingRainWaterFixture, testing::ValuesIn(
    Loader<TrappingRainWaterData>()(find_path("arrays/data/trapping_rain_water.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
