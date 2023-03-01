/**
 * @file maximum_ones_rowtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=MaximumOnesRow
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "maximum_ones_row.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::maximum_ones_row;

// Test Fixture Data Class
class MaximumOnesRowData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    MaximumOnesRowData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input;  }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MaximumOnesRowData &);
    friend std::istream& operator>>(std::istream&, MaximumOnesRowData &);

};

std::ostream& operator<<(std::ostream& out, const MaximumOnesRowData & data) {
    out << "MaximumOnesRowData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    }
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MaximumOnesRowData &data) {
    matrixLoader<int> loader(data.m_input);

    in >> loader;

    in >> data.m_expected;

    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class MaximumOnesRowFixture :
    public testing::TestWithParam<MaximumOnesRowData> {
};

// Parameterized Test Definition
TEST_P(MaximumOnesRowFixture, MaximumOnesRowTests) {
    MaximumOnesRowData data = GetParam();

    Solution solution;

    int actual = solution.findRow(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaximumOnesRowTests, MaximumOnesRowFixture, testing::ValuesIn(
    Loader<MaximumOnesRowData>()(find_path("matrices/data/maximum_ones_row.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
