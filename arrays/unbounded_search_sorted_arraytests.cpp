/**
 * @file unbounded_search_sorted_arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This are tests for the problem https://www.techiedelight.com/?problem=UnboundedSearchSortedArray
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
#include "unbounded_search_sorted_array.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::arrays::unbounded_search_sorted_array;

// Test Fixture Data Class
class UnboundedSearchSortedArrayData {
    std::function<int(int)> m_func;
    int m_expected;
public:
    UnboundedSearchSortedArrayData() = default;
    UnboundedSearchSortedArrayData(std::function<int(int)> func, int expected) : m_func(func), m_expected(expected) {}

    std::function<int(int)> get_input() { return m_func; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const UnboundedSearchSortedArrayData &);
    friend std::istream& operator>>(std::istream&, UnboundedSearchSortedArrayData &);

};

std::ostream& operator<<(std::ostream& out, const UnboundedSearchSortedArrayData & data) {
    out << "UnboundedSearchSortedArrayData [ function=n/a expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, UnboundedSearchSortedArrayData &data) {
    std::string line;

    std::getline(in, line);
    // std::cout << "Function definition: " << line << std::endl;
    // Parse the equation and generate a lambda that is used by the data instance
    std::vector<int>::size_type pos = line.find_first_of("*^");
    if (pos != std::string::npos) {
        switch (line[pos])
        {
            // multiplication function
            // defined as n*x?c
            //  where n is an integer
            //        c is an integer
            //        ? is '+' or '-'
            //        x is just x
            case '*':
                {
                    int multiple = std::atoi(line.substr(0,pos).c_str());
                    pos = line.find_first_of("-+", pos);
                    if (pos != std::string::npos) {
                        int constant = std::atoi(line.substr(pos+1).c_str());
                        if (line[pos] == '-') {
                            constant *= -1;
                        } // if
                        data.m_func = [multiple, constant](int x) { return multiple * x + constant; };
                    } // if
                    else {
                        data.m_func = [multiple](int x) { return multiple * x; };
                    }
                }
                break;

            // power function
            // defined as x^n?c
            //  where n is an integer
            //        c is an integer
            //        ? is '+' or '-'
            //        x is just x
            // NOTE: This will not always be monotonically increasing function unless n is even
            case '^':
                {
                    std::vector<int>::size_type n = line.find_first_not_of("0123456789",pos+1);
                    int power = std::atoi(line.substr(pos+1, n-pos-1).c_str());
                    // std::cout << "Power: " << power << std::endl;
                    pos = line.find_first_of("-+", pos);
                    if (pos != std::string::npos) {
                        int constant = std::atoi(line.substr(pos+1).c_str());
                        if (line[pos] == '-') {
                            constant *= -1;
                        } // if
                        data.m_func = [power, constant](int x) { int result = 1; for (int cnt = power ; cnt > 0 ; cnt--) { result *= x; }; return result + constant; };
                    } // if
                    else {
                        data.m_func = [power](int x) { int result = 1; for (int cnt = power ; cnt > 0 ; cnt--) { result *= x; }; return result; };
                    }
                }
                break;

        }
    }  else {
        data.m_func = [](int x) { return 0; };
    } // else
    in >> data.m_expected;
    std::getline(in, line);
    // std::cout << "Expected result: " << data.m_expected << std::endl;

    return in;
}

// Test Fixture Class
class UnboundedSearchSortedArrayFixture :
    public testing::TestWithParam<UnboundedSearchSortedArrayData> {
};

// Parameterized Test Definition
TEST_P(UnboundedSearchSortedArrayFixture, UnboundedSearchSortedArrayTests) {
    UnboundedSearchSortedArrayData data = GetParam();

    Solution solution;

    f = data.get_input();

    int actual = solution.findValue();

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(UnboundedSearchSortedArrayTests, UnboundedSearchSortedArrayFixture, testing::ValuesIn(
    Loader<UnboundedSearchSortedArrayData>()(find_path("arrays/data/unbounded_search_sorted_array.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
