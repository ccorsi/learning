/**
 * @file move_zeroes_to_endtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "move_zeroes_to_end.h"

using namespace valhalla::arrays::move_zeroes_to_end;

// Test Fixture Data Class
class MoveZeroesToEndData {
    std::vector<int> m_input;
    std::vector<int> m_expected;
public:
    MoveZeroesToEndData() = default;
    MoveZeroesToEndData(std::vector<int> input, std::vector<int> expected) : m_input(input), m_expected(expected) {}

    std::vector<int> get_input() { return m_input; }
    std::vector<int> get_expected() { return m_expected; }
};

// Test Fixture Class
class MoveZeroesToEndFixture :
    public testing::TestWithParam<MoveZeroesToEndData> {
};

TEST_P(MoveZeroesToEndFixture, MoveZeroesToEndTests) {
    MoveZeroesToEndData data = GetParam();

    Solution solution;

    std::vector<int> actual(data.get_input());

    solution.rearrange(actual);

    ASSERT_EQ(data.get_expected(), actual);
}

INSTANTIATE_TEST_SUITE_P(MoveZeroesToEndTests, MoveZeroesToEndFixture, testing::Values(
    MoveZeroesToEndData({6, 0, 8, 2, 3, 0, 4, 0, 1}, {6, 8, 2, 3, 4, 1, 0, 0, 0}),
    MoveZeroesToEndData({0, 0, 0}, {0, 0, 0}),
    MoveZeroesToEndData({0, 1, 0}, {1, 0, 0})
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
