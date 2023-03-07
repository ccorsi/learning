/**
 * @file combinations_sixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsVI
 * @version 0.1
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
#include "combinations_six.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::combinations_six;

// Test Fixture Data Class
class CombinationsSixData {
    std::unordered_map<int,std::vector<char>> m_keypad;
    std::vector<int> m_input;
    std::unordered_set<std::string> m_expected;
public:
    CombinationsSixData() = default;

    std::unordered_map<int,std::vector<char>> & get_keypad() { return m_keypad; }
    std::vector<int> & get_input() { return m_input; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsSixData &);
    friend std::istream& operator>>(std::istream&, CombinationsSixData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsSixData & data) {
    out << "CombinationsSixData [ keypad={";
    for (std::pair<int,std::vector<char>> entry : data.m_keypad) {
        out << " " << entry.first << ": [";
        for (char chr : entry.second)
            out << " '" << chr << "'";
        out << " ]";
    } // for
    out << " } input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected={";
    for (std::string word : data.m_expected)
        out << " \"" << word << "\"";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsSixData &data) {
    if (static_cast<char>(in.peek()) == '{') {
        std::string line;
        std::getline(in, line); // read '{' line
        while (static_cast<char>(in.peek()) != '}') {
            int key;
            in >> key;
            char chr;
            in >> chr; // read ':' character
            while (static_cast<char>(in.peek()) == ' ') in.get(); // skip white spaces
            std::vector<char> values;
            in >> vectorLoader<char>('[', ']', values);
            data.m_keypad[key] = values;
        } // while
        std::getline(in, line); // read '}' line
        in >> vectorLoader<int>('[', ']', data.m_input);
        if (static_cast<char>(in.peek()) == '{'){
            std::getline(in, line); // read '{' line
            while (static_cast<char>(in.peek()) != '}') {
                std::getline(in, line); // read string
                data.m_expected.insert(line);
            } // while
            std::getline(in, line); // read '}' line
            return in;
        } // if
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsSixFixture :
    public testing::TestWithParam<CombinationsSixData> {
};

// Parameterized Test Definition
TEST_P(CombinationsSixFixture, CombinationsSixTests) {
    CombinationsSixData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findCombinations(data.get_keypad(), data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsSixTests, CombinationsSixFixture, testing::ValuesIn(
    Loader<CombinationsSixData>()(find_path("strings/data/combinations_six.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
