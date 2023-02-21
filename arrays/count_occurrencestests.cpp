/**
 * @file count_occurrencestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These are tests for the problem https://www.techiedelight.com/?problem=CountOccurrences
 * @version 0.1
 * @date 2023-02-21
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
#include "count_occurrences.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::count_occurrences;

// Test Fixture Data Class
class CountOccurrencesData {
    std::vector<int> m_input;
    int m_target;
    int m_expected;
public:
    CountOccurrencesData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CountOccurrencesData &);
    friend std::istream& operator>>(std::istream&, CountOccurrencesData &);

};

std::ostream& operator<<(std::ostream& out, const CountOccurrencesData & data) {
    out << "CountOccurrencesData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, CountOccurrencesData &data) {
    std::string line;
    std::getline(in,line); // read '[' character line
    std::cout << "Line: " << line << std::endl;

    if (line == "[") {
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
            std::getline(in, line); // read the end of line
        } // while
        std::getline(in,line); // read ']' character line
    } // if

    in >> data.m_target >> data.m_expected;
    std::getline(in,line); // read end of line

    return in;
}

// Test Fixture Class
class CountOccurrencesFixture :
    public testing::TestWithParam<CountOccurrencesData> {
};

// Parameterized Test Definition
TEST_P(CountOccurrencesFixture, CountOccurrencesTests) {
    CountOccurrencesData data = GetParam();

    Solution solution;

    int actual = solution.countOccurrences(data.get_input(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CountOccurrencesTests, CountOccurrencesFixture, testing::ValuesIn(
    Loader<CountOccurrencesData>()(find_path("arrays/data/count_occurrences.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
