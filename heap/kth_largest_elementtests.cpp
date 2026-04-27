/**
 * @file kth_largest_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2026-04-23
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
#include "kth_largest_element.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::kth_largest_element;

// Test Fixture Data Class
class KthLargestElementData {
    std::vector<int> m_input;
    int m_k, m_expected;
public:
    KthLargestElementData() = default;

    std::vector<int> const & get_input() { return m_input; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KthLargestElementData &);
    friend std::istream& operator>>(std::istream&, KthLargestElementData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const KthLargestElementData & data) {
    out << "KthLargestElementData [ input=[";
    for (auto & value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << data.m_expected;
    out << " ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, KthLargestElementData & data, int state) {
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
                > DataLoader(data.m_input);
                in >> DataLoader;
            }
            break;
            case 1:
                in >> data.m_k;
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

std::istream& operator>>(std::istream& in, KthLargestElementData &data) {
    ::loaders::loader::v6::dataLoader<
        KthLargestElementData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;
    return in;
}

// Test Fixture Class
class KthLargestElementFixture :
    public testing::TestWithParam<KthLargestElementData> {
};

// Parameterized Test Definition
TEST_P(KthLargestElementFixture, KthLargestElementTests) {
    KthLargestElementData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.findKthLargest(data.get_input(), data.get_k()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KthLargestElementTests, KthLargestElementFixture, testing::ValuesIn(
    Loader<KthLargestElementData>()(find_path("heap/data/kth_largest_element.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
