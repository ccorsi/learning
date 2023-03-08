/**
 * @file combinations_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=CombinationsII
 * @version 0.2
 * @date 2023-03-03
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
#include "combinations_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::combinations_two;

// Test Fixture Data Class
class CombinationsTwoData {
    int m_input;
    std::set<std::vector<int>> m_expected;
public:
    CombinationsTwoData() = default;

    int get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsTwoData &);
    friend std::istream& operator>>(std::istream&, CombinationsTwoData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsTwoData & data) {
    out << "CombinationsTwoData [ input=" << data.m_input << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    }
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsTwoData &data) {
    in >> data.m_input;
    std::string line;
    std::getline(in, line); // read the end of line
    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read the '{' line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> combination;
            vectorLoader<int> loader('[',']', combination);
            in >> loader;
            data.m_expected.insert(combination);
        } // while
        std::getline(in, line); // read the '}' line
        return in;
    } // if

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsTwoFixture :
    public testing::TestWithParam<CombinationsTwoData> {
};

// Parameterized Test Definition
TEST_P(CombinationsTwoFixture, CombinationsTwoTests) {
    CombinationsTwoData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findCombinations(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsTwoTests, CombinationsTwoFixture, testing::ValuesIn(
    Loader<CombinationsTwoData>()(find_path("arrays/data/combinations_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
