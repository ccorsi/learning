/**
 * @file generatortests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different tests associated with the dynamic test data generators
 * @version 0.1
 * @date 2025-04-16
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <random>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "generator.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::utils::generator;

// Test Fixture Data Class
class GeneratorData {
    std::vector<int> m_nums, m_expected;
public:
    GeneratorData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    std::vector<int> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const GeneratorData &);
    friend std::istream& operator>>(std::istream&, GeneratorData &);

    GeneratorData & operator()();
};

std::vector<std::pair<std::vector<int>,std::vector<int>>> g_inputs;
int g_idx = 0;

std::random_device rd;
std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> ndistrib(1,2000/*INT_MIN, INT_MAX*/), sdistrib(5, 25);

/**
 * @brief This operator is used to generate a new GeneratorData instance that will be
 *      passed to the container used for the tests.  It is assumed that the returned
 *      instance will be copied to its destination such that this instance can generate
 *      another unique instance.
 * 
 * @return GeneratorData& A reference to the update GeneratorData instance of this.
 */
GeneratorData & GeneratorData::operator()() {
    int size = sdistrib(gen); // generate the size of the array.
    std::pair<std::vector<int>,std::vector<int>> input; // create a temporary pair to store entries

    // populate the pair
    while (size-- > 0) {
        input.first.push_back(ndistrib(gen));
        input.second.push_back(ndistrib(gen));
    } // while (size-- > 0)

    input.second = input.first;

    std::make_heap(input.first.begin(), input.first.end());
    std::make_heap(input.second.begin(), input.second.end(), [](int & lhs, int & rhs) { return lhs > rhs; });
    
    // save the pair to compare the result of the test
    g_inputs.push_back(input);

    // assign the generated vectors to its private fields
    m_nums = input.first;
    m_expected = input.second;

    return *this;
};

std::ostream& operator<<(std::ostream& out, const GeneratorData & data) {
    out << "GeneratorData [ nums={";
    for (int value : data.m_nums)
        out << " " << value;
    out << (data.m_nums.empty() ? "" : " ") << "} expected={";
    for (int value : data.m_expected)
        out << " " << value;
    out << (data.m_expected.empty() ? "" : " ") << "} ]";

    return out;
}

// Test Fixture Class
class GeneratorVectorFixture :
    public testing::TestWithParam<GeneratorData> {
};

// Parameterized Test Definition
TEST_P(GeneratorVectorFixture, GeneratorVectorTests) {
    GeneratorData data = GetParam();

    auto & expected = g_inputs[g_idx++];

    EXPECT_EQ(data.get_nums(), expected.first);
    EXPECT_EQ(data.get_expected(), expected.second);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(GeneratorVectorTests, GeneratorVectorFixture, testing::ValuesIn(
    container_generator<std::vector<GeneratorData>>()(100)
));

template<typename Type = int,
Type Start = 1
>
class data_generator {
    Type m_count = Start;
    GeneratorData m_allocator;
public:
    data_generator() = default;

    std::pair<Type,GeneratorData> operator()() {
        return std::pair<Type,GeneratorData>(m_count++, m_allocator());
    }

    Type counter() { return m_count; }
};

TEST(GeneratorTestSuite, MapGenerator) {
    constexpr int SIZE = 100;
    std::map<int,GeneratorData> data =
        map_generator<
            std::map<int,GeneratorData>,
            int,
            GeneratorData,
            data_generator<>
        >()(SIZE);

    for (auto & value : data) {
        std::cout << "key: " << value.first << ", value: " << value.second << '\n';
    }

    for (int value = 1 ; value < SIZE + 1 ; value++) {
        EXPECT_NE(data.find(value), data.end());
    }

    ASSERT_EQ(data.size(), SIZE);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
