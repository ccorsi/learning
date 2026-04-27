/**
 * @file kth_largest_element_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2026-04-24
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
#include "kth_largest_element_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::utils::readers;
using namespace valhalla::heap::kth_largest_element_two;

class KthLargestElementTwoEntry {
    int m_input, m_k, m_expected;
public:
    KthLargestElementTwoEntry() = default;

    int get_input() { return m_input; }
    int get_k() { return m_k; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KthLargestElementTwoEntry &);

    friend struct EntryReader;
};

std::ostream& operator<<(std::ostream& out, const KthLargestElementTwoEntry & data) {
    out << "KthLargestElementTwoEntry [ k=";
    out << data.m_k << ", nextInt=" << data.m_input << ", expected=" << data.m_expected;
    out << " ]";

    return out;
}

struct EntryReader {
    KthLargestElementTwoEntry m_entry;

    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<KthLargestElementTwoEntry> & vec, int state) {
        switch (state) {
            case 0:
                in >> m_entry.m_k;
                break;
            case 1:
                in >> m_entry.m_input;
                break;
            case 2:
                in >> m_entry.m_expected;
                vec.push_back(m_entry);
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

// Test Fixture Data Class
class KthLargestElementTwoData {
    std::vector<KthLargestElementTwoEntry> m_data; 
public:
    KthLargestElementTwoData() = default;

    std::vector<KthLargestElementTwoEntry> const & get_data() { return m_data; }

    friend std::ostream& operator<<(std::ostream&, const KthLargestElementTwoData &);
    friend std::istream& operator>>(std::istream&, KthLargestElementTwoData &);

    friend struct CombinedReader;
};

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, KthLargestElementTwoData & type, int state) {
        switch (state) {
            case 0: {
                ::loaders::loader::v6::dataLoader<
                    std::vector<KthLargestElementTwoEntry>,
                    char,
                    EntryReader,
                    3,
                    ::checkers::is_character<char, '{'>,
                    ::checkers::is_character<char, '}'>,
                    ::checkers::is_space_or<','>,
                    ::checkers::is_space_or<','>
                > VectorLoader(type.m_data);
                in >> VectorLoader;
            }
            break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)
        return in;
    }
};

std::ostream& operator<<(std::ostream& out, const KthLargestElementTwoData & data) {
    out << "KthLargestElementTwoData [ input=[\n";
    for (auto & entry : data.m_data) {
        out << entry << "\n";
    } // for (auto & entry : data.m_data)
    out << " ]";
    out << " ]";

    return out;
}

std::istream& operator>>(std::istream& in, KthLargestElementTwoData &data) {
    ::loaders::loader::v6::dataLoader<
        KthLargestElementTwoData,
        char,
        CombinedReader,
        1,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class KthLargestElementTwoFixture :
    public testing::TestWithParam<KthLargestElementTwoData> {
};

// Parameterized Test Definition
TEST_P(KthLargestElementTwoFixture, KthLargestElementTwoTests) {
    KthLargestElementTwoData data = GetParam();

    Solution solution;

    for (KthLargestElementTwoEntry entry : data.get_data()) {
        int actual = solution.findKthLargest(entry.get_k(), entry.get_input()), expected = entry.get_expected();
        ASSERT_EQ(actual, expected);
    } // for (auto & entry : data.get_data())
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KthLargestElementTwoTests, KthLargestElementTwoFixture, testing::ValuesIn(
    Loader<KthLargestElementTwoData>()(find_path("heap/data/kth_largest_element_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
