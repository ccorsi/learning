/**
 * @file maximum_product_pairtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-01
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "maximum_product_pair.h"

using namespace valhalla::arrays::maximum_product_pair;

TEST(MaximumProductPairTestSuite, EmptyValues) {
    Solution solution;

    std::vector<int> values = {};
    std::pair<int,int> expected(-1,-1);

    std::pair<int,int> actual = solution.find(values);

    ASSERT_EQ(expected, actual) << "no pairs exists";
}

TEST(MaximumProductPairTestSuite, NoneExists) {
    Solution solution;

    std::vector<int> values = { 1 };
    std::pair<int,int> expected(-1,-1);

    std::pair<int,int> actual = solution.find(values);

    ASSERT_EQ(expected, actual) << "no pairs exists";
}

// Input : [-10, -3, 5, 6, -2]
// Output: (-10, -3) or (-3, -10) or (5, 6) or (6, 5)
TEST(MaximumProductPairTestSuite, FourExists) {
    Solution solution;

    std::vector<int> values = { -10, -3, 5, 6, -2 };
    std::set<std::pair<int,int>> expected = {
        { -10, -3 }, { -3, -10 }, { 5, 6 }, { 6, 5 }
    };

    std::pair<int,int> actual = solution.find(values);
    std::cout << "Returned pair: [" << actual.first << "," << actual.second << "]" << std::endl;

    ASSERT_TRUE(expected.find(actual) != expected.end()) << "A maximum product pair exists";
}

// Input : [-4, 3, 2, 7, -5]
// Output: (3, 7) or (7, 3)
TEST(MaximumProductPairTestSuite, TwoExists) {
    Solution solution;

    std::vector<int> values = { -4, 3, 2, 7, -5 };
    std::set<std::pair<int,int>> expected = {
        { 3, 7 }, { 7, 3 }
    };

    std::pair<int,int> actual = solution.find(values);
    std::cout << "Returned pair: [" << actual.first << "," << actual.second << "]" << std::endl;

    ASSERT_TRUE(expected.find(actual) != expected.end()) << "A maximum product pair exists";
}

TEST(MaximumProductPairTestSuite, ZeroPair) {
    Solution solution;

    std::vector<int> values = { 0, 0 };
    std::set<std::pair<int,int>> expected = {
        { 0, 0 }
    };

    std::pair<int,int> actual = solution.find(values);
    std::cout << "Returned pair: [" << actual.first << "," << actual.second << "]" << std::endl;

    ASSERT_TRUE(expected.find(actual) != expected.end()) << "A maximum product pair exists";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}