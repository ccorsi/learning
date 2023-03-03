/**
 * @file search_matrix_twotests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=SearchMatrixII
 * @version 0.1
 * @date 2023-03-03
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <stdexcept>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "paths.h"
#include "loader.h"
#include "search_matrix_two.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::search_matrix_two;

// Test Fixture Data Class
class SearchMatrixTwoData {
    std::vector<std::vector<char>> m_input;
    std::string m_word;
    std::set<std::vector<std::pair<int,int>>> m_expected;
public:
    SearchMatrixTwoData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    std::string const & get_word() { return m_word; }
    std::set<std::vector<std::pair<int,int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const SearchMatrixTwoData &);
    friend std::istream& operator>>(std::istream&, SearchMatrixTwoData &);

};

std::ostream& operator<<(std::ostream& out, const SearchMatrixTwoData & data) {
    out << "SearchMatrixTwoData [ input=[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char value : values)
            out << " " << value;
        out << " ]";
    } // for
    out << " ] word=\"" << data.m_word << "\" expected=[";
    for(std::vector<std::pair<int,int>> points : data.m_expected) {
        out << " [";
        for (std::pair<int,int> point : points)
            out << " (" << point.first << "," << point.second << ")";
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

std::istream& operator>>(std::istream& in, SearchMatrixTwoData &data) {
    matrixLoader<char> loader(data.m_input);
    in >> loader;
    std::getline(in, data.m_word); // read the word line
    // std::cout << "word: " << data.m_word << std::endl;
    if (static_cast<char>(in.peek()) == '{') {
        std::string line;
        std::getline(in, line); // read the '{' line
        // std::cout << "line: " << line << std::endl;
        while (static_cast<char>(in.peek()) != '}') {
            if (static_cast<char>(in.peek()) != '[') {
                // std::cout << "1 - Invalid input format" << std::endl;
                throw std::runtime_error("Invalud input format");
            } // if
            char chr;
            in >> chr;
            // std::cout << "Read char: " << chr << std::endl;
            std::vector<std::pair<int,int>> points;
            while (static_cast<char>(in.peek()) != ']') {
                if (static_cast<char>(in.peek()) != '(') {
                    // std::cout << "2 - Invalid input format: " << static_cast<char>(in.peek()) << std::endl;
                    throw std::runtime_error("Invalud input format");
                } // if
                std::pair<int,int> point;
                in >> chr >> point.first >> point.second >> chr;
                points.push_back(point);
                // std::cout << "chr: " << chr << std::endl;
                // skip white spaces
                while (static_cast<char>(in.peek()) == ' ') {
                    chr = in.get();
                    // in >> chr;  this call will skip white spaces
                    // std::cout << "Skipped white space: '" << chr << "'" << std::endl;
                } // while
                // std::cout << "Added point: (" << point.first << "," << point.second << ") chr: " << chr << std::endl;
            } // while
            std::getline(in, line); // read the ']' to end of line
            data.m_expected.insert(points);
        } // while
        std::getline(in, line); // read the '}' line
        return in;
    }

    // std::cout << "3 - Invalid input format" << std::endl;
    throw std::runtime_error("Invalid input format");
}

// Test Fixture Class
class SearchMatrixTwoFixture :
    public testing::TestWithParam<SearchMatrixTwoData> {
};

// Parameterized Test Definition
TEST_P(SearchMatrixTwoFixture, SearchMatrixTwoTests) {
    SearchMatrixTwoData data = GetParam();

    // std::cout << "Processing: input=[";
    // for (auto values : data.get_input()) {
    //     std::cout << " [";
    //     for (auto value : values)
    //         std::cout << " " << value;
    //     std::cout << " ]" << std::endl;
    // } // for
    // std::cout << "]" << std::endl;

    Solution solution;

    std::set<std::vector<std::pair<int,int>>> actual = solution.searchMatrix(data.get_input(), data.get_word());

    // std::cout << "Actual: {" << std::endl;
    // for (auto points : actual) {
    //     std::cout << " [";
    //     for (auto point : points)
    //         std::cout << " (" << point.first << "," << point.second << ")";
    //     std::cout << " ]" << std::endl;
    // } // for
    // std::cout << "}" << std::endl;

    // std::cout << "Expected: {" << std::endl;
    // for (auto points : data.get_expected()) {
    //     std::cout << " [";
    //     for (auto point : points)
    //         std::cout << " (" << point.first << "," << point.second << ")";
    //     std::cout << " ]" << std::endl;
    // } // for
    // std::cout << "}" << std::endl;

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(SearchMatrixTwoTests, SearchMatrixTwoFixture, testing::ValuesIn(
    Loader<SearchMatrixTwoData>()(find_path("matrices/data/search_matrix_two.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
