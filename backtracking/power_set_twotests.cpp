/**
 * @file power_set_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=PowerSetII
 * @version 0.1
 * @date 2025-04-03
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
#include "power_set_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::backtracking::power_set_two;

// Test Fixture Data Class
class PowerSetTwoData {
    std::vector<int> m_S;
    std::vector<std::vector<int>> m_expected;
public:
    PowerSetTwoData() = default;

    std::vector<int> get_S() { return m_S; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const PowerSetTwoData &);
    friend std::istream& operator>>(std::istream&, PowerSetTwoData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const PowerSetTwoData & data) {
    out << "PowerSetTwoData [ S={";
    for (auto & value : data.m_S)
        out << " " << value;
    out << (data.m_S.empty() ? "" : " ") << "} expected={ ";
    for (auto & s : data.m_expected) {
        out << "{";
        for (auto & value : s)
            out << " " << value;
        out << (s.empty() ? "" : " ") << "} ";
    }
    out << "} ]";

    return out;
}

template<typename Type>
struct VecReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<Type> & vec, int state) {
        switch (state) {
            case 0: {
                Type value;
                in >> value;
                vec.push_back(value);
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & vecvec, int state) {
        switch (state) {
            case 0: {
                std::vector<int> vec;
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VecReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > VectorLoader(vec);
                in >> VectorLoader;

                std::sort(vec.begin(),vec.end());

                vecvec.push_back(vec);
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, PowerSetTwoData & data, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<int>,
                    char,
                    VecReader<int>,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > VecLoader(data.m_S);
                in >> VecLoader;
            }
                break;
            case 1: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<std::vector<int>>,
                    char,
                    VectorVectorReader,
                    1,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > VectorVectorLoader(data.m_expected);
                in >> VectorVectorLoader;
            }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, PowerSetTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        PowerSetTwoData,
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
class PowerSetTwoFixture :
    public testing::TestWithParam<PowerSetTwoData> {
};

bool cmp(std::vector<int> & ls, std::vector<int> & rs) {
    if (ls.size() == rs.size()) {
        for (size_t idx = 0, size = ls.size() ; idx < size ; idx++) {
            if (ls[idx] == rs[idx]) continue;
            return ls[idx] < rs[idx];
        } // for (size_t idx = 0, size = ls.size() ; idx < size ; idx++)
        return false;
    } // if (ls.size() == rs.size())

    return ls.size() < rs.size();
}

// Parameterized Test Definition
TEST_P(PowerSetTwoFixture, PowerSetTwoTests) {
    PowerSetTwoData data = GetParam();

    Solution solution;

    auto S = data.get_S();

    auto actual = solution.findPowerSet(S);
    auto expected = data.get_expected();

    for (auto & vec : actual) {
        std::sort(vec.begin(), vec.end());
    } // for (auto & vec : actual)

    std::sort(actual.begin(), actual.end(), cmp);

    for (auto & vec : expected) {
        std::sort(vec.begin(), vec.end());
    } // for (auto & vec : actual)

    std::sort(expected.begin(), expected.end(), cmp);

    ASSERT_EQ(actual, expected);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(PowerSetTwoTests, PowerSetTwoFixture, testing::ValuesIn(
    Loader<PowerSetTwoData>()(find_path("backtracking/data/power_set_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
