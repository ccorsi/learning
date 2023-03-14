/**
 * @file matrixloadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the matrix loader template class
 * @version 0.1
 * @date 2023-03-08
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <sstream>

#include "matrix_loader.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace valhalla::utils::loaders::matrix;

TEST(MatrixLoaderTestSuite, MatrixLoaderTest) {
    std::vector<std::vector<int>> actual;
    matrixLoader<int> loader(actual, '[', ']');

    std::istringstream in("[\n[1 2 3 4]\n]\n");

    in >> loader;

    std::vector<std::vector<int>> expected = {
        {1 , 2, 3, 4}
    };

    ASSERT_EQ(actual, expected);
}

TEST(MatrixLoaderTestSuite, MatrixLoaderExtractSpacesTest) {
    std::vector<std::vector<int>> actual;
    matrixLoader<int> loader(actual, '[', ']');

    std::istringstream in(" [\n [   1    2 3 4]  \n ] \n");

    in >> loader;

    std::vector<std::vector<int>> expected = {
        {1 , 2, 3, 4}
    };

    ASSERT_EQ(actual, expected);
}

TEST(MatrixLoaderTestSuite, MatrixLoaderEmptyMatrixTest) {
    std::vector<std::vector<int>> actual;
    matrixLoader<int> loader(actual, '[', ']');

    std::istringstream in(" [\n [    ]  \n ] \n");

    in >> loader;

    std::vector<std::vector<int>> expected = {
        {}
    };

    ASSERT_EQ(actual, expected);
}

TEST(MatrixLoaderTestSuite, MatrixLoaderTwoByTwoTest) {
    std::vector<std::vector<int>> actual;
    matrixLoader<int> loader(actual, '[', ']');

    std::istringstream in("[\n[1 2 3 4]\n[5 6 7 8]\n]\n");

    in >> loader;

    std::vector<std::vector<int>> expected = {
        {1 , 2, 3, 4}, {5, 6, 7, 8}
    };

    ASSERT_EQ(actual, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
