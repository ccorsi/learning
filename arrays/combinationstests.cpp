/**
 * @file combinationstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=Combinations
 * @version 0.2
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
#include "combinations.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::combinations;

// Test Fixture Data Class
class CombinationsData {
    std::vector<int> m_input;
    int m_k;
    std::set<std::vector<int>> m_expected;
public:
    CombinationsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsData &);
    friend std::istream& operator>>(std::istream&, CombinationsData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsData & data) {
    out << "CombinationsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, CombinationsData &data) {
    vectorLoader<int> outerLoader('[', ']', data.m_input);
    in >> outerLoader;
    in >> data.m_k;
    std::string line;
    std::getline(in, line); // read end of line
    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read the '{' line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> combination;
            vectorLoader<int> innerLoader('[', ']', combination);
            in >> innerLoader;
            data.m_expected.insert(combination);
        } // while
        std::getline(in, line); // read the '}' line
        return in;
    }

    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsFixture :
    public testing::TestWithParam<CombinationsData> {
};

// Parameterized Test Definition
TEST_P(CombinationsFixture, CombinationsTests) {
    CombinationsData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findCombinations(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsTests, CombinationsFixture, testing::ValuesIn(
    Loader<CombinationsData>()(find_path("arrays/data/combinations.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
