/**
 * @file missing_number_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MissingNumberIII
 * @version 0.1
 * @date 2025-04-08
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
#include "missing_number_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::missing_number_three;

// Test Fixture Data Class
class MissingNumberThreeData {
    std::vector<int> m_nums;
    int m_expected;
public:
    MissingNumberThreeData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MissingNumberThreeData &);
    friend std::istream& operator>>(std::istream&, MissingNumberThreeData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MissingNumberThreeData & data) {
    out << "MissingNumberThreeData [ nums={";
    for (int num : data.m_nums)
        out << " " << num;
    out << (data.m_nums.empty() ? "" : " ") << "} expected=" << data.m_expected << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MissingNumberThreeData & data, int state) {
        switch (state) {
        case 0: {
            ::loaders::loader::v6::dataLoader<
                std::vector<int>,
                char,
                VectorReader<int>,
                1,
                ::checkers::is_character<char, '{'>,
                ::checkers::is_character<char, '}'>,
                ::checkers::is_space_or<','>,
                ::checkers::is_space_or<','>
            > VectorLoader(data.m_nums);
            in >> VectorLoader;
        }
            break;
        case 1:
            in >> data.m_expected;
            break;
        default:
            throw std::runtime_error("INVALID STATE");
        } // switch

        return in;
    }
};

std::istream& operator>>(std::istream& in, MissingNumberThreeData &data) {
    ::loaders::loader::v6::dataLoader<
        MissingNumberThreeData,
        char,
        CombinedReader,
        2,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class MissingNumberThreeFixture :
    public testing::TestWithParam<MissingNumberThreeData> {
};

// Parameterized Test Definition
TEST_P(MissingNumberThreeFixture, MissingNumberThreeTests) {
    MissingNumberThreeData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMissingNumber(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MissingNumberThreeTests, MissingNumberThreeFixture, testing::ValuesIn(
    Loader<MissingNumberThreeData>()(find_path("bit_manipulation/data/missing_number_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
