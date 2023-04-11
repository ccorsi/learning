/**
 * @file k_divisible_pairstests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=KDivisiblePairs
 * @version 0.1
 * @date 2023-04-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "k_divisible_pairs.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::k_divisible_pairs;

// Test Fixture Data Class
class KDivisiblePairsData {
    std::vector<int> m_input;
    int m_k;
    bool m_expected;
public:
    KDivisiblePairsData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KDivisiblePairsData &);
    friend std::istream& operator>>(std::istream&, KDivisiblePairsData &);

};

std::ostream& operator<<(std::ostream& out, const KDivisiblePairsData & data) {
    out << "KDivisiblePairsData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << ((data.m_expected) ? "true" : "false") << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, KDivisiblePairsData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in);
    in >> data.m_k;
    skipSpace(in);
    in >> data.m_expected;
    skipSpace(in);

    return in;
}

// Test Fixture Class
class KDivisiblePairsFixture :
    public testing::TestWithParam<KDivisiblePairsData> {
};

// Parameterized Test Definition
TEST_P(KDivisiblePairsFixture, KDivisiblePairsTests) {
    KDivisiblePairsData data = GetParam();

    Solution solution;

    bool actual = solution.hasPairs(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KDivisiblePairsTests, KDivisiblePairsFixture, testing::ValuesIn(
    Loader<KDivisiblePairsData>()(find_path("arrays/data/k_divisible_pairs.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
