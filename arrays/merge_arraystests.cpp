/**
 * @file merge_arraystests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "merge_arrays.h"

using namespace valhalla::arrays::merge_arrays;

class MergeArraysFixture :
    public testing::TestWithParam<std::pair<std::pair<std::vector<int>,std::vector<int>>,std::pair<std::vector<int>,std::vector<int>>>> {
private:
    std::vector<int> actualX, actualY, expectedX, expectedY;

protected:
    void SetUp() override {
        auto params = GetParam();

        auto actuals = params.first;
        actualX = actuals.first;
        actualY = actuals.second;

        auto expected = params.second;
        expectedX = expected.first;
        expectedY = expected.second;
    }

    const std::vector<int>& GetActualX() { return actualX; }
    const std::vector<int>& GetActualY() { return actualY; }

    const std::vector<int>& GetExpectedX() { return expectedX; }
    const std::vector<int>& GetExpectedY() { return expectedY; }
};

TEST_P(MergeArraysFixture, MergeArrays) {
    Solution solution;

    std::vector<int> actualX(GetActualX()), actualY(GetActualY()), expectedX(GetExpectedX()), expectedY(GetExpectedY());

    solution.merge(actualX, actualY);

    ASSERT_EQ(expectedX, actualX) << "X array was not sorted properly";
    ASSERT_EQ(expectedY, actualY) << "Y array was not sorted properly";
}

// Create some expected arrays
std::vector<int> v1x({1,2,3,4,5}),v1y({6,7,8}), v2x({1,2,3}), v2y({4,5,6,7,8});
// Create some expected pairs of arrays
std::pair<std::vector<int>,std::vector<int>> ex1(v1x,v1y), ex2(v2x,v2y);

std::pair<std::pair<std::vector<int>,std::vector<int>>,std::pair<std::vector<int>,std::vector<int>>> i1(ex1,ex1),
    i2({{4,5,6,7,8},{1,2,3}},ex1), i3({{1,3,4,5,7},{2,6,8}},ex1);

INSTANTIATE_TEST_SUITE_P(MergingArrays, MergeArraysFixture, testing::Values(i1, i2, i3));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}