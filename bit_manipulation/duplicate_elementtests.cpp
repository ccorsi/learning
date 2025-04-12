/**
 * @file duplicate_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=DuplicateElement
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
#include "duplicate_element.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::duplicate_element;

// Test Fixture Data Class
class DuplicateElementData {
    std::vector<int> m_nums;
    int m_expected;
public:
    DuplicateElementData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DuplicateElementData &);
    friend std::istream& operator>>(std::istream&, DuplicateElementData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const DuplicateElementData & data) {
    out << "DuplicateElementData [ nums={";
    for (int num : data.m_nums)
        out << " " << num;
    out << (data.m_nums.empty() ? "" : " ") << "} expected=" << data.m_expected << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, DuplicateElementData & data, int state) {
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
            case 1:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, DuplicateElementData &data) {
    ::loaders::loader::v6::dataLoader<
        DuplicateElementData,
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
class DuplicateElementFixture :
    public testing::TestWithParam<DuplicateElementData> {
};

// Parameterized Test Definition
TEST_P(DuplicateElementFixture, DuplicateElementTests) {
    DuplicateElementData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findDuplicateElement(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DuplicateElementTests, DuplicateElementFixture, testing::ValuesIn(
    Loader<DuplicateElementData>()(find_path("bit_manipulation/data/duplicate_element.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
