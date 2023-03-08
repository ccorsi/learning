/**
 * @file combinations_seventests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsVII
 * @version 0.2
 * @date 2023-03-03
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
#include "combinations_seven.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::combinations_seven;

// Test Fixture Data Class
class CombinationsSevenData {
    std::unordered_set<std::string> m_expected;
    std::vector<std::vector<char>> m_input;
    std::vector<int> m_keys;

public:
    CombinationsSevenData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    std::vector<int> const & get_keys() { return m_keys; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsSevenData &);
    friend std::istream& operator>>(std::istream&, CombinationsSevenData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsSevenData & data) {
    out << "CombinationsSevenData [ input=[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char chr : values)
            out << " '" << chr << "'";
        out << " ]";
    } // for
    out << " ] keys=[";
    for (int value : data.m_keys)
        out << " " << value;
    out << " ] expected={";
    for (std::string word : data.m_expected)
        out << " \"" << word << "\"";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsSevenData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        std::string line;
        std::getline(in, line); // read the '[' line
        while (static_cast<char>(in.peek()) != ']') {
            std::vector<char> values;
            vectorLoader<char> loader('[', ']', values);
            in >> loader;
            data.m_input.push_back(values);
        } // while
        std::getline(in, line); // read the ']' line
        vectorLoader<int> loader('[', ']', data.m_keys);
        in >> loader;
        if (static_cast<char>(in.peek()) == '{') {
            std::getline(in, line); // read the '{' line
            while (static_cast<char>(in.peek()) != '}') {
                std::getline(in, line); // read word
                data.m_expected.insert(line);
            } // while
            std::getline(in, line); // read the '}' line
            return in;
        } // if
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsSevenFixture :
    public testing::TestWithParam<CombinationsSevenData> {
};

// Parameterized Test Definition
TEST_P(CombinationsSevenFixture, CombinationsSevenTests) {
    CombinationsSevenData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findCombinations(data.get_input(), data.get_keys());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsSevenTests, CombinationsSevenFixture, testing::ValuesIn(
    Loader<CombinationsSevenData>()(find_path("strings/data/combinations_seven.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
