/**
 * @file combinations_ninetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsIX
 * @version 0.1
 * @date 2023-03-06
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <cassert>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "combinations_nine.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::strings::combinations_nine;

// Test Fixture Data Class
class CombinationsNineData {
    std::vector<std::vector<std::string>> m_input;
    std::unordered_set<std::string> m_expected;
public:
    CombinationsNineData() = default;

    std::vector<std::vector<std::string>> const & get_input() { return m_input; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsNineData &);
    friend std::istream& operator>>(std::istream&, CombinationsNineData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsNineData & data) {
    out << "CombinationsNineData [ input=[";
    for (std::vector<std::string> words : data.m_input) {
        out << " [";
        for (std::string word : words)
            out << " \"" << word << "\"";
        out << " ]";
    } // for
    out << " ] expected={";
    for (std::string word : data.m_expected)
        out << " \"" << word << "\"";
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsNineData &data) {
    if (static_cast<char>(in.peek()) == '[') {
    // read the matrix
    // TODO: the following doesn't work when applied to a string
    // in >> matrixLoader<std::string>(data.m_input);

        std::string line;
        std::getline(in, line); // read the '[' line
        while (static_cast<char>(in.peek()) != ']') {
            if (static_cast<char>(in.peek()) == '[') {
                std::vector<std::string> words;
                char chr;
                in >> chr; // read the '[' character
                while (static_cast<char>(in.peek()) != ']') {
                    while (( chr = static_cast<char>(in.peek())) == ' ') in.get(); // skip white spaces
                    in >> chr; line = chr; // assign character to word and skip character
                    while ( (chr = static_cast<char>(in.peek()) != ' ' && static_cast<char>(in.peek()) != ']') ) {
                        assert(chr != ']');
                        in >> chr; line += chr; // append the character to word and skip character
                    } // while
                    words.push_back(line); // add word
                }
                std::getline(in, line); // read ']' to end of line
                data.m_input.push_back(words); // add words to input
            } else {
                std::cout << "Inner invalid input format: " << data << std::endl;
                throw std::runtime_error("Inner Invalid input format");
            } // else
        } // while
        std::getline(in, line); // read the ']' line

        if (static_cast<char>(in.peek()) == '{') {
            std::getline(in, line); // read the '{' line
            while (static_cast<char>(in.peek()) != '}') {
                std::getline(in, line); // read the word
                data.m_expected.insert(line); // add the read word
            } // while
            std::getline(in, line); // read the '}' line
            return in;
        }
    }

    std::cout << "Outter invalid input format: " << data << std::endl;
    throw std::runtime_error("Outter Invalid input format");
}

// Test Fixture Class
class CombinationsNineFixture :
    public testing::TestWithParam<CombinationsNineData> {
};

// Parameterized Test Definition
TEST_P(CombinationsNineFixture, CombinationsNineTests) {
    CombinationsNineData data = GetParam();

    Solution solution;

    std::unordered_set<std::string> actual = solution.findCombinations(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsNineTests, CombinationsNineFixture, testing::ValuesIn(
    Loader<CombinationsNineData>()(find_path("strings/data/combinations_nine.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
