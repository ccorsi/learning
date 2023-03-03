/**
 * @file longest_pathtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=LongestPath
 * @version 0.1
 * @date 2023-03-02
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
#include "longest_path.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::longest_path;

// Test Fixture Data Class
class LongestPathData {
    std::vector<std::vector<int>> m_input;
    std::pair<int,int> m_src, m_dest;
    int m_expected;
public:
    LongestPathData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::pair<int,int> const & get_src() { return m_src; }
    std::pair<int,int> const & get_dest() { return m_dest; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const LongestPathData &);
    friend std::istream& operator>>(std::istream&, LongestPathData &);

};

std::ostream& operator<<(std::ostream& out, const LongestPathData & data) {
    out << "LongestPathData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] src=(" << data.m_src.first << "," << data.m_src.second << ") dest=("
        << data.m_dest.first << "," << data.m_dest.second << ") expected="
        << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, LongestPathData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        matrixLoader<int> loader(data.m_input);
        in >> loader;
        if (static_cast<char>(in.peek()) == '(') {
            std::string line;
            char chr;
            in >> chr >> data.m_src.first >> data.m_src.second;
            std::getline(in, line); // read the ')' to the end of line
            if (static_cast<char>(in.peek()) == '(') {
                in >> chr >> data.m_dest.first >> data.m_dest.second;
                std::getline(in, line); // read the ')' to the end of line
                in >> data.m_expected;
                std::getline(in, line); // read end of line
            } else {
                throw std::runtime_error("Invalid input format");
            }
        }
    } else {
        throw std::runtime_error("Invalid input format");
    }

    return in;
}

// Test Fixture Class
class LongestPathFixture :
    public testing::TestWithParam<LongestPathData> {
};

// Parameterized Test Definition
TEST_P(LongestPathFixture, LongestPathTests) {
    LongestPathData data = GetParam();

    Solution solution;

    int actual = solution.findLongestPathLen(data.get_input(), data.get_src(), data.get_dest());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(LongestPathTests, LongestPathFixture, testing::ValuesIn(
    Loader<LongestPathData>()(find_path("matrices/data/longest_path.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
