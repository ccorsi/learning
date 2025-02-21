/**
 * @file n_digit_numbers_sixtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=NDigitNumbersVI
 * @version 0.1
 * @date 2025-02-20
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
#include "n_digit_numbers_six.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::backtracking::n_digit_numbers_six;

// Test Fixture Data Class
class NDigitNumbersSixData {
    int m_input;
    std::unordered_set<int> m_expected;

public:
    NDigitNumbersSixData() = default;

    int get_input() { return m_input; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NDigitNumbersSixData &);
    friend std::istream& operator>>(std::istream&, NDigitNumbersSixData &);

};

std::ostream& operator<<(std::ostream& out, const NDigitNumbersSixData & data) {
    out << "NDigitNumbersSixData [ n=" << data.m_input << ", expected={";
    for (auto & entry : data.m_expected)
        out << ' ' << entry;
    out << " } ]";

    return out;
}

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<int> & container, int state) {
        int value;

        ::loaders::loader::v6::dataLoader<int,char> ValueLoader(value);
        in >> ValueLoader;

        container.insert(value);

        return in;
    }
};
std::istream& operator>>(std::istream& in, NDigitNumbersSixData &data) {
    ::loaders::loader::v6::dataLoader<int,char> InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<
        std::unordered_set<int>,
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
class NDigitNumbersSixFixture :
    public testing::TestWithParam<NDigitNumbersSixData> {
};

// Parameterized Test Definition
TEST_P(NDigitNumbersSixFixture, NDigitNumbersSixTests) {
    NDigitNumbersSixData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findNDigitNumbers(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NDigitNumbersSixTests, NDigitNumbersSixFixture, testing::ValuesIn(
    Loader<NDigitNumbersSixData>()(find_path("backtracking/data/n_digit_numbers_six.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
