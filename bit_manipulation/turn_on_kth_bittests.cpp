/**
 * @file turn_on_kth_bittests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=TurnOnKthBit
 * @version 0.1
 * @date 2025-03-10
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
#include "turn_on_kth_bit.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::turn_on_kth_bit;

// Test Fixture Data Class
class TurnOnKthBitData {
    int m_n, m_k, m_expected;
public:
    TurnOnKthBitData() = default;

    int get_n() { return m_n; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const TurnOnKthBitData &);
    friend std::istream& operator>>(std::istream&, TurnOnKthBitData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const TurnOnKthBitData & data) {
    return out << "TurnOnKthBitData [ n=" << data.m_n << ", k=" << data.m_k << ", expected="
               << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, TurnOnKthBitData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                in >> data.m_k;
                break;
            case 2:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};
std::istream& operator>>(std::istream& in, TurnOnKthBitData &data) {
    ::loaders::loader::v6::dataLoader<
        TurnOnKthBitData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class TurnOnKthBitFixture :
    public testing::TestWithParam<TurnOnKthBitData> {
};

// Parameterized Test Definition
TEST_P(TurnOnKthBitFixture, TurnOnKthBitTests) {
    TurnOnKthBitData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.turnOnKthBit(data.get_n(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(TurnOnKthBitTests, TurnOnKthBitFixture, testing::ValuesIn(
    Loader<TurnOnKthBitData>()(find_path("bit_manipulation/data/turn_on_kth_bit.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
