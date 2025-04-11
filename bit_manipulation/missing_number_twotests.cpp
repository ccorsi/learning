/**
 * @file missing_number_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MissingNumberII
 * @version 0.1
 * @date 2025-04-08
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
#include "missing_number_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::missing_number_two;

// Test Fixture Data Class
class MissingNumberTwoData {
    std::vector<int> m_nums;
    int m_expected;
public:
    MissingNumberTwoData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MissingNumberTwoData &);
    friend std::istream& operator>>(std::istream&, MissingNumberTwoData &);

    friend struct CombinedReader;
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MissingNumberTwoData & data, int state) {
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
            > DataLoader(data.m_nums);
            in >> DataLoader;
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

std::ostream& operator<<(std::ostream& out, const MissingNumberTwoData & data) {
    out << "MissingNumberTwoData [ nums={";
    for (int value : data.m_nums)
        out << " " << value;
    out << (data.m_nums.empty() ? "" : " ") << "} expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, MissingNumberTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        MissingNumberTwoData,
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
class MissingNumberTwoFixture :
    public testing::TestWithParam<MissingNumberTwoData> {
};

// Parameterized Test Definition
TEST_P(MissingNumberTwoFixture, MissingNumberTwoTests) {
    MissingNumberTwoData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMissingNumber(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MissingNumberTwoTests, MissingNumberTwoFixture, testing::ValuesIn(
    Loader<MissingNumberTwoData>()(find_path("bit_manipulation/data/missing_number_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
