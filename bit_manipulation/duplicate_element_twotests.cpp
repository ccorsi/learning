/**
 * @file duplicate_element_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=DuplicateElementII
 * @version 0.1
 * @date 2025-04-12
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
#include "duplicate_element_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::duplicate_element_two;

// Test Fixture Data Class
class DuplicateElementTwoData {
    std::vector<int> m_nums;
    std::pair<int,int> m_expected;
public:
    DuplicateElementTwoData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DuplicateElementTwoData &);
    friend std::istream& operator>>(std::istream&, DuplicateElementTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const DuplicateElementTwoData & data) {
    out << "DuplicateElementTwoData [ nums={";
    out << (data.m_nums.empty() ? "" : " ") << "} expected=(" << data.m_expected.first << "," << data.m_expected.second << ") } ]";

    return out;
}

struct PairReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::pair<int,int> & data, int state) {
        switch (state) {
            case 0:
                in >> data.first;
                break;
            case 1:
                in >> data.second;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, DuplicateElementTwoData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_nums);
                in >> VectorLoader;
            }
                break;
            case 1: {
                ::loaders::loader::v6::dataLoader<
                    std::pair<int,int>,
                    char,
                    PairReader,
                    2,
                    ::checkers::is_character<char, '('>,
                    ::checkers::is_character<char, ')'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > PairLoader(data.m_expected);
                in >> PairLoader;
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, DuplicateElementTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        DuplicateElementTwoData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class DuplicateElementTwoFixture :
    public testing::TestWithParam<DuplicateElementTwoData> {
};

// Parameterized Test Definition
TEST_P(DuplicateElementTwoFixture, DuplicateElementTwoTests) {
    DuplicateElementTwoData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findDuplicateElements(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DuplicateElementTwoTests, DuplicateElementTwoFixture, testing::ValuesIn(
    Loader<DuplicateElementTwoData>()(find_path("bit_manipulation/data/duplicate_element_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
