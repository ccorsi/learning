/**
 * @file previous_power_of_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=PreviousPowerOf2
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
#include "previous_power_of_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::previous_power_of_two;

// Test Fixture Data Class
class PreviousPowerOfTwoData {
    int m_n, m_expected;
public:
    PreviousPowerOfTwoData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PreviousPowerOfTwoData &);
    friend std::istream& operator>>(std::istream&, PreviousPowerOfTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const PreviousPowerOfTwoData & data) {
    return out << "PreviousPowerOfTwoData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, PreviousPowerOfTwoData & data, int state) {
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

std::istream& operator>>(std::istream& in, PreviousPowerOfTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        PreviousPowerOfTwoData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class PreviousPowerOfTwoFixture :
    public testing::TestWithParam<PreviousPowerOfTwoData> {
};

// Parameterized Test Definition
TEST_P(PreviousPowerOfTwoFixture, PreviousPowerOfTwoTests) {
    PreviousPowerOfTwoData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.previousPowerOf2(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PreviousPowerOfTwoTests, PreviousPowerOfTwoFixture, testing::ValuesIn(
    Loader<PreviousPowerOfTwoData>()(find_path("bit_manipulation/data/previous_power_of_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
