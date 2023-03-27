/**
 * @file frequency_maptests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=FrequencyMap
 * @version 0.1
 * @date 2023-03-27
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
#include "frequency_map.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::frequency_map;

// Test Fixture Data Class
class FrequencyMapData {
    std::vector<int> m_input;
    std::unordered_map<int,int> m_expected;
public:
    FrequencyMapData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::unordered_map<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const FrequencyMapData &);
    friend std::istream& operator>>(std::istream&, FrequencyMapData &);

};

std::ostream& operator<<(std::ostream& out, const FrequencyMapData & data) {
    out << "FrequencyMapData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::unordered_map<int,int>::value_type entry : data.m_expected)
        out << " " << entry.first << ":" << entry.second;
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, FrequencyMapData &data) {
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
        in.get(); // read '{' character
        skipSpace(in);

        while (static_cast<char>(in.peek()) != '}') {
            skipSpace(in);
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
class FrequencyMapFixture :
    public testing::TestWithParam<FrequencyMapData> {
};

// Parameterized Test Definition
TEST_P(FrequencyMapFixture, FrequencyMapTests) {
    FrequencyMapData data = GetParam();

    Solution solution;

    std::vector<int> input = data.get_input();

    std::unordered_map<int,int> actual = solution.findFrequency(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(FrequencyMapTests, FrequencyMapFixture, testing::ValuesIn(
    Loader<FrequencyMapData>()(find_path("arrays/data/frequency_map.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
