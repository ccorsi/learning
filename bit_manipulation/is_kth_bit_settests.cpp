/**
 * @file is_kth_bit_settests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the solution https://www.techiedelight.com/?problem=IsKthBitSet
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
#include "is_kth_bit_set.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::is_kth_bit_set;

// Test Fixture Data Class
class IsKthBitSetData {
    int m_n, m_k;
    bool m_expected;
public:
    IsKthBitSetData() = default;

    int get_n() { return m_n; }
    int get_k() { return m_k; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const IsKthBitSetData &);
    friend std::istream& operator>>(std::istream&, IsKthBitSetData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const IsKthBitSetData & data) {
    return out << "IsKthBitSetData [ n=" << data.m_n << ", k=" << data.m_k
        << ", expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, IsKthBitSetData & data, int state) {
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

std::istream& operator>>(std::istream& in, IsKthBitSetData &data) {
    ::loaders::loader::v6::dataLoader<
        IsKthBitSetData,
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
class IsKthBitSetFixture :
    public testing::TestWithParam<IsKthBitSetData> {
};

// Parameterized Test Definition
TEST_P(IsKthBitSetFixture, IsKthBitSetTests) {
    IsKthBitSetData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.isKthBitSet(data.get_n(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(IsKthBitSetTests, IsKthBitSetFixture, testing::ValuesIn(
    Loader<IsKthBitSetData>()(find_path("bit_manipulation/data/is_kth_bit_set.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
