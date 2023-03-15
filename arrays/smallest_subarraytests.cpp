/**
 * @file smallest_subarraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=SmallestSubarray
 * @version 0.1
 * @date 2023-03-15
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
#include "smallest_subarray.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::smallest_subarray;

// Test Fixture Data Class
class SmallestSubarrayData {
    std::vector<int> m_input;
    int m_k, m_expected;
public:
    SmallestSubarrayData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SmallestSubarrayData &);
    friend std::istream& operator>>(std::istream&, SmallestSubarrayData &);

};

std::ostream& operator<<(std::ostream& out, const SmallestSubarrayData & data) {
    out << "SmallestSubarrayData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, SmallestSubarrayData &data) {
    ::loaders::vectors::vectorLoader<
        int,
        std::vector<int>,
        char,
        ::checkers::is_space_or<','>
    > loader(data.m_input, '[', ']');
    in >> loader;

    in >> data.m_k >> data.m_expected;
    std::string line;
    std::getline(in, line); // read end of line

    return in;
}

// Test Fixture Class
class SmallestSubarrayFixture :
    public testing::TestWithParam<SmallestSubarrayData> {
};

// Parameterized Test Definition
TEST_P(SmallestSubarrayFixture, SmallestSubarrayTests) {
    SmallestSubarrayData data = GetParam();

    Solution solution;

    int actual = solution.findSmallestSubarray(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SmallestSubarrayTests, SmallestSubarrayFixture, testing::ValuesIn(
    Loader<SmallestSubarrayData>()(find_path("arrays/data/smallest_subarray.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
