/**
 * @file rotate_matrix_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=RotateMatrixII
 * @version 0.1
 * @date 2023-01-04
 * 
 * @copyright Copyright (c) 2023 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "rotate_matrix_two.h"

using namespace valhalla::matrices::rotate_matrix_two;

#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<int> &values) {
    out << "[";

    for(int value : values) 
        out << " " << value;
    
    out << ((values.empty()) ? "]" : " ]");

    return out;
}

#include <iostream>

std::ostream& operator<<(std::ostream& out, const std::vector<std::vector<int>> &values) {
    out << "[" << std::endl;

    for(std::vector<int> row : values) 
        out << "\t" << row << std::endl;

    out << "]" << std::endl;

    return out;
}

class RotateMatrixTwoTestBaseFixture :
    public testing::TestWithParam<std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>> {
protected:
    const std::vector<std::vector<int>>& GetActual() { return GetParam().first; }
    const std::vector<std::vector<int>>& GetExpected() { return GetParam().second; }
};

class RotateMatrixTwoTestNoRotationFixture : public RotateMatrixTwoTestBaseFixture {};

class RotateMatrixTwoTestRotationFixture : public RotateMatrixTwoTestBaseFixture {};

TEST_P(RotateMatrixTwoTestNoRotationFixture, NoRotation) {
    Solution solution;

    std::vector<std::vector<int>> expected(GetExpected());
    std::vector<std::vector<int>> actual(GetActual());

    std::cout << "Before" << std::endl << actual << std::endl;
    solution.rotate(actual);
    std::cout << "After" << std::endl << actual << std::endl;
    std::cout << "Expected" << std::endl << expected << std::endl;

    ASSERT_EQ(expected, actual) << "the matrix was not supposed to be rotated";
}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>> empty({},{}), onebyone({{1}}, {{1}});

INSTANTIATE_TEST_SUITE_P(NoRotation, RotateMatrixTwoTestNoRotationFixture, testing::Values( empty, onebyone ));

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
    twobytwo(
        {
            {1,2},
            {4,3}
        },
        {
            {3,4},
            {2,1}
        }),
    threebythree(
        {
            {1,2,3},
            {4,5,6},
            {7,8,9}
        },
        {
            {9,8,7},
            {6,5,4},
            {3,2,1}
        }
    ),
    fourbyfour(
        {
            {1,2,3,4},
            {5,6,7,8},
            {9,10,11,12},
            {13,14,15,16}
        },
        {
            {16,15,14,13},
            {12,11,10,9},
            {8,7,6,5},
            {4,3,2,1}
        }
    ),
    fivebyfive(
        {
            {1,2,3,4,5},
            {6,7,8,9,10},
            {11,12,13,14,15},
            {16,17,18,19,20},
            {21,22,23,24,25}
        },
        {
            {25,24,23,22,21},
            {20,19,18,17,16},
            {15,14,13,12,11},
            {10,9,8,7,6},
            {5,4,3,2,1}
        }
    ),
    sixbysix(
        {
            {1,2,3,4,5,6},
            {7,8,9,10,11,12},
            {13,14,15,16,17,18},
            {19,20,21,22,23,24},
            {25,26,27,28,29,30},
            {31,32,33,34,35,36}
        },
        {
            {36,35,34,33,32,31},
            {30,29,28,27,26,25},
            {24,23,22,21,20,19},
            {18,17,16,15,14,13},
            {12,11,10,9,8,7},
            {6,5,4,3,2,1}
        }
    );

INSTANTIATE_TEST_SUITE_P(NoRotation, RotateMatrixTwoTestRotationFixture, testing::Values(twobytwo, threebythree, fourbyfour, fivebyfive, sixbysix));

TEST_P(RotateMatrixTwoTestRotationFixture, RotationRequired) {
    Solution solution;

    std::vector<std::vector<int>> expected(GetExpected());
    std::vector<std::vector<int>> actual(GetActual());

    std::cout << "Before" << std::endl << actual << std::endl;
    solution.rotate(actual);
    std::cout << "After" << std::endl << actual << std::endl;
    std::cout << "Expected" << std::endl << expected << std::endl;

    ASSERT_EQ(expected, actual) << "the matrix was supposed to be rotated";
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}