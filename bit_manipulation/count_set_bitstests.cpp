/**
 * @file count_set_bitstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=CountSetBits
 * @version 0.1
 * @date 2025-03-11
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
#include "count_set_bits.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::count_set_bits;

// Test Fixture Data Class
class CountSetBitsData {
    int m_n, m_expected;
public:
    CountSetBitsData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CountSetBitsData &);
    friend std::istream& operator>>(std::istream&, CountSetBitsData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const CountSetBitsData & data) {
    return out << "CountSetBitsData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, CountSetBitsData & data, int state) {
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

std::istream& operator>>(std::istream& in, CountSetBitsData &data) {
    ::loaders::loader::v6::dataLoader<
        CountSetBitsData,
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
class CountSetBitsFixture :
    public testing::TestWithParam<CountSetBitsData> {
};

// Parameterized Test Definition
TEST_P(CountSetBitsFixture, CountSetBitsTests) {
    CountSetBitsData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.countSetBits(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CountSetBitsTests, CountSetBitsFixture, testing::ValuesIn(
    Loader<CountSetBitsData>()(find_path("bit_manipulation/data/count_set_bits.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
