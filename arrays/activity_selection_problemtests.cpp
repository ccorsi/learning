/**
 * @file activity_selection_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ActivitySelectionProblem
 * @version 0.1
 * @date 2023-04-03
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
#include "activity_selection_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::activity_selection_problem;

// Test Fixture Data Class
class ActivitySelectionProblemData {
    std::vector<std::pair<int,int>> m_input;
    std::vector<std::set<std::pair<int,int>>> m_expected;
public:
    ActivitySelectionProblemData() = default;

    std::vector<std::pair<int,int>> const & get_input() { return m_input; }
    std::vector<std::set<std::pair<int,int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ActivitySelectionProblemData &);
    friend std::istream& operator>>(std::istream&, ActivitySelectionProblemData &);

};

std::ostream& operator<<(std::ostream& out, const ActivitySelectionProblemData & data) {
    out << "ActivitySelectionProblemData [ input=[";
    for (std::pair<int,int> values : data.m_input)
        out << " (" << values.first << "," << values.second << ")";
    out << " ] expected=[";
    for (std::set<std::pair<int,int>> values : data.m_expected) {
        out << " {";
        for (std::pair<int,int> value : values)
            out << " (" << value.first << "," << value.second << ")";
        out << " }";
    }
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ActivitySelectionProblemData &data) {
    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    if (static_cast<char>(in.peek()) == '[') {
        in.get(); // read '[' character
        skipSpace(in);
        while (static_cast<char>(in.peek()) != ']') {
            std::pair<int,int> values;
            ::loaders::pairs::pairLoader<
              int,
              int,
              char,
              '(',
              ')',
              ::checkers::is_space_or<','>
            > inputLoader(values);
            in >> inputLoader;

            data.m_input.push_back(values);
            skipSpace(in);
        } // while
        in.get(); // read ']' character
        skipSpace(in);

        if (static_cast<char>(in.peek()) == '[') {
            in.get(); // read '[' character
            skipSpace(in);

            while (static_cast<char>(in.peek()) != ']') {
                if (static_cast<char>(in.peek()) == '{') {
                    in.get(); // read '{' character
                    skipSpace(in);
                    std::set<std::pair<int,int>> pairs;

                    while (static_cast<char>(in.peek()) != '}') {
                        std::pair<int,int> values;
                        ::loaders::pairs::pairLoader<
                        int,
                        int,
                        char,
                        '(',
                        ')',
                        ::checkers::is_space_or<','>
                        > inputLoader(values);
                        in >> inputLoader;

                        pairs.insert(values);
                        skipSpace(in);
                    } // while
                    in.get(); // read '}' character
                    skipSpace(in);
                    data.m_expected.push_back(pairs);
                } else {
                    throw new std::runtime_error("Invalid input format");
                } // else
            } // if
            in.get(); // read ']' character
            skipSpace(in);

            return in;
        } // if
    } // if

    throw new std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ActivitySelectionProblemFixture :
    public testing::TestWithParam<ActivitySelectionProblemData> {
};

// Parameterized Test Definition
TEST_P(ActivitySelectionProblemFixture, ActivitySelectionProblemTests) {
    ActivitySelectionProblemData data = GetParam();

    Solution solution;

    std::set<std::pair<int,int>> actual = solution.selectActivity(data.get_input());

    ASSERT_THAT(actual, ::testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ActivitySelectionProblemTests, ActivitySelectionProblemFixture, testing::ValuesIn(
    Loader<ActivitySelectionProblemData>()(find_path("arrays/data/activity_selection_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
