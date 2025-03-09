/**
 * @file minimum_delete_operationstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MinimumDeleteOperations
 * @version 0.1
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "minimum_delete_operations.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::dynamic_programming::minimum_delete_operations;

// Test Fixture Data Class
class MinimumDeleteOperationsData {
    std::string m_input;
    int m_expected;

public:
    MinimumDeleteOperationsData() = default;

    std::string get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MinimumDeleteOperationsData &);
    friend std::istream& operator>>(std::istream&, MinimumDeleteOperationsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MinimumDeleteOperationsData & data) {
    out << "MinimumDeleteOperationsData [ s=\"" << data.m_input << "\", expected=" << data.m_expected;
    out << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MinimumDeleteOperationsData & data, int state) {
        switch(state) {
            case 0:
            {
                ::loaders::loader::v6::dataLoader<
                    std::string,
                    char,
                    StringReader,
                    1,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_character<char, '"'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_noop<char>
                > InputLoader(data.m_input);
                in >> InputLoader;
            }
            break;
            case 1:
                in >> data.m_expected;
            break;
            default:
                throw std::runtime_error("INVALID STATE PASSED");
        } // switch(state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, MinimumDeleteOperationsData &data) {

    ::loaders::loader::v6::dataLoader<
        MinimumDeleteOperationsData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character_noop<char>,
        ::checkers::is_no_character<char>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;

}

// Test Fixture Class
class MinimumDeleteOperationsFixture :
    public testing::TestWithParam<MinimumDeleteOperationsData> {
};

// Parameterized Test Definition
TEST_P(MinimumDeleteOperationsFixture, MinimumDeleteOperationsTests) {
    MinimumDeleteOperationsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMinimumDeletions(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MinimumDeleteOperationsTests, MinimumDeleteOperationsFixture, testing::ValuesIn(
    Loader<MinimumDeleteOperationsData>()(find_path("dynamic_programming/data/minimum_delete_operations.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
