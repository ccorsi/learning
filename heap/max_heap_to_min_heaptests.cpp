/**
 * @file max_heap_to_min_heaptests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem 
 * @version 0.1
 * @date 2025-04-12
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <queue>
#include <algorithm>
#include <functional>
#include <random>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "max_heap_to_min_heap.h"
#include "generator.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::heap::max_heap_to_min_heap;
using namespace valhalla::utils::generator;

// Test Fixture Data Class
class MaxHeapToMinHeapData {
    std::vector<int> m_nums;
public:
    MaxHeapToMinHeapData() = default;
    MaxHeapToMinHeapData(std::vector<int> & nums) : m_nums(nums) {}

    std::vector<int> const & get_nums() { return m_nums; }

    friend std::ostream& operator<<(std::ostream&, const MaxHeapToMinHeapData &);
    friend std::istream& operator>>(std::istream&, MaxHeapToMinHeapData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const MaxHeapToMinHeapData & data) {
    out << "MaxHeapToMinHeapData [ nums={";
    for (int value : data.m_nums)
        out << " " << value;
    out << (data.m_nums.empty() ? "" : " ") << "} ]";

    return out;
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, MaxHeapToMinHeapData & data, int state) {
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
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, MaxHeapToMinHeapData &data) {
    ::loaders::loader::v6::dataLoader<
        MaxHeapToMinHeapData,
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
class MaxHeapToMinHeapFixture :
    public testing::TestWithParam<MaxHeapToMinHeapData> {
};

std::string PrintHeapToString(const std::vector<int> & arg) {
    std::vector<int> heap(arg.begin(),arg.end());
    std::make_heap(heap.begin(), heap.end(), std::greater<>{});
    return ::testing::PrintToString(heap);
};

MATCHER_P(IsMinHeap, heap, PrintHeapToString(heap)) {
    const std::vector<int>::size_type size = arg.size();
    std::queue<std::vector<int>::size_type> entries;
    entries.push(0);

    while (entries.empty() == false) {
        std::vector<int>::size_type root = entries.front(); entries.pop();
        const std::vector<int>::size_type left = 2 * root + 1, right = 2 * root + 2;
        if (left < arg.size()) {
            if (arg[root] > arg[left]) {
                *result_listener << "\nEntry value '" << arg[root] << "' is not less than or equal to entry value '" << arg[left]
                    << "' at indexes [" << root << "," << left << "]";
                return false;
            } // if (arg[root] > arg[left])
            entries.push(left);
            if (right < arg.size()) {
                entries.push(right);
                if (arg[root] > arg[right]) {
                    *result_listener << "\nEntry value '" << arg[root] << "' is not less than or equal to entry value '" << arg[right]
                        << "' at indexes [" << root << "," << right << "]";
                    return false;
                } // if (arg[root] > arg[right])
            } // if (right < arg.size())
        } // if (left < arg.size())
    } // while (entries.empty() == false)

    return true;
} // IsMinHeap

std::random_device rd;
std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> ndistrib(/*from=*/-99,/*to=*/99/*INT_MIN, INT_MAX*/), sdistrib(/*from=*/10, /*to=*/15);

std::vector<MaxHeapToMinHeapData> generate() {
    std::vector<MaxHeapToMinHeapData> data,
        file_data = Loader<MaxHeapToMinHeapData>()(find_path("heap/data/max_heap_to_min_heap.txt"));

    // add the entries from the file data to the return data vector
    data.insert(data.cbegin(), file_data.begin(), file_data.end());

    for(int idx = 0, size = sdistrib(gen) ; idx < size ; idx++) {
        std::vector<int> gen_data;
        for (int cnt = 0, tot = sdistrib(gen) ; cnt < tot ; cnt++) {
            gen_data.push_back(ndistrib(gen));
        }
        std::make_heap(gen_data.begin(), gen_data.end(), std::less<int>());
        data.push_back(MaxHeapToMinHeapData(gen_data));
    }

    return data;
} // generate()

// Parameterized Test Definition
TEST_P(MaxHeapToMinHeapFixture, MaxHeapToMinHeapTests) {
    MaxHeapToMinHeapData data = GetParam();

    Solution solution;

    std::vector<int> nums = data.get_nums();

    solution.convert(nums);

    ASSERT_THAT(nums, IsMinHeap(data.get_nums()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MaxHeapToMinHeapTests, MaxHeapToMinHeapFixture, testing::ValuesIn(
    generate()
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
