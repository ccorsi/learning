/**
 * @file transform_string_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TransformStringII
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
#include "transform_string_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::transform_string_two;

// Test Fixture Data Class
class TransformStringTwoData {
    std::string m_x, m_y;
    bool m_expected;
public:
    TransformStringTwoData() = default;

    std::string const & get_x() { return m_x; }
    std::string const & get_y() { return m_y; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TransformStringTwoData &);
    friend std::istream& operator>>(std::istream&, TransformStringTwoData &);

};

std::ostream& operator<<(std::ostream& out, const TransformStringTwoData & data) {
    return out << "TransformStringTwoData [ X=\"" << data.m_x << "\" Y=\"" << data.m_y
        << "\" expected=" << ((data.m_expected) ? "true" : "false") << " ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        str += static_cast<char>(in.get());

        return in;
    }
};

std::istream& operator>>(std::istream& in, TransformStringTwoData &data) {
    ::checkers::skip_spaces<char,::checkers::is_space_or<','>> skipSpaces;

    skipSpaces(in);

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

    skipSpaces(in);

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
        bool,
        char,
        loader::v4::reader<bool,char>,
        1,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class TransformStringTwoFixture :
    public testing::TestWithParam<TransformStringTwoData> {
};

// Parameterized Test Definition
TEST_P(TransformStringTwoFixture, TransformStringTwoTests) {
    TransformStringTwoData data = GetParam();

    Solution solution;

    bool actual = solution.isTransformable(data.get_x(), data.get_y());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TransformStringTwoTests, TransformStringTwoFixture, testing::ValuesIn(
    Loader<TransformStringTwoData>()(find_path("strings/data/transform_string_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
