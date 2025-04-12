/**
 * @file odd_occurring_element_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=OddOccurringElementIII
 * @version 0.1
 * @date 2025-04-11
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
#include "odd_occurring_element_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::odd_occurring_element_three;

// Test Fixture Data Class
class OddOccurringElementsThreeData {
    std::vector<int> m_nums;
    std::unordered_set<int> m_expected;
public:
    OddOccurringElementsThreeData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    std::unordered_set<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const OddOccurringElementsThreeData &);
    friend std::istream& operator>>(std::istream&, OddOccurringElementsThreeData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const OddOccurringElementsThreeData & data) {
    out << "OddOccurringElementsThreeData [ nums={";
    for (int num : data.m_nums)
        out << " " << num;
    out << (data.m_nums.empty() ? "" : " ") << "}, expected={";
    for (int result : data.m_expected)
        out << " " << result;
    out << (data.m_expected.empty() ? "" : " ") << "} ]";

    return out;
}

struct UnorderedSetReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::unordered_set<int> & data, int state) {
        switch (state) {
            case 0: {
                int value;
                in >> value;
                data.insert(value);
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, OddOccurringElementsThreeData  & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_nums);
                in >> VectorLoader;
            }
                break;
            case 1: {
                ::loaders::loader::v6::dataLoader<
                    std::unordered_set<int>,
                    char,
                    UnorderedSetReader,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > UnorderedSetLoader(data.m_expected);
                in >> UnorderedSetLoader;
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, OddOccurringElementsThreeData &data) {
    ::loaders::loader::v6::dataLoader<
        OddOccurringElementsThreeData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class OddOccurringElementsThreeFixture :
    public testing::TestWithParam<OddOccurringElementsThreeData> {
};

// Parameterized Test Definition
TEST_P(OddOccurringElementsThreeFixture, OddOccurringElementsThreeTests) {
    OddOccurringElementsThreeData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findOddOccurringElements(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(OddOccurringElementsThreeTests, OddOccurringElementsThreeFixture, testing::ValuesIn(
    Loader<OddOccurringElementsThreeData>()(find_path("bit_manipulation/data/odd_occurring_element_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
