/**
 * @file remove_adjacent_duplicatestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=RemoveAdjacentDuplicates
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
#include "remove_adjacent_duplicates.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::remove_adjacent_duplicates;

// Test Fixture Data Class
class RemoveAdjacentDuplicatesData {
    std::string m_s, m_expected;
public:
    RemoveAdjacentDuplicatesData() = default;

    std::string const & get_s() { return m_s; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RemoveAdjacentDuplicatesData &);
    friend std::istream& operator>>(std::istream&, RemoveAdjacentDuplicatesData &);

};

std::ostream& operator<<(std::ostream& out, const RemoveAdjacentDuplicatesData & data) {
    return out << "RemoveAdjacentDuplicatesData [ s=\"" << data.m_s << "\" expected=\""
        << data.m_expected << "\" ]";
}

struct StringReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::string & str, int state) {
        if (static_cast<char>(in.peek()) != '"') {
            str += static_cast<char>(in.get());
        }

        return in;
    }
};

std::istream& operator>>(std::istream& in, RemoveAdjacentDuplicatesData &data) {
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
        std::string,
        char,
        StringReader,
        1,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_character<char,'"'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_noop<int>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class RemoveAdjacentDuplicatesFixture :
    public testing::TestWithParam<RemoveAdjacentDuplicatesData> {
};

// Parameterized Test Definition
TEST_P(RemoveAdjacentDuplicatesFixture, RemoveAdjacentDuplicatesTests) {
    RemoveAdjacentDuplicatesData data = GetParam();

    Solution solution;

    std::string actual = data.get_s();

    solution.removeAdjacentDuplicates(actual);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RemoveAdjacentDuplicatesTests, RemoveAdjacentDuplicatesFixture, testing::ValuesIn(
    Loader<RemoveAdjacentDuplicatesData>()(find_path("strings/data/remove_adjacent_duplicates.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
