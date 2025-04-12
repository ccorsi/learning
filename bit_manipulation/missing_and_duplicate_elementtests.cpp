/**
 * @file missing_and_duplicate_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=MissingAndDuplicateElement
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
#include "missing_and_duplicate_element.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::missing_and_duplicate_element;

// Test Fixture Data Class
class MissingAndDuplicateElementData {
    std::vector<int> m_nums;
    std::pair<int,int> m_expected;
public:
    MissingAndDuplicateElementData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    std::pair<int,int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MissingAndDuplicateElementData &);
    friend std::istream& operator>>(std::istream&, MissingAndDuplicateElementData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MissingAndDuplicateElementData & data) {
    out << "MissingAndDuplicateElementData [ nums={";
    for (int num : data.m_nums)
        out << " " << num;
    out << (data.m_nums.empty() ? "" : " ") << "} expected=(" << data.m_expected.first << "," << data.m_expected.second << ") ]";

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
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MissingAndDuplicateElementData & data, int state) {
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

std::istream& operator>>(std::istream& in, MissingAndDuplicateElementData &data) {
    ::loaders::loader::v6::dataLoader<
        MissingAndDuplicateElementData,
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
class MissingAndDuplicateElementFixture :
    public testing::TestWithParam<MissingAndDuplicateElementData> {
};

// Parameterized Test Definition
TEST_P(MissingAndDuplicateElementFixture, MissingAndDuplicateElementTests) {
    MissingAndDuplicateElementData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMissingAndDuplicate(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MissingAndDuplicateElementTests, MissingAndDuplicateElementFixture, testing::ValuesIn(
    Loader<MissingAndDuplicateElementData>()(find_path("bit_manipulation/data/missing_and_duplicate_element.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
