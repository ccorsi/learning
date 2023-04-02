/**
 * @file strictly_increasing_subarraystests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=StrictlyIncreasingSubarrays
 * @version 0.1
 * @date 2023-03-31
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
#include "strictly_increasing_subarrays.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::strictly_increasing_subarrays;

// Test Fixture Data Class
class StrictlyIncreasingSubarraysData {
    std::vector<int> m_input;
    int m_expected;
public:
    StrictlyIncreasingSubarraysData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const StrictlyIncreasingSubarraysData &);
    friend std::istream& operator>>(std::istream&, StrictlyIncreasingSubarraysData &);

};

std::ostream& operator<<(std::ostream& out, const StrictlyIncreasingSubarraysData & data) {
    out << "StrictlyIncreasingSubarraysData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, StrictlyIncreasingSubarraysData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in); // skip space characters
    in >> data.m_expected;
    skipSpace(in); // skip space characters

    return in;
}

// Test Fixture Class
class StrictlyIncreasingSubarraysFixture :
    public testing::TestWithParam<StrictlyIncreasingSubarraysData> {
};

// Parameterized Test Definition
TEST_P(StrictlyIncreasingSubarraysFixture, StrictlyIncreasingSubarraysTests) {
    StrictlyIncreasingSubarraysData data = GetParam();

    Solution solution;

    int actual = solution.getCount(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(StrictlyIncreasingSubarraysTests, StrictlyIncreasingSubarraysFixture, testing::ValuesIn(
    Loader<StrictlyIncreasingSubarraysData>()(find_path("arrays/data/strictly_increasing_subarrays.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
