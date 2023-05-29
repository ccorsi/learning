/**
 * @file unattended_customers_counttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=UnattendedCustomersCount
 * @version 0.1
 * @date 2023-05-19
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
#include "unattended_customers_count.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::strings::unattended_customers_count;

// Test Fixture Data Class
class UnattendedCustomersCountData {
    std::string m_input;
    int m_capactity, m_expected;
public:
    UnattendedCustomersCountData() = default;

    std::string const & get_input() { return m_input; }
    int get_capacity() { return m_capactity; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const UnattendedCustomersCountData &);
    friend std::istream& operator>>(std::istream&, UnattendedCustomersCountData &);

};

std::ostream& operator<<(std::ostream& out, const UnattendedCustomersCountData & data) {
    out << "UnattendedCustomersCountData [ sequence=\"" << data.m_input << "\" capacity=" << data.m_capactity;
    out << " expected=" << data.m_expected << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, UnattendedCustomersCountData &data) {
    ::loaders::primitive::primitiveLoader<
      std::string,
      char,
      ::checkers::is_space_or<','>
    > inputLoader(&data.m_input);
    in >> inputLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > capacityLoader(&data.m_capactity);
    in >> capacityLoader;

    ::loaders::primitive::primitiveLoader<
      int,
      char,
      ::checkers::is_space_or<','>
    > expectedLoader(&data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class UnattendedCustomersCountFixture :
    public testing::TestWithParam<UnattendedCustomersCountData> {
};

// Parameterized Test Definition
TEST_P(UnattendedCustomersCountFixture, UnattendedCustomersCountTests) {
    UnattendedCustomersCountData data = GetParam();

    Solution solution;

    std::string sequence = data.get_input();

    int actual = solution.findUnattendedCustomers(sequence, data.get_capacity());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(UnattendedCustomersCountTests, UnattendedCustomersCountFixture, testing::ValuesIn(
    Loader<UnattendedCustomersCountData>()(find_path("strings/data/unattended_customers_count.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
