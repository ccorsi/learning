/**
 * @file negative_numbers_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=NegativeNumbersCount
 * @version 0.1
 * @date 2023-02-27
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
#include "negative_numbers_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::negative_numbers_count;

// Test Fixture Data Class
class NegativeNumbersCountData {
    std::vector<std::vector<int>> m_input;
    int m_expected;
public:
    NegativeNumbersCountData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NegativeNumbersCountData &);
    friend std::istream& operator>>(std::istream&, NegativeNumbersCountData &);

};

std::ostream& operator<<(std::ostream& out, const NegativeNumbersCountData & data) {
    out << "NegativeNumbersCountData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, NegativeNumbersCountData &data) {
    matrixLoader<int> loader(data.m_input);

    in >> loader;
    in >> data.m_expected;

    std::string line;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class NegativeNumbersCountFixture :
    public testing::TestWithParam<NegativeNumbersCountData> {
};

// Parameterized Test Definition
TEST_P(NegativeNumbersCountFixture, NegativeNumbersCountTests) {
    NegativeNumbersCountData data = GetParam();

    Solution solution;

    int actual = solution.negativeCount(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NegativeNumbersCountTests, NegativeNumbersCountFixture, testing::ValuesIn(
    Loader<NegativeNumbersCountData>()(find_path("matrices/data/negative_numbers_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
