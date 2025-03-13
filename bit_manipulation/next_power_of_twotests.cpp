/**
 * @file next_power_of_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=NextPowerOf2
 * @version 0.1
 * @date 2025-03-12
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
#include "next_power_of_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::next_power_of_two;

// Test Fixture Data Class
class NextPowerOfTwoData {
    int m_n, m_expected;
public:
    NextPowerOfTwoData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const NextPowerOfTwoData &);
    friend std::istream& operator>>(std::istream&, NextPowerOfTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const NextPowerOfTwoData & data) {
    return out << "NextPowerOfTwoData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, NextPowerOfTwoData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
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

std::istream& operator>>(std::istream& in, NextPowerOfTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        NextPowerOfTwoData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class NextPowerOfTwoFixture :
    public testing::TestWithParam<NextPowerOfTwoData> {
};

// Parameterized Test Definition
TEST_P(NextPowerOfTwoFixture, NextPowerOfTwoTests) {
    NextPowerOfTwoData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.nextPowerOf2(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(NextPowerOfTwoTests, NextPowerOfTwoFixture, testing::ValuesIn(
    Loader<NextPowerOfTwoData>()(find_path("bit_manipulation/data/next_power_of_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
