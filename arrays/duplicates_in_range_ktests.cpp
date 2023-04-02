/**
 * @file duplicates_in_range_ktests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DuplicatesInRangeK
 * @version 0.1
 * @date 2023-04-01
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
#include "duplicates_in_range_k.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::arrays::duplicates_in_range_k;

// Test Fixture Data Class
class DuplicatesInRangeKData {
    std::vector<int> m_input;
    int m_k;
    bool m_expected;
public:
    DuplicatesInRangeKData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DuplicatesInRangeKData &);
    friend std::istream& operator>>(std::istream&, DuplicatesInRangeKData &);

};

std::ostream& operator<<(std::ostream& out, const DuplicatesInRangeKData & data) {
    out << "DuplicatesInRangeKData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << ((data.m_expected) ? "true" : "false") << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, DuplicatesInRangeKData &data) {
    ::loaders::vectors::vectorLoader<
      int,
      std::vector<int>,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input,'[', ']');
    in >> inputLoader;

    ::checkers::skip_spaces<char, ::checkers::is_space_or<','>> skipSpace;

    skipSpace(in); // skip space characters
    in >> data.m_k;
    skipSpace(in); // skip space characters
    in >> data.m_expected;
    skipSpace(in); // skip space characters

    return in;
}

// Test Fixture Class
class DuplicatesInRangeKFixture :
    public testing::TestWithParam<DuplicatesInRangeKData> {
};

// Parameterized Test Definition
TEST_P(DuplicatesInRangeKFixture, DuplicatesInRangeKTests) {
    DuplicatesInRangeKData data = GetParam();

    Solution solution;

    bool actual = solution.hasDuplicate(data.get_input(), data.get_k());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DuplicatesInRangeKTests, DuplicatesInRangeKFixture, testing::ValuesIn(
    Loader<DuplicatesInRangeKData>()(find_path("arrays/data/duplicates_in_range_k.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
