/**
 * @file check_min_heaptests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=CheckMinHeap
 * @version 0.1
 * @date 2025-04-12
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
#include "check_min_heap.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::check_min_heap;

// Test Fixture Data Class
class CheckMinHeapData {
    std::vector<int> m_nums;
    bool m_expected;
public:
    CheckMinHeapData() = default;

    std::vector<int> const & get_nums() { return m_nums; }
    bool get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CheckMinHeapData &);
    friend std::istream& operator>>(std::istream&, CheckMinHeapData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const CheckMinHeapData & data) {
    out << "CheckMinHeapData [ nums={";
    for (int num : data.m_nums)
        out << " " << num;
    out << (data.m_nums.empty() ? "" : " ") << "} expected=" << (data.m_expected ? "true" : "false") << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, CheckMinHeapData & data, int state) {
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
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, CheckMinHeapData &data) {
    ::loaders::loader::v6::dataLoader<
        CheckMinHeapData,
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
class CheckMinHeapFixture :
    public testing::TestWithParam<CheckMinHeapData> {
};

// Parameterized Test Definition
TEST_P(CheckMinHeapFixture, CheckMinHeapTests) {
    CheckMinHeapData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.checkMinHeap(data.get_nums()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CheckMinHeapTests, CheckMinHeapFixture, testing::ValuesIn(
    Loader<CheckMinHeapData>()(find_path("heap/data/check_min_heap.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
