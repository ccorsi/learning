/**
 * @file toggle_kth_bittests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=ToggleKthBit
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
#include "toggle_kth_bit.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::toggle_kth_bit;

// Test Fixture Data Class
class ToggleKthBitData {
    int m_n, m_k, m_expected;
public:
    ToggleKthBitData() = default;

    int get_n() { return m_n; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ToggleKthBitData &);
    friend std::istream& operator>>(std::istream&, ToggleKthBitData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const ToggleKthBitData & data) {
    return out << "ToggleKthBitData [ n=" << data.m_n << ", k=" << data.m_k
        << ", expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ToggleKthBitData & data, int state) {
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
std::istream& operator>>(std::istream& in, ToggleKthBitData &data) {
    ::loaders::loader::v6::dataLoader<
        ToggleKthBitData,
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
class ToggleKthBitFixture :
    public testing::TestWithParam<ToggleKthBitData> {
};

// Parameterized Test Definition
TEST_P(ToggleKthBitFixture, ToggleKthBitTests) {
    ToggleKthBitData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.toggleKthBit(data.get_n(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ToggleKthBitTests, ToggleKthBitFixture, testing::ValuesIn(
    Loader<ToggleKthBitData>()(find_path("bit_manipulation/data/toggle_kth_bit.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
