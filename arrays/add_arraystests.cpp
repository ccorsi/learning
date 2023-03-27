/**
 * @file add_arraystests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=AddArrays
 * @version 0.1
 * @date 2023-03-27
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
#include "add_arrays.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::add_arrays;

// Test Fixture Data Class
class AddArraysData {
    std::vector<int> m_x_input, m_y_input;
    std::vector<int> m_expected;
public:
    AddArraysData() = default;

    std::vector<int> const & get_x_input() { return m_x_input; }
    std::vector<int> const & get_y_input() { return m_y_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const AddArraysData &);
    friend std::istream& operator>>(std::istream&, AddArraysData &);

};

std::ostream& operator<<(std::ostream& out, const AddArraysData & data) {
    out << "AddArraysData [ X=[";
    for (int value : data.m_x_input)
        out << " " << value;
    out << " ] Y=[";
    for (int value : data.m_y_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, AddArraysData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputXLoader(data.m_x_input, '[', ']');
    in >> inputXLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > inputYLoader(data.m_y_input, '[', ']');
    in >> inputYLoader;

    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected, '[', ']');
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class AddArraysFixture :
    public testing::TestWithParam<AddArraysData> {
};

// Parameterized Test Definition
TEST_P(AddArraysFixture, AddArraysTests) {
    AddArraysData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.add(data.get_x_input(), data.get_y_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(AddArraysTests, AddArraysFixture, testing::ValuesIn(
    Loader<AddArraysData>()(find_path("arrays/data/add_arrays.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
