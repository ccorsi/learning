/**
 * @file employees_manager_mappingtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=EmployeesManagerMapping
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "employees_manager_mapping.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::employees_manager_mapping;

// Test Fixture Data Class
class EmployeesManagerMappingData {
    std::unordered_map<char,char> m_input;
    std::unordered_map<char, std::unordered_set<char>> m_expected;

public:
    EmployeesManagerMappingData() = default;

    std::unordered_map<char,char> const & get_input() { return m_input; }
    std::unordered_map<char, std::unordered_set<char>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const EmployeesManagerMappingData &);
    friend std::istream& operator>>(std::istream&, EmployeesManagerMappingData &);

};

std::ostream& operator<<(std::ostream& out, const EmployeesManagerMappingData & data) {
    out << "EmployeesManagerMappingData [ input={";
    for (std::pair<char,char> value : data.m_input) {
        out << " '" << value.first << "' : '" << value.second << "'";
    }
    out << " } expected={";
    for (std::pair<char,std::unordered_set<char>> value : data.m_expected) {
        out << " '" << value.first << "' : [";
        for (char v : value.second) {
            out << " '" << v << "'";
        }
        out << " ]";
    }
    out << " } ]";

    return out;
}

std::istream& operator>>(std::istream& in, EmployeesManagerMappingData &data) {
    ::loaders::map::mapLoader<
      char,
      char,
      std::unordered_map<char,char>,
      char,
      '{',
      '}',
      ':',
      ::checkers::is_space_or<',','\''>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<',', '\''>> skipSpaces;

    skipSpaces(in);

    if (static_cast<char>(in.peek()) == '{') {
        in.get(); // read '{' character

        skipSpaces(in);

        while (static_cast<char>(in.peek()) != '}') {
            char key;
            std::unordered_set<char> values;

            in >> key;
            skipSpaces(in);

            if (static_cast<char>(in.peek()) != ':') {
                throw std::runtime_error("Invalid input format was passed");
            } // if

            in.get();

            ::loaders::set::setLoader<
              char,
              std::unordered_set<char>,
              char,
              ::checkers::is_space_or<',','\''>
            > valuesLoader(values,'[', ']');
            in >> valuesLoader;

            data.m_expected[key] = values;

            skipSpaces(in);
        } // while

        in.get(); // read '}' character

        skipSpaces(in);

        return in;
    } // if

    std::cout << "Invalid input format was passed. Invalid character: " << in.get() << std::endl;
    throw std::runtime_error("Invalid input format was passed");
}

// Test Fixture Class
class EmployeesManagerMappingFixture :
    public testing::TestWithParam<EmployeesManagerMappingData> {
};

// Parameterized Test Definition
TEST_P(EmployeesManagerMappingFixture, EmployeesManagerMappingTests) {
    EmployeesManagerMappingData data = GetParam();

    Solution solution;

    std::unordered_map<char, char> input = data.get_input();

    std::unordered_map<char, std::unordered_set<char>> actual = solution.findMapping(input);

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(EmployeesManagerMappingTests, EmployeesManagerMappingFixture, testing::ValuesIn(
    Loader<EmployeesManagerMappingData>()(find_path("dynamic_programming/data/employees_manager_mapping.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
