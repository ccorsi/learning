/**
 * @file k_closest_elementstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=KClosestElements
 * @version 0.1
 * @date 2023-02-21
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
#include "k_closest_elements.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::k_closest_elements;

// Test Fixture Data Class
class KClosestElementsData {
    std::vector<int> m_input, m_expected;
    int m_x, m_target;
public:
    KClosestElementsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }
    int get_x() { return m_x; }
    int get_target() { return m_target; }

    friend std::ostream& operator<<(std::ostream&, const KClosestElementsData &);
    friend std::istream& operator>>(std::istream&, KClosestElementsData &);

};

std::ostream& operator<<(std::ostream& out, const KClosestElementsData & data) {
    out << "KClosestElementsData [ input=[";
    for(int value : data.m_input)
        out << " " << value;
    out << " ] x=" << data.m_x << " target=" << data.m_target << " expected=[";
    for(int value : data.m_expected)
        out << " " << value;
    out << " ]";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, KClosestElementsData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        char chr;
        in >> chr; // read the [ character

        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
        } // while

        std::string line;
        std::getline(in, line); // read ] and end of line

        in >> data.m_x >> data.m_target;
        std::getline(in, line); // read end of line

        if (static_cast<char>(in.peek()) == '[') {
            in >> chr; // read the [ character

            while (static_cast<char>(in.peek()) != ']') {
                int value;
                in >> value;
                data.m_expected.push_back(value);
            } // while

            std::getline(in, line); // read ] and end of line
        } // if
    } // if

    return in;
}

// Test Fixture Class
class KClosestElementsFixture :
    public testing::TestWithParam<KClosestElementsData> {
};

// Parameterized Test Definition
TEST_P(KClosestElementsFixture, KClosestElementsTests) {
    KClosestElementsData data = GetParam();

    Solution solution;

    std::vector<int> actual = solution.kClosestElements(data.get_input(), data.get_x(), data.get_target());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KClosestElementsTests, KClosestElementsFixture, testing::ValuesIn(
    Loader<KClosestElementsData>()(find_path("arrays/data/k_closest_elements.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
