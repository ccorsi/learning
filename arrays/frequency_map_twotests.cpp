/**
 * @file frequency_map_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FrequencyMapII
 * @version 0.1
 * @date 2023-03-28
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
#include "frequency_map_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::frequency_map_two;

// Test Fixture Data Class
class FrequencyMapTwoData {
    std::vector<int> m_input;
    std::unordered_map<int,int> m_expected;
public:
    FrequencyMapTwoData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::unordered_map<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FrequencyMapTwoData &);
    friend std::istream& operator>>(std::istream&, FrequencyMapTwoData &);

};

std::ostream& operator<<(std::ostream& out, const FrequencyMapTwoData & data) {
    out << "FrequencyMapTwoData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::unordered_map<int,int>::value_type value : data.m_expected)
        out << " " << value.first << ":" << value.second;
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, FrequencyMapTwoData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read the '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            int key, value;

            in >> key;
            skipSpace(in);

            if (static_cast<char>(in.peek()) != ':') {
                throw std::runtime_error("Invalid input format");
            } // if
            in.get(); // read ':' character
            skipSpace(in);

            in >> value;
            data.m_expected[key] = value;

            skipSpace(in);
        } // while
        in.get(); // read '}' character
        skipSpace(in);

        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class FrequencyMapTwoFixture :
    public testing::TestWithParam<FrequencyMapTwoData> {
};

// Parameterized Test Definition
TEST_P(FrequencyMapTwoFixture, FrequencyMapTwoTests) {
    FrequencyMapTwoData data = GetParam();

    Solution solution;

    std::unordered_map<int,int> actual = solution.findFrequency(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FrequencyMapTwoTests, FrequencyMapTwoFixture, testing::ValuesIn(
    Loader<FrequencyMapTwoData>()(find_path("arrays/data/frequency_map_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
