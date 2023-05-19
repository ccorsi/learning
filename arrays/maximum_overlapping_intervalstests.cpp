/**
 * @file maximum_overlapping_intervalstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MaximumOverlappingIntervals
 * @version 0.1
 * @date 2023-05-15
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
#include "maximum_overlapping_intervals.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::maximum_overlapping_intervals;

// Test Fixture Data Class
class MaximumOverlappingIntervalsData {
    std::vector<int> m_arrival;
    std::vector<int> m_departure;
    int m_expected;
public:
    MaximumOverlappingIntervalsData() = default;

    std::vector<int> const & get_arrival() { return m_arrival; }
    std::vector<int> const & get_departure() { return m_departure; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumOverlappingIntervalsData &);
    friend std::istream& operator>>(std::istream&, MaximumOverlappingIntervalsData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumOverlappingIntervalsData & data) {
    out << "MaximumOverlappingIntervalsData [ arrival=[";
    for (int value : data.m_arrival) {
        out << " " << value;
    }
    out << " ] departure=[";
    for (int value : data.m_departure) {
        out << " " << value;
    }
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumOverlappingIntervalsData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > arrivalLoader(data.m_arrival,'[', ']');
    in >> arrivalLoader;

    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > departureLoader(data.m_departure,'[', ']');
    in >> departureLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MaximumOverlappingIntervalsFixture :
    public testing::TestWithParam<MaximumOverlappingIntervalsData> {
};

// Parameterized Test Definition
TEST_P(MaximumOverlappingIntervalsFixture, MaximumOverlappingIntervalsTests) {
    MaximumOverlappingIntervalsData data = GetParam();

    Solution solution;

    int actual = solution.findMaxGuests(data.get_arrival(), data.get_departure());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumOverlappingIntervalsTests, MaximumOverlappingIntervalsFixture, testing::ValuesIn(
    Loader<MaximumOverlappingIntervalsData>()(find_path("arrays/data/maximum_overlapping_intervals.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
