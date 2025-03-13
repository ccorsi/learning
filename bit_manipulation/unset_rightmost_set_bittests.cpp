/**
 * @file unset_rightmost_set_bittests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=UnsetRightmostSetBit
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
#include "unset_rightmost_set_bit.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::unset_rightmost_set_bit;

// Test Fixture Data Class
class UnsetRightmostSetBitData {
    int m_n, m_expected;
public:
    UnsetRightmostSetBitData() = default;

    int get_n() { return m_n; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const UnsetRightmostSetBitData &);
    friend std::istream& operator>>(std::istream&, UnsetRightmostSetBitData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const UnsetRightmostSetBitData & data) {
    return out << "UnsetRightmostSetBitData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, UnsetRightmostSetBitData & data, int state) {
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
std::istream& operator>>(std::istream& in, UnsetRightmostSetBitData &data) {
    ::loaders::loader::v6::dataLoader<
        UnsetRightmostSetBitData,
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
class UnsetRightmostSetBitFixture :
    public testing::TestWithParam<UnsetRightmostSetBitData> {
};

// Parameterized Test Definition
TEST_P(UnsetRightmostSetBitFixture, UnsetRightmostSetBitTests) {
    UnsetRightmostSetBitData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.unsetRightmostSetBit(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(UnsetRightmostSetBitTests, UnsetRightmostSetBitFixture, testing::ValuesIn(
    Loader<UnsetRightmostSetBitData>()(find_path("bit_manipulation/data/unset_rightmost_set_bit.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
