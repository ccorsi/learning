/**
 * @file arraytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains different tests that will be executed against the different
 *  array algorithms that insure that the given implementations fullfill the expected
 *  requirements for these algorithms.
 *
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "arrays.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

TEST(ArrayTestSuite, FindTargetFoundTest) {
    std::pair<int,int> result;
    std::vector<int> values = {1, 2, 4, 5, 10};

    bool found = valhalla::find_pair(values, 11, result);

    ASSERT_TRUE(found);

    ASSERT_EQ(result.first, 1);

    ASSERT_EQ(result.second, 10);

}

TEST(ArrayTestSuite, FindTargetNotFoundTest) {
    std::pair<int,int> result;
    std::vector<int> values = {1, 2, 4, 5, 10};

    ASSERT_FALSE(valhalla::find_pair(values, 21, result));

}

TEST(ArrayTestSuite, FindZeroSumFoundTest) {
    std::vector<int> values = {4, 2, -1, -3, 0, 4};

    ASSERT_TRUE(valhalla::find_subarray_with_zero_sum(values));

}

TEST(ArrayTestSuite, FindZeroSumNotFoundTest) {
    std::vector<int> values = {5, 2, -1, -3, 7, 5};

    ASSERT_FALSE(valhalla::find_subarray_with_zero_sum(values));

}

TEST(ArrayTestSuite, NotFoundPrintZeroSubArraysSumTest) {
    std::vector<int> values = {5, 2, -1, -3, 7, 5};

    ASSERT_EQ(0, valhalla::print_all_subarrays_with_zero_sum(values));

}

TEST(ArrayTestSuite, FoundPrintZeroSubArraysSumTest) {
    std::vector<int> values = {3, 4, -7, 3, 1, 3, 1, -4, -2, -2};
    std::stringstream ss;

    ASSERT_EQ(valhalla::print_all_subarrays_with_zero_sum(values, ss), 6);

    std::vector<std::string> expected = {
        "[0..2]",
        "[0..9]",
        "[1..3]",
        "[2..5]",
        "[3..9]",
        "[5..7]",
    };

    std::string actual = ss.str();

    for( auto itr = expected.begin() ; itr != expected.end() ; itr++ ) {
        EXPECT_THAT(actual, ::testing::HasSubstr(*itr)) << "Missing: " << *itr << " in the resulting output.";
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}