/**
 * @file common_elementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CommonElements
 * @version 0.1
 * @date 2023-03-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "common_elements.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::common_elements;

// Test Fixture Data Class
class CommonElementsData {
    std::vector<std::vector<int>> m_input;
    std::unordered_set<int> m_expected;
public:
    CommonElementsData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CommonElementsData &);
    friend std::istream& operator>>(std::istream&, CommonElementsData &);

};

std::ostream& operator<<(std::ostream& out, const CommonElementsData & data) {
    out << "CommonElementsData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, CommonElementsData &data) {
    matrixLoader<int> loader(data.m_input);

    in >> loader;

    if (static_cast<char>(in.peek()) == '{') {
        char chr;
        in >> chr;
        while (static_cast<char>(in.peek()) != '}') {
            int value;
            in >> value;
            data.m_expected.insert(value);
        }
        std::string line;
        std::getline(in, line); // read the '}' and the end of line
    } else {
        throw std::runtime_error("Invalid set character");
    } // else

    return in;
}

// Test Fixture Class
class CommonElementsFixture :
    public testing::TestWithParam<CommonElementsData> {
};

// Parameterized Test Definition
TEST_P(CommonElementsFixture, CommonElementsTests) {
    CommonElementsData data = GetParam();

    Solution solution;

    std::unordered_set<int> actual = solution.findCommonElements(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CommonElementsTests, CommonElementsFixture, testing::ValuesIn(
    Loader<CommonElementsData>()(find_path("matrices/data/common_elements.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
