/**
 * @file combinations_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=CombinationsIII
 * @version 0.1
 * @date 2023-03-03
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
#include "combinations_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::combinations_three;

// Test Fixture Data Class
class CombinationsThreeData {
    int m_n;
    std::set<std::vector<int>> m_expected;
public:
    CombinationsThreeData() = default;

    int get_n() {return m_n; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsThreeData &);
    friend std::istream& operator>>(std::istream&, CombinationsThreeData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsThreeData & data) {
    out << "CombinationsThreeData [ n=" << data.m_n << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsThreeData &data) {
    in >> data.m_n;
    std::string line;
    std::getline(in, line); // read end of line
    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read '{' line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> values;
            in >> vectorLoader<int>('[', ']', values);
            data.m_expected.insert(values);
        } // for
        std::getline(in, line); // read '}' line
        return in;
    }

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsThreeFixture :
    public testing::TestWithParam<CombinationsThreeData> {
};

// Parameterized Test Definition
TEST_P(CombinationsThreeFixture, CombinationsThreeTests) {
    CombinationsThreeData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findCombinations(data.get_n());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsThreeTests, CombinationsThreeFixture, testing::ValuesIn(
    Loader<CombinationsThreeData>()(find_path("arrays/data/combinations_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
