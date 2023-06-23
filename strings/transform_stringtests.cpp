/**
 * @file transform_stringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TransformString
 * @version 0.1
 * @date 2023-06-23
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
#include "transform_string.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::transform_string;

// Test Fixture Data Class
class TransformStringData {
    std::string m_x, m_y;
    int m_expected;
public:
    TransformStringData() = default;

    std::string const & get_x() { return m_x; }
    std::string const & get_y() { return m_y; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TransformStringData &);
    friend std::istream& operator>>(std::istream&, TransformStringData &);

};

std::ostream& operator<<(std::ostream& out, const TransformStringData & data) {
    return out << "TransformStringData [ X=\"" << data.m_x << "\" Y=\"" << data.m_y
        << "\" expected=" << data.m_expected << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        str += static_cast<char>(in.get());

        return in;
    }
};

std::istream& operator>>(std::istream& in, TransformStringData &data) {
    std::cout << "Reading X" << std::endl;
    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_noop<int>
    > xLoader(data.m_x);
    in >> xLoader;

    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpace;
    skipSpace(in);

    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_noop<int>
    > yLoader(data.m_y);
    in >> yLoader;

    ::loaders::loader::v4::dataLoader<
        int,
        char,
        loader::v4::reader<int,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class TransformStringFixture :
    public testing::TestWithParam<TransformStringData> {
};

// Parameterized Test Definition
TEST_P(TransformStringFixture, TransformStringTests) {
    TransformStringData data = GetParam();

    Solution solution;

    int actual = solution.getMinimumOperations(data.get_x(), data.get_y());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TransformStringTests, TransformStringFixture, testing::ValuesIn(
    Loader<TransformStringData>()(find_path("strings/data/transform_string.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
