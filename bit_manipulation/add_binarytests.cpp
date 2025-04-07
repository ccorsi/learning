/**
 * @file add_binarytests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains the tests to the problem https://www.techiedelight.com/?problem=AddBinary
 * @version 0.1
 * @date 2025-03-18
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
#include "add_binary.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::bit_manipulation::add_binary;

// Test Fixture Data Class
class AddBinaryData {
    int m_x, m_y;
    std::string m_expected;
public:
    AddBinaryData() = default;

    int get_x() { return m_x; }
    int get_y() { return m_y; }
    std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const AddBinaryData &);
    friend std::istream& operator>>(std::istream&, AddBinaryData &);

    friend struct CombinedReader;
};

std::ostream& operator<<(std::ostream& out, const AddBinaryData & data) {
    return out << "AddBinaryData [ x=" << data.m_x << " y=" << data.m_y
        << " expected=\"" << data.m_expected << "\"  ]";
}

struct CombinedReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, AddBinaryData & data, int state) {
        switch (state) {
            case 0:
                in >> data.m_x;
                break;
            case 1:
                in >> data.m_y;
                break;
            case 2:
                {
                    ::loaders::loader::v6::dataLoader<
                        std::string,
                        char,
                        StringReader,
                        1,
                        ::checkers::is_character<char, '"'>,
                        ::checkers::is_character<char, '"'>,
                        ::checkers::is_space_or<','>,
                        ::checkers::is_space_noop<char>
                    > StringLoader(data.m_expected);
                    in >> StringLoader;
                }
                break;
            default:
                throw std::runtime_error("INVALID STATE");
        } // switch (state)

        return in;
    }
};

std::istream& operator>>(std::istream& in, AddBinaryData &data) {
    ::loaders::loader::v6::dataLoader<
        AddBinaryData,
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
class AddBinaryFixture :
    public testing::TestWithParam<AddBinaryData> {
};

// Parameterized Test Definition
TEST_P(AddBinaryFixture, AddBinaryTests) {
    AddBinaryData data = GetParam();

    Solution solution;

    ASSERT_EQ(solution.add(data.get_x(), data.get_y()), data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(AddBinaryTests, AddBinaryFixture, testing::ValuesIn(
    Loader<AddBinaryData>()(find_path("bit_manipulation/data/add_binary.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
