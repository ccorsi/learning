/**
 * @file transform_string_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=TransformStringIII
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
#include "transform_string_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::transform_string_three;

// Test Fixture Data Class
class TransformStringThreeData {
    std::string m_s, m_expected;
public:
    TransformStringThreeData() = default;

    std::string const & get_s() { return m_s; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TransformStringThreeData &);
    friend std::istream& operator>>(std::istream&, TransformStringThreeData &);

};

std::ostream& operator<<(std::ostream& out, const TransformStringThreeData & data) {
    return out << "TransformStringThreeData [ s=\"" << data.m_s << "\" expected=\""
        << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {

        if (static_cast<char>(in.peek()) != '"') {
            // only include it if it isn't a " character
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, TransformStringThreeData &data) {
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
    > sLoader(data.m_s);
    in >> sLoader;

    skipSpace(in);

    ::loaders::loader::v4::dataLoader<
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    skipSpace(in);

    return in;
}

// Test Fixture Class
class TransformStringThreeFixture :
    public testing::TestWithParam<TransformStringThreeData> {
};

// Parameterized Test Definition
TEST_P(TransformStringThreeFixture, TransformStringThreeTests) {
    TransformStringThreeData data = GetParam();

    Solution solution;

    std::string actual = solution.remove(data.get_s());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TransformStringThreeTests, TransformStringThreeFixture, testing::ValuesIn(
    Loader<TransformStringThreeData>()(find_path("strings/data/transform_string_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
