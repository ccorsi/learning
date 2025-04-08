/**
 * @file circular_shifttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=CircularShift
 * @version 0.1
 * @date 2025-03-19
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>
#include <bitset>
#include <random>
#include <limits>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "readers.h"
#include "circular_shift.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::circular_shift;

// Test Fixture Data Class
class CircularShiftData {
    int m_n, m_k, m_expected;
    bool m_isLeftShift;
public:
    CircularShiftData() = default;

    int get_n() { return m_n; }
    int get_k() { return m_k; }
    bool get_isLeftShift() { return m_isLeftShift; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const CircularShiftData &);
    friend std::istream& operator>>(std::istream&, CircularShiftData &);

    friend struct CombinedReader;

    CircularShiftData& operator()();

    friend struct CircularShiftDataHash;

    // bool operator==(const CircularShiftData & other) const {
    //     return m_n == other.m_n && m_k == other.m_k && m_isLeftShift == other.m_isLeftShift;
    // }

    // friend bool operator<(const CircularShiftData & lhs, const CircularShiftData & rhs) {
    //     if (lhs.m_isLeftShift == rhs.m_isLeftShift) {
    //         if (lhs.m_n == rhs.m_n) {
    //             return lhs.m_k < rhs.m_k;
    //         } // if (lhs.m_n == rhs.m_n)

    //         return lhs.m_n < rhs.m_n;
    //     } // if (lhs.m_isLeftShift == rhs.m_isLeftShift)

    //     return lhs.m_isLeftShift < rhs.m_isLeftShift;
    // }

    // friend bool operator==(const CircularShiftData & lhs, const CircularShiftData & rhs) {
    //     return lhs.m_n == rhs.m_n && lhs.m_k == rhs.m_k && lhs.m_isLeftShift == rhs.m_isLeftShift;
    // }
};

struct CircularShiftDataHash {
    std::size_t operator()(const CircularShiftData & data) const {
        std::size_t m_n_hash = std::hash<int>()(data.m_n),
            m_k_hash = std::hash<int>()(data.m_k),
            m_expected_hash = std::hash<bool>()(data.m_expected);

        return m_n_hash ^ (m_k_hash << 1) ^ (m_expected_hash >> 1);
    }
};

std::random_device rd;
std::mt19937 gen(rd()); // mersenne_twister_engine seeded with rd()
std::uniform_int_distribution<> ndistrib(INT_MIN, INT_MAX), kdistrib(0, sizeof(int) * 8), bdistrib(0,1);

CircularShiftData& CircularShiftData::operator()() {
    m_n = ndistrib(gen);
    m_k = kdistrib(gen);
    m_isLeftShift = bdistrib(gen);
    if (m_k > 0) {
        const int bits = sizeof(int) * 8;
        int lshift, rshift;
        if (m_isLeftShift) {
            lshift = bits - m_k;
            rshift = m_k;
        } else {
            lshift = m_k;
            rshift = bits - m_k;
        } // if (m_isLeftShift)
        // create a left mask to purge possible 1's that are added on the right side of the integer when shifting right
        int lmask = 0;
        for (int count = rshift ; count > 0 ; count--) {
            lmask <<= 1;
            lmask += 1;
        } // for (int count = rshift ; count > 0 ; count--)
        m_expected = (((m_n >> lshift) & lmask) | (m_n << rshift));
        // TODO: Get the correct manipulation for this conversion
        // m_expected = ((m_n >> lshift) ^ (-1 << (bits - m_k))) | (m_n << rshift);
        // int mask = 0x1;
        // for (int k = m_k ; --k > 0 ; ) {
        //     mask <<= 1;
        //     mask |= 0x1;
        // } // for (int k = m_k ; --k > 0 ; )
        // if (m_isLeftShift) {
        //     int value = (m_n & mask) >> (sizeof(int) * 8 - m_k);
        //     m_expected = (m_n << m_k) | value;
        // } else {
        //     int value = (m_n & mask) << (sizeof(int) * 8 - m_k);
        //     m_expected = (m_n >> m_k) | value;
        // } // if (m_isLeftShift)
    } else {
        m_expected = m_n;
    } // if (m_k > 0)

    return *(this);
}

std::ostream& operator<<(std::ostream& out, const CircularShiftData & data) {
    return out << "CircularShiftData [ n=" << std::bitset<sizeof(int) * 8>(data.m_n) << " k=" << data.m_k
        << " isLeftShift=" << (data.m_isLeftShift ? "true" : "false") << " expected="
        << std::bitset<sizeof(int) * 8>(data.m_expected) << " ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, CircularShiftData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_n;
                break;
            case 1:
                in >> data.m_k;
                break;
            case 2:
                in >> data.m_isLeftShift;
                break;
            case 3:
                in >> data.m_expected;
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

/**
 * @brief This template is used to generate a vector container with elements of
 *  typename Type.
 *
 * @tparam Type This is the element type that is part of the vector container
 */
template<typename Type>
class ElementContainerGenerator {
public:
    ElementContainerGenerator() = default;

    /**
     * @brief This operator will generate a vector container with the number
     *      of elements passed.
     *
     * @param count The expected number of elements contained in the returned
     *      vector container
     * @return std::vector<Type> The container containing the expected number of
     *      entries.
     */
     std::vector<Type> operator()(int count) {
        std::vector<Type> container;

        while (count-- > 0) {
            Type element;

            container.push_back(element());
        } // while (count-- > 0)

        return container;
    }
};

#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <type_traits>

/**
 * @brief This is the default class that will be used to allocate an instance
 *      using the instance Type operator()().
 *
 * @tparam Type The class type that will be return by this class Type operator()() operator
 */
template<typename Type>
class ElementAllocator {
    Type m_generator;
public:
    ElementAllocator() = default;

    Type & operator()() {
        return m_generator();
    }
};

template<typename Container,
    typename Type = typename Container::value_type,
    typename Allocator = ElementAllocator<Type>
>
class ContainerGenerator {
public:
    ContainerGenerator() = default;

    Container operator()(int count) {
        Container container;
        Allocator allocator;

        while (count-- > 0) {

            if constexpr (std::is_same_v<Container, std::vector<Container::value_type>> ||
                std::is_same_v<Container, std::deque<Container::value_type>> ||
                std::is_same_v<Container, std::list<Container::value_type>>) {
                container.push_back(allocator());
            } else if constexpr (std::is_same_v<Container, std::forward_list<Container::value_type>>) {
                container.push_front(allocator());
            } else if constexpr (std::is_same_v<Container, std::set<Container::value_type>> ||
                std::is_same_v<Container, std::unordered_set<Container::value_type>>) {
                container.insert(allocator());
            }
        } // while (count-- > 0)

        return container;
    }
};

class Log {
    std::string m_block;
public:
    Log(std::string block) : m_block(block) {
        std::cout << "Entering " << block << "\n";
    }
    ~Log() {
        std::cout << "Exiting " << m_block << "\n";
    }
};

template<typename Container,
    typename Allocator = ElementAllocator<Container::value_type>
>
Container populate_container(int count) {
    // Log log("populate_container");
    ContainerGenerator<Container, Container::value_type, Allocator> generator;

    return generator(count);
}

auto vector_container = populate_container<std::vector<CircularShiftData>>(10);
auto deque_container = populate_container<std::deque<CircularShiftData>>(10);
auto list_container = populate_container<std::list<CircularShiftData>>(10);
auto forward_list_container = populate_container<std::forward_list<CircularShiftData>>(10);

template<int count>
class CircularShiftDataAllocator {
    int m_count = count;
public:
    CircularShiftDataAllocator() = default;

    CircularShiftData & operator()() {
        CircularShiftData element;

        std::cout << "Created element: " << element() << '\n';

        return element;
    }
};

auto aset_container = populate_container<std::set<CircularShiftData, CircularShiftDataHash>, CircularShiftDataAllocator<10>>(10);
auto aunordered_set_container = populate_container<std::unordered_set<CircularShiftData, CircularShiftDataHash>, CircularShiftDataAllocator<10>>(10);

std::unordered_set<CircularShiftData, CircularShiftDataHash> acontainer;

template<int count>
class int_generator {
    int m_count = count;
public:
    int_generator() = default;

    int operator()() {
        // std::cout << "Returning integer value " << m_count << "\n";
        return m_count--;
    }
};

auto set_container = populate_container<std::set<int>, int_generator<10>>(10);
auto unordered_set_container = populate_container<std::unordered_set<int>, int_generator<10>>(10);

int testme() {
    for (CircularShiftData data : ElementContainerGenerator<CircularShiftData>()(10)) {
        // std::cout << data << '\n';
    }
    return 0;
}

auto container = testme();

std::istream& operator>>(std::istream& in, CircularShiftData &data) {
    ::loaders::loader::v6::dataLoader<
        CircularShiftData,
        char,
        CombinedReader,
        4,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
}

// Test Fixture Class
class CircularShiftFixture :
    public testing::TestWithParam<CircularShiftData> {
};

// Parameterized Test Definition
TEST_P(CircularShiftFixture, CircularShiftTests) {
    CircularShiftData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.circularShift(data.get_n(), data.get_k(), data.get_isLeftShift()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(CircularShiftTests, CircularShiftFixture, testing::ValuesIn(
    Loader<CircularShiftData>()(find_path("bit_manipulation/data/circular_shift.txt"))
    // ElementContainerGenerator<CircularShiftData>()(1000)
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
