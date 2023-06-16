/**
 * @file matrix_path_fourtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=MatrixPathIV
 * @version 0.1
 * @date 2023-06-16
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loaders.h"
#include "matrix_path_four.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::matrix_path_four;

// Test Fixture Data Class
class MatrixPathFourData {
    std::vector<std::vector<int>> m_input;
    std::set<std::vector<int>> m_expected;
public:
    MatrixPathFourData() = default;

    std::vector<std::vector<int>> const & get_input() { return m_input; }
    std::set<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const MatrixPathFourData &);
    friend std::istream& operator>>(std::istream&, MatrixPathFourData &);

};

std::ostream& operator<<(std::ostream& out, const MatrixPathFourData & data) {
    out << "MatrixPathFourData [ input=[";
    for (std::vector<int> values : data.m_input) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] expected={";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

struct VectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<int> & vec, int state) {
        int entry;

        ::loaders::loader::v4::dataLoader<
            int,
            char,
            loader::v4::reader<int,char>,
            1,
            ::checkers::is_character_noop<char>,
            ::checkers::is_no_character<char>,
            ::checkers::is_space_or<','>
        > inputLoader(entry);
        in >> inputLoader;

        vec.push_back(entry);

        return in;
    }
};

struct VectorVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<int>> & type, int state) {
        std::vector<int> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<int>,
            char,
            VectorReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > inputLoader(entry);
        in >> inputLoader;

        type.push_back(entry);
        return in;
    }
};

struct SetVectorReader {
    std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::set<std::vector<int>> & container, int state) {
        std::vector<int> entry;

        ::loaders::loader::v4::dataLoader<
            std::vector<int>,
            char,
            VectorReader,
            1,
            ::checkers::is_character<char,'['>,
            ::checkers::is_character<char,']'>,
            ::checkers::is_space_or<','>
        > inputLoader(entry);
        in >> inputLoader;

        container.insert(entry);

        return in;
    }
};

std::istream& operator>>(std::istream& in, MatrixPathFourData &data) {
    ::loaders::loader::v4::dataLoader<
      std::vector<std::vector<int>>,
      char,
      VectorVectorReader,
      1,
      ::checkers::is_character<char,'['>,
      ::checkers::is_character<char,']'>,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
      std::set<std::vector<int>>,
      char,
      SetVectorReader,
      1,
      ::checkers::is_character<char,'{'>,
      ::checkers::is_character<char,'}'>,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class MatrixPathFourFixture :
    public testing::TestWithParam<MatrixPathFourData> {
};

// Parameterized Test Definition
TEST_P(MatrixPathFourFixture, MatrixPathFourTests) {
    MatrixPathFourData data = GetParam();

    Solution solution;

    std::set<std::vector<int>> actual = solution.findAllPaths(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(MatrixPathFourTests, MatrixPathFourFixture, testing::ValuesIn(
    Loader<MatrixPathFourData>()(find_path("matrices/data/matrix_path_four.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
