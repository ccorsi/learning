/**
 * @file minimum_platformstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumPlatforms
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
#include "minimum_platforms.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::minimum_platforms;

// Test Fixture Data Class
class MinimumPlatformsData {
    std::vector<double> m_arrivals;
    std::vector<double> m_departures;
    int m_expected;
public:
    MinimumPlatformsData() = default;

    std::vector<double> get_arrivals() { return m_arrivals; }
    std::vector<double> get_departures() { return m_departures; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumPlatformsData &);
    friend std::istream& operator>>(std::istream&, MinimumPlatformsData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumPlatformsData & data) {
    out << "MinimumPlatformsData [ arrivals=[";
    for(double value : data.m_arrivals)
        out << " " << value;
    out << " ] departures=[";
    for(double value : data.m_departures)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MinimumPlatformsData &data) {
    ::loaders::vectors::vectorLoader<
        double,
        std::vector<double>,
        char,
        ::checkers::is_space_or<','>
    > arrivalLoader(data.m_arrivals, '[', ']');
    in >> arrivalLoader;

    ::loaders::vectors::vectorLoader<
        double,
        std::vector<double>,
        char,
        ::checkers::is_space_or<','>
    > departuresLoader(data.m_departures, '[', ']');
    in >> departuresLoader;

    in >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class MinimumPlatformsFixture :
    public testing::TestWithParam<MinimumPlatformsData> {
};

// Parameterized Test Definition
TEST_P(MinimumPlatformsFixture, MinimumPlatformsTests) {
    MinimumPlatformsData data = GetParam();

    Solution solution;

    int actual = solution.findMinPlatforms(data.get_arrivals(), data.get_departures());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumPlatformsTests, MinimumPlatformsFixture, testing::ValuesIn(
    Loader<MinimumPlatformsData>()(find_path("arrays/data/minimum_platforms.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
