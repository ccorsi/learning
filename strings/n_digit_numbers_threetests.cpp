/**
 * @file n_digit_numbers_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=NDigitNumbersIII
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
#include "n_digit_numbers_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::strings::n_digit_numbers_three;

// Test Fixture Data Class
class NDigitNumbersThreeData {
    int m_input, m_target;
    std::unordered_set<int> m_expected;
public:
    NDigitNumbersThreeData() = default;

    int get_input() { return m_input; }
    int get_target() { return m_target; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NDigitNumbersThreeData &);
    friend std::istream& operator>>(std::istream&, NDigitNumbersThreeData &);

};

std::ostream& operator<<(std::ostream& out, const NDigitNumbersThreeData & data) {
    out << "NDigitNumbersThreeData [ n=" << data.m_input << ", target=" << data.m_target;
    out << ", expected={";
    for (auto & value : data.m_expected)
        out << ' ' << value;
    out << " } ]";

    return out;
}

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<int> & data, int state) {
        int value;

        ::loaders::loader::v6::dataLoader<int,char> ValueLoader(value);
        in >> ValueLoader;

        data.insert(value);

        return in;
    }
};
std::istream& operator>>(std::istream& in, NDigitNumbersThreeData &data) {
    ::loaders::loader::v6::dataLoader<int,char> InputLoader(data.m_input);
    in >> InputLoader;

    ::loaders::loader::v6::dataLoader<int,char> TargetLoader(data.m_target);
    in >> TargetLoader;

    ::loaders::loader::v6::dataLoader<
        std::unordered_set<int>,
        char,
        UnorderedSetReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space,
        ::checkers::is_space
    > ExpectedLoader(data.m_expected);
    in >> ExpectedLoader;

    return in;
}

// Test Fixture Class
class NDigitNumbersThreeFixture :
    public testing::TestWithParam<NDigitNumbersThreeData> {
};

// Parameterized Test Definition
TEST_P(NDigitNumbersThreeFixture, NDigitNumbersThreeTests) {
    NDigitNumbersThreeData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findNDigitNumbers(data.get_input(), data.get_target()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NDigitNumbersThreeTests, NDigitNumbersThreeFixture, testing::ValuesIn(
    Loader<NDigitNumbersThreeData>()(find_path("strings/data/n_digit_numbers_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
