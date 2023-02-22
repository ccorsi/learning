/**
 * @file peak_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests for the problem https://www.techiedelight.com/?problem=PeakElement
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
#include "peak_element.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::peak_element;

// Test Fixture Data Class
class PeakElementData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    PeakElementData() = default;

    std::vector<int> const & get_input() { return m_input; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PeakElementData &);
    friend std::istream& operator>>(std::istream&, PeakElementData &);

};

std::ostream& operator<<(std::ostream& out, const PeakElementData & data) {
    out << "PeakElementData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=[";
    for (int value : data.m_expected)
        out << " " << value;
    out << " ]";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, PeakElementData &data) {
    if (static_cast<char>(in.peek()) == '[') {
        char chr;
        in >> chr; // read the '[' character
        while (static_cast<char>(in.peek()) != ']') {
            int value;
            in >> value;
            data.m_input.push_back(value);
        } // while
        std::string line;
        std::getline(in, line); // read ']' character to end of line
        if (static_cast<char>(in.peek()) == '[') {
            in >> chr; // read the '[' character
            while (static_cast<char>(in.peek()) != ']') {
                int value;
                in >> value;
                data.m_expected.push_back(value);
            } // while
            std::getline(in, line); // read ']' character to end of line
        } // if
    } // if

    return in;
}

// Test Fixture Class
class PeakElementFixture :
    public testing::TestWithParam<PeakElementData> {
};

// Parameterized Test Definition
TEST_P(PeakElementFixture, PeakElementTests) {
    PeakElementData data = GetParam();

    Solution solution;

    int actual = solution.findPeakElement(data.get_input());

    ASSERT_THAT(actual, testing::AnyOfArray(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PeakElementTests, PeakElementFixture, testing::ValuesIn(
    Loader<PeakElementData>()(find_path("arrays/data/peak_element.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
