/**
 * @file n_digit_numbers_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains test for the problem https://www.techiedelight.com/?problem=NDigitNumbersII
 * @version 0.1
 * @date 2025-02-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "n_digit_numbers_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::strings::n_digit_numbers_two;

// Test Fixture Data Class
class NDigitNumbersTwoData {
    int m_input;
    std::unordered_set<std::string> m_expected;
public:
    NDigitNumbersTwoData() = default;

    std::unordered_set<std::string> const & get_expected() { return m_expected; }
    int get_input() { return m_input; }

    friend std::ostream& operator<<(std::ostream&, const NDigitNumbersTwoData &);
    friend std::istream& operator>>(std::istream&, NDigitNumbersTwoData &);

};

std::ostream& operator<<(std::ostream& out, const NDigitNumbersTwoData & data) {
    out << "NDigitNumbersTwoData [ n=" << data.m_input << ", expected={ ";
    for (auto & entry : data.m_expected) {
        out << entry << " ";
    }
    out << "}";
    out << " ]";

    return out;
}

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & container, int state) {
        std::string value;

        ::loaders::loader::v6::dataLoader<
            std::string,
            char,
            StringReader,
            1,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_character<char, '"'>,
            ::checkers::is_space_or<','>,
            ::checkers::is_space_noop<char>
        > ValueLoader(value);
        in >> ValueLoader;

        container.insert(value);

        return in;
    }
};
std::istream& operator>>(std::istream& in, NDigitNumbersTwoData &data) {
    ::loaders::loader::v6::dataLoader<int,char> InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<
        std::unordered_set<std::string>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class NDigitNumbersTwoFixture :
    public testing::TestWithParam<NDigitNumbersTwoData> {
};

// Parameterized Test Definition
TEST_P(NDigitNumbersTwoFixture, NDigitNumbersTwoTests) {
    NDigitNumbersTwoData data = GetParam();

    Solution solution;

    auto actual = solution.findNDigitNumbers(data.get_input());
    auto & expected = data.get_expected();
    if (actual != expected) {
        for (auto & entry : expected) {
            if (actual.find(entry) == actual.end())
                std::cout << "Missing: " << entry << '\n';
        }
    }
    ASSERT_EQ(solution.findNDigitNumbers(data.get_input()), data.get_expected());

}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NDigitNumbersTwoTests, NDigitNumbersTwoFixture, testing::ValuesIn(
    Loader<NDigitNumbersTwoData>()(find_path("strings/data/n_digit_numbers_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
