/**
 * @file decimal_to_binarytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=DecimalToBinary
 * @version 0.1
 * @date 2025-03-18
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
#include "decimal_to_binary.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::decimal_to_binary;

// Test Fixture Data Class
class DecimalToBinaryData {
    int m_n;
    std::string m_expected;
public:
    DecimalToBinaryData() = default;

    int get_n() { return m_n; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const DecimalToBinaryData &);
    friend std::istream& operator>>(std::istream&, DecimalToBinaryData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const DecimalToBinaryData & data) {
    return out << "DecimalToBinaryData [ n=" << data.m_n << " expected=\"" << data.m_expected << "\"  ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, DecimalToBinaryData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                {
                    ::loaders::loader::v6::dataLoader<
                        std::string,
                        char,
                        StringReader,
                        1,
                        ::checkers::is_character<char, '"'>,
                        ::checkers::is_character<char, '"'>,
                        ::checkers::is_space_or<','>,
                        ::checkers::is_space_noop<char>
                    > StringLoader(data.m_expected);
                    in >> StringLoader;
                }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, DecimalToBinaryData &data) {
    ::loaders::loader::v6::dataLoader<
        DecimalToBinaryData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class DecimalToBinaryFixture :
    public testing::TestWithParam<DecimalToBinaryData> {
};

// Parameterized Test Definition
TEST_P(DecimalToBinaryFixture, DecimalToBinaryTests) {
    DecimalToBinaryData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.toBinary(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(DecimalToBinaryTests, DecimalToBinaryFixture, testing::ValuesIn(
    Loader<DecimalToBinaryData>()(find_path("bit_manipulation/data/decimal_to_binary.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
