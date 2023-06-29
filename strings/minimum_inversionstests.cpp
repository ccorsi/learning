/**
 * @file minimum_inversionstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumInversions
 * @version 0.1
 * @date 2023-06-29
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
#include "minimum_inversions.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::minimum_inversions;

// Test Fixture Data Class
class MinimumInversionsData {
    std::string m_s;
    int m_expected;
public:
    MinimumInversionsData() = default;

    std::string const & get_s() { return m_s; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumInversionsData &);
    friend std::istream& operator>>(std::istream&, MinimumInversionsData &);

};

std::ostream& operator<<(std::ostream& out, const MinimumInversionsData & data) {
    return out << "MinimumInversionsData [ s=\"" << data.m_s << "\" expected="
        << data.m_expected << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, MinimumInversionsData &data) {
    ::loaders::loader::v5::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > sLoader(data.m_s);
    in >> sLoader;

    ::loaders::loader::v5::dataLoader<
        int,
        char,
        loader::v5::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MinimumInversionsFixture :
    public testing::TestWithParam<MinimumInversionsData> {
};

// Parameterized Test Definition
TEST_P(MinimumInversionsFixture, MinimumInversionsTests) {
    MinimumInversionsData data = GetParam();

    Solution solution;

    int actual = solution.findMinimumInversions(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumInversionsTests, MinimumInversionsFixture, testing::ValuesIn(
    Loader<MinimumInversionsData>()(find_path("strings/data/minimum_inversions.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
