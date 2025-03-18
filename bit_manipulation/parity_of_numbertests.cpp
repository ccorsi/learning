/**
 * @file parity_of_numbertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=ParityOfNumber
 * @version 0.1
 * @date 2025-03-12
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
#include "parity_of_number.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::parity_of_number;

// Test Fixture Data Class
class ParityOfNumberData {
    int m_n;
    bool m_expected;
public:
    ParityOfNumberData() = default;

    int get_n() { return m_n; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ParityOfNumberData &);
    friend std::istream& operator>>(std::istream&, ParityOfNumberData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const ParityOfNumberData & data) {
    return out << "ParityOfNumberData [ n=" << data.m_n << " expected=" << data.m_expected << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ParityOfNumberData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)
        return in;
    }
};

std::istream& operator>>(std::istream& in, ParityOfNumberData &data) {
    ::loaders::loader::v6::dataLoader<
        ParityOfNumberData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    return in >> DataLoader;
}

// Test Fixture Class
class ParityOfNumberFixture :
    public testing::TestWithParam<ParityOfNumberData> {
};

// Parameterized Test Definition
TEST_P(ParityOfNumberFixture, ParityOfNumberTests) {
    ParityOfNumberData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findParity(data.get_n()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ParityOfNumberTests, ParityOfNumberFixture, testing::ValuesIn(
    Loader<ParityOfNumberData>()(find_path("bit_manipulation/data/parity_of_number.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
