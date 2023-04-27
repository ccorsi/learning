/**
 * @file primitiveLoadertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the primitiveLoader template
 * @version 0.1
 * @date 2023-04-14
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <sstream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "primitive_loader.h"

using namespace valhalla::utils::loaders::primitive;
using namespace valhalla::utils::checkers;

// Test Fixture Class
class PrimitiveLoaderFixture :
    public testing::Test {
};

// Test Fixture Definition
TEST_F(PrimitiveLoaderFixture, PrimitiveLoaderIntTest) {
    std::stringstream in;

    in << "      100       101    ";
    int value = 0;
    primitiveLoader<int, char, is_space> loader(&value);

    EXPECT_EQ(value, 0);
    in >> loader;
    EXPECT_EQ(value, 100);

    int other = -1;

    loader.set_reference(&other);

    EXPECT_EQ(other, -1);
    in >> loader;
    EXPECT_EQ(other, 101);

    // std::cout << "value: " << value << ", other: " << other << std::endl;

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
