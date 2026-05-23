/**
 * @file connect_n_ropestests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=ConnectNRopes
 * @version 0.1
 * @date 2026-05-22
 *
 * @copyright Copyright (c) 2026 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "connect_n_ropes.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::connect_n_ropes;

// Test Fixture Data Class
class ConnectNRopesData {
    std::vector<int> m_input;
    int m_expected;
public:
    ConnectNRopesData() = default;

    std::vector<int> get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ConnectNRopesData &);
    friend std::istream& operator>>(std::istream&, ConnectNRopesData &);

    friend struct CombinedReader;
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, ConnectNRopesData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VectorReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>
                > VectorLoader(data.m_input);
                in >> VectorLoader;
            }
            break;
            case 1:
                in >>  data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::ostream& operator<<(std::ostream& out, const ConnectNRopesData & data) {
    out << "ConnectNRopesData [ input=[";
    for (auto & value : data.m_input) {
        out << " " << value;
    } // for (auto & value : data.m_input)
    out << " ], expected=" << data.m_expected;
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, ConnectNRopesData &data) {
    ::loaders::loader::v5::dataLoader<
        ConnectNRopesData,
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
class ConnectNRopesFixture :
    public testing::TestWithParam<ConnectNRopesData> {
};

// Parameterized Test Definition
TEST_P(ConnectNRopesFixture, ConnectNRopesTests) {
    ConnectNRopesData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMinCost(data.get_input()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ConnectNRopesTests, ConnectNRopesFixture, testing::ValuesIn(
    Loader<ConnectNRopesData>()(find_path("heap/data/connect_n_ropes.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
