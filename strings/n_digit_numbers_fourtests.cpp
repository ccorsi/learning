/**
 * @file n_digit_numbers_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=NDigitNumbersIV
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
#include "n_digit_numbers_four.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::strings::n_digit_numbers_four;

// Test Fixture Data Class
class NDigitNumbersFourData {
    int m_input;
    std::unordered_set<std::string> m_expected;
public:
    NDigitNumbersFourData() = default;

    int get_input() { return m_input; }
    std::unordered_set<std::string> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NDigitNumbersFourData &);
    friend std::istream& operator>>(std::istream&, NDigitNumbersFourData &);

};

std::ostream& operator<<(std::ostream& out, const NDigitNumbersFourData & data) {
    out << "NDigitNumbersFourData [ n=" << data.m_input << ", expected={";
    for (auto & entry : data.m_expected)
        out << ' ' << entry;
    out << " } ]";

    return out;
}

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<std::string> & data, int state) {
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
        > ExpectedLoader(value);
        in >> ExpectedLoader;

        data.insert(value);

        return in;
    }
};

std::istream& operator>>(std::istream& in, NDigitNumbersFourData &data) {
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
class NDigitNumbersFourFixture :
    public testing::TestWithParam<NDigitNumbersFourData> {
};

// Parameterized Test Definition
TEST_P(NDigitNumbersFourFixture, NDigitNumbersFourTests) {
    NDigitNumbersFourData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findNDigitNumbers(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NDigitNumbersFourTests, NDigitNumbersFourFixture, testing::ValuesIn(
    Loader<NDigitNumbersFourData>()(find_path("strings/data/n_digit_numbers_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
