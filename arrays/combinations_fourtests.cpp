/**
 * @file combinations_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=CombinationsIV
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
#include "combinations_four.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::combinations_four;

// Test Fixture Data Class
class CombinationsFourData {
    std::vector<int> m_input;
    int m_k;
    std::set<std::vector<int>> m_expected;
public:
    CombinationsFourData() = default;

    std::vector<int> & get_input() { return m_input; }
    int get_k() { return m_k; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CombinationsFourData &);
    friend std::istream& operator>>(std::istream&, CombinationsFourData &);

};

std::ostream& operator<<(std::ostream& out, const CombinationsFourData & data) {
    out << "CombinationsFourData [ input=[";
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

std::istream& operator>>(std::istream& in, CombinationsFourData &data) {
    vectorLoader<int> loader('[', ']', data.m_input);
    in >> loader;
    // std::cout << "Loading input" << std::endl;
    in >> data.m_k;
    std::string line;
    std::getline(in, line); // read end of line
    // std::cout << "Loading k=" << data.m_k << std::endl;
    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read '{' line
        // std::cout << "Read '{' line='" << line << "'" << std::endl;
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<int> values;
            vectorLoader<int> innerLoader('[', ']', values);
            in >> innerLoader;
            // std::cout << "Loading values" << std::endl;
            data.m_expected.insert(values);
        } // while
        std::getline(in, line); // read '}' line
        // std::cout << "Read '}' line='" << line << "'" << std::endl;
        return in;
    } // if

    // std::cout << "Invalid input format was encountered" << std::endl;
    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class CombinationsFourFixture :
    public testing::TestWithParam<CombinationsFourData> {
};

// Parameterized Test Definition
TEST_P(CombinationsFourFixture, CombinationsFourTests) {
    CombinationsFourData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findCombinations(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CombinationsFourTests, CombinationsFourFixture, testing::ValuesIn(
    Loader<CombinationsFourData>()(find_path("arrays/data/combinations_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
