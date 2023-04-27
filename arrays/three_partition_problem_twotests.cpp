/**
 * @file three_partition_problem_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=3PartitionProblemII
 * @version 0.1
 * @date 2023-04-12
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
#include "three_partition_problem_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::three_partition_problem_two;

// Test Fixture Data Class
class ThreePartitionProblemTwoData {
    std::vector<int> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    ThreePartitionProblemTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ThreePartitionProblemTwoData &);
    friend std::istream& operator>>(std::istream&, ThreePartitionProblemTwoData &);

};

std::ostream& operator<<(std::ostream& out, const ThreePartitionProblemTwoData & data) {
    out << "ThreePartitionProblemTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, ThreePartitionProblemTwoData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;
    
    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '[') {
        in.get(); // read the '[' character
        skipSpace(in);
        while (static_cast<char>(in.peek()) != ']') {
            std::vector<int> expected;

            ::loaders::vectors::vectorLoader<
              int,
              std::vector<int>,
              char,
              ::checkers::is_space_or<','>
            > expectedLoader(expected,'[', ']');
            in >> expectedLoader;
            
            data.m_expected.push_back(expected);

            skipSpace(in);
        }
        in.get(); // read the ']' character
        skipSpace(in);
        return in;
    } // if

    throw new std::runtime_error("Invalid input format");
}

// Test Fixture Class
class ThreePartitionProblemTwoFixture :
    public testing::TestWithParam<ThreePartitionProblemTwoData> {
};

/*
 * This matcher is useful in the case that you want to compare two vectors that contain the
 * correct answer but are ordered differently.  This will be able to determine if the given
 * entries are part of the container or not.  The only requirement is that the entries of
 * the passed container has the operator!= defined. 
 */
MATCHER_P(IsPartOf, container,
    "This will determine if the passed container entries are part of the given container") {

    // Iterate over the container
    for (auto value : arg) {
        bool found = false;
        // determine if any of the entries are equal
        for (auto compare : container) {
            found |= value == compare;
            if (found) break;
        } // for
        // return early if not found
        if (found == false) return false;
    } // for

    return true;
}

// Parameterized Test Definition
TEST_P(ThreePartitionProblemTwoFixture, ThreePartitionProblemTwoTests) {
    ThreePartitionProblemTwoData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::vector<std::vector<int>> actual = solution.partition(input);

    ASSERT_THAT(actual, IsPartOf(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ThreePartitionProblemTwoTests, ThreePartitionProblemTwoFixture, testing::ValuesIn(
    Loader<ThreePartitionProblemTwoData>()(find_path("arrays/data/three_partition_problem_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
