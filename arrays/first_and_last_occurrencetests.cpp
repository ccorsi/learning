/**
 * @file first_and_last_occurrencetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These are tests for the problem https://www.techiedelight.com/?problem=FirstAndLastOccurrence
 * @version 0.1
 * @date 2023-02-20
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
#include "first_and_last_occurrence.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::first_and_last_occurrence;

// Test Fixture Data Class
class FirstAndLastOccurrenceData {
    std::vector<int> m_input;
    int m_target;
    std::pair<int,int> m_expected;
public:
    FirstAndLastOccurrenceData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_target() { return m_target; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FirstAndLastOccurrenceData &);
    friend std::istream& operator>>(std::istream&, FirstAndLastOccurrenceData &);

};

std::ostream& operator<<(std::ostream& out, const FirstAndLastOccurrenceData & data) {
    out << "FirstAndLastOccurrenceData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] target=" << data.m_target << " expected=(" << data.m_expected.first << "," << data.m_expected.second << ")";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, FirstAndLastOccurrenceData &data) {
    std::string line;
    std::getline(in, line);

    if(line == "[") {
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
            std::getline(in, line); // read the end of line
        } // while
        std::getline(in, line); // read the ] line
    } // if

    in >> data.m_target >> data.m_expected.first >> data.m_expected.second;
    std::getline(in, line); // read the end of line

    return in;
}

// Test Fixture Class
class FirstAndLastOccurrenceFixture :
    public testing::TestWithParam<FirstAndLastOccurrenceData> {
};

// Parameterized Test Definition
TEST_P(FirstAndLastOccurrenceFixture, FirstAndLastOccurrenceTests) {
    FirstAndLastOccurrenceData data = GetParam();

    Solution solution;

    std::pair<int,int> actual = solution.findPair(data.get_input(), data.get_target());

    std::pair<int, int> expected = data.get_expected();

    ASSERT_EQ(actual, expected);
    // ASSERT_EQ(actual.second, expected.second);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FirstAndLastOccurrenceTests, FirstAndLastOccurrenceFixture, testing::ValuesIn(
    Loader<FirstAndLastOccurrenceData>()(find_path("arrays/data/first_and_last_occurrence.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
