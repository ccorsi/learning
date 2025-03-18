/**
 * @file power_of_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=PowerOf4
 * @version 0.1
 * @date 2025-03-13
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
#include "power_of_four.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::power_of_four;

// Test Fixture Data Class
class PowerOfFourData {
    int m_n;
    bool m_expected;
public:
    PowerOfFourData() = default;

    int get_n() { return m_n; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PowerOfFourData &);
    friend std::istream& operator>>(std::istream&, PowerOfFourData &);

    friend struct CombinedReader;

};

std::ostream& operator<<(std::ostream& out, const PowerOfFourData & data) {
    return out << "PowerOfFourData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, PowerOfFourData & data, int state) {
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

std::istream& operator>>(std::istream& in, PowerOfFourData &data) {
    ::loaders::loader::v6::dataLoader<
        PowerOfFourData,
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
class PowerOfFourFixture :
    public testing::TestWithParam<PowerOfFourData> {
};

// Parameterized Test Definition
TEST_P(PowerOfFourFixture, PowerOfFourTests) {
    PowerOfFourData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.isPowerOf4(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PowerOfFourTests, PowerOfFourFixture, testing::ValuesIn(
    Loader<PowerOfFourData>()(find_path("bit_manipulation/data/power_of_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
