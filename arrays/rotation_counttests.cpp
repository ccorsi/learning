/**
 * @file rotation_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=RotationCount
 * @version 0.1
 * @date 2023-02-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "rotation_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::rotation_count;

// Test Fixture Data Class
class RotationCountData {
    std::vector<int> m_input;
    int m_expected;
public:
    RotationCountData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const RotationCountData &);
    friend std::istream& operator>>(std::istream&, RotationCountData &);

};

std::ostream& operator<<(std::ostream& out, const RotationCountData & data) {
    out << "RotationCountData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, RotationCountData &data) {
    std::string line;
    std::getline(in, line);
    if (line == "[") {
        std::getline(in, line);
        while (line != "]") {
            data.m_input.push_back(std::atoi(line.c_str()));
            std::getline(in, line);
        } // while
    } // if
    in >> data.m_expected;
    std::getline(in, line); // read end of line character

    return in;
}

// Test Fixture Class
class RotationCountFixture :
    public testing::TestWithParam<RotationCountData> {
};

// Parameterized Test Definition
TEST_P(RotationCountFixture, RotationCountTests) {
    RotationCountData data = GetParam();

    Solution solution;

    int actual = solution.findRotationCount(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(RotationCountTests, RotationCountFixture, testing::ValuesIn(
    Loader<RotationCountData>()(find_path("arrays/data/rotation_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
