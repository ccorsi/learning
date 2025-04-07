/**
 * @file xor_without_xoringtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=XORWithoutXORing
 * @version 0.1
 * @date 2025-03-22
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "xor_without_xoring.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::xor_without_xoring;

// Test Fixture Data Class
class XORWithoutXORingData {
    int m_x, m_y, m_expected;
public:
    XORWithoutXORingData() = default;

    int get_x() { return m_x; }
    int get_y() { return m_y; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const XORWithoutXORingData &);
    friend std::istream& operator>>(std::istream&, XORWithoutXORingData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const XORWithoutXORingData & data) {
    return out << "XORWithoutXORingData [ x=" << data.m_x << " y=" << data.m_y
        << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, XORWithoutXORingData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_x;
                break;
            case 1:
                in >> data.m_y;
                break;
            case 2:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, XORWithoutXORingData &data) {

    ::loaders::loader::v6::dataLoader<
        XORWithoutXORingData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class XORWithoutXORingFixture :
    public testing::TestWithParam<XORWithoutXORingData> {
};

// Parameterized Test Definition
TEST_P(XORWithoutXORingFixture, XORWithoutXORingTests) {
    XORWithoutXORingData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findXOR(data.get_x(), data.get_y()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(XORWithoutXORingTests, XORWithoutXORingFixture, testing::ValuesIn(
    Loader<XORWithoutXORingData>()(find_path("bit_manipulation/data/xor_without_xoring.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
