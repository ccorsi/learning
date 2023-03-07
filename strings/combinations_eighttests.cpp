/**
 * @file combinations_eighttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsVIII
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
#include "combinations_eight.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::combinations_eight;

// Test Fixture Data Class
class CombinationsEightData {
    std::set<std::vector<std::string>> m_expected;
    std::string m_input;
public:
    CombinationsEightData() = default;

    std::set<std::vector<std::string>> const & get_expected() { return m_expected; }
    std::string get_input() { return m_input; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsEightData &);
    friend std::istream& operator>>(std::istream&, CombinationsEightData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsEightData & data) {
    out << "CombinationsEightData [ input=\"" << data.m_input << "\" expected={";
    for (std::vector<std::string> words : data.m_expected) {
        out << " [";
        for (std::string word : words)
            out << " \"" << word << "\"";
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsEightData &data) {
    std::getline(in, data.m_input); // read input line
    if (static_cast<char>(in.peek()) == '{') {
        std::string line;
        std::getline(in, line); // read the '{' line
        while (static_cast<char>(in.peek()) != '}') {
            if (static_cast<char>(in.peek()) == '[') {
                std::getline(in, line); // read '[' line
                std::vector<std::string> words;
                while (static_cast<char>(in.peek()) != ']') {
                    std::getline(in, line); // read word
                    words.push_back(line);
                } // while
                data.m_expected.insert(words);
                std::getline(in, line); // read ']' line
            } else {
                throw std::runtime_error("Invalid input format");
            } // else
        } // while
        std::getline(in, line); // read the '}' line
        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsEightFixture :
    public testing::TestWithParam<CombinationsEightData> {
};

// Parameterized Test Definition
TEST_P(CombinationsEightFixture, CombinationsEightTests) {
    CombinationsEightData data = GetParam();

    Solution solution;

    std::set<std::vector<std::string>> actual = solution.findCombinations(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsEightTests, CombinationsEightFixture, testing::ValuesIn(
    Loader<CombinationsEightData>()(find_path("strings/data/combinations_eight.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
