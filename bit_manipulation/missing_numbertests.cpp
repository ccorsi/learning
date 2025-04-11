/**
 * @file missing_numbertests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MissingNumber
 * @version 0.1
 * @date 2025-04-04
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
#include "missing_number.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::missing_number;

// Test Fixture Data Class
class MissingNumberData {
    std::vector<int> m_nums;
    int m_expected;
public:
    MissingNumberData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MissingNumberData &);
    friend std::istream& operator>>(std::istream&, MissingNumberData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MissingNumberData & data) {
    out << "MissingNumberData [ nums={";
    for (int value : data.m_nums)
        out << " " << value;
    out << " } expectd=" << data.m_expected << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MissingNumberData & data, int state) {
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
                > DataLoader(data.m_nums);
                in >> DataLoader;
            }
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

std::istream& operator>>(std::istream& in, MissingNumberData &data) {
    ::loaders::loader::v6::dataLoader<
        MissingNumberData,
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
class MissingNumberFixture :
    public testing::TestWithParam<MissingNumberData> {
};

// Parameterized Test Definition
TEST_P(MissingNumberFixture, MissingNumberTests) {
    MissingNumberData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findMissingNumber(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MissingNumberTests, MissingNumberFixture, testing::ValuesIn(
    Loader<MissingNumberData>()(find_path("bit_manipulation/data/missing_number.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
