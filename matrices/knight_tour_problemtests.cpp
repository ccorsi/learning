/**
 * @file knight_tour_problemtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=KnightTourProblem
 * @version 0.1
 * @date 2023-03-01
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
#include "knight_tour_problem.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::matrices::knight_tour_problem;

// Test Fixture Data Class
class KnightTourProblemData {
    int m_n;
    std::set<std::vector<std::vector<int>>> m_expected;
public:
    KnightTourProblemData() = default;

    int get_n() { return m_n; }
    std::set<std::vector<std::vector<int>>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KnightTourProblemData &);
    friend std::istream& operator>>(std::istream&, KnightTourProblemData &);

};

std::ostream& operator<<(std::ostream& out, const KnightTourProblemData & data) {
    out << "KnightTourProblemData [ n=" << data.m_n;
    out << " expected={";
    for( std::vector<std::vector<int>> mat : data.m_expected) {
        out << " [";
        for (std::vector<int> values : mat) {
            out << " [";
            for (int value : values)
                out << " " << value;
            out << " ]";
        } // for
        out << " ]";
    } // for
    out << " } ]";

    return out;
}

void print_matrix(std::vector<std::vector<int>> const & mat) {
    std::cout << "[";
    for( std::vector<int> values : mat) {
        std::cout << " [";
        for (int value : values)
            std::cout << " " << value;
        std::cout << " ]";
    } // for
    std::cout << " ]";
}

std::istream& operator>>(std::istream& in, KnightTourProblemData &data) {
    in >> data.m_n;
    std::string line;
    std::getline(in, line); // read end of line
    // std::cout << "Read n=" << data.m_n << std::endl;

    if (static_cast<char>(in.peek()) == '{') {
        std::getline(in, line); // read '{' line
        while (static_cast<char>(in.peek()) != '}') {
            std::vector<std::vector<int>> mat;
            matrixLoader<int> loader(mat);
            in >> loader;
            data.m_expected.insert(mat);
            // std::cout << "Added matrix: "; print_matrix(mat); std::cout << std::endl;
        } // while
        std::getline(in, line); // read '}' line
    } else {
        throw std::runtime_error("Invalid input stream");
    } // else

    return in;
}

// Test Fixture Class
class KnightTourProblemFixture :
    public testing::TestWithParam<KnightTourProblemData> {
};

// Created a matcher that will iterate over all of the container entries to determine if they are all
// part of the passed arg container.  It will fail if the size is different or if any of the instances
// in the container is part of the passed arg container.
MATCHER_P(ContainsAll, container, "Checks that all entries in container are part of the passed arg container") {
    std::cout << "arg size: " << container.size() << std::endl;

    // insure that the passed arg container contains at least the same number of elements as the container
    if (container.size() != arg.size())
        return false;

    // check that each item in the container is also contained within the arg container
    for (auto entry : container)
        if (arg.find(entry) == arg.end())
            return false;

    return true;
}

// Parameterized Test Definition
TEST_P(KnightTourProblemFixture, KnightTourProblemTests) {
    KnightTourProblemData data = GetParam();

    Solution solution;

    std::set<std::vector<std::vector<int>>> actual = solution._knightTour(data.get_n());

    // std::cout << "Size of actual: " << actual.size() << ", size of expected: " << data.get_expected().size() << std::endl;

    // This will generate a failure even though the two sets are the same
    ASSERT_EQ(actual, data.get_expected());

    // This doesn't compile because of a lack of a missing == operator
    // ASSERT_THAT(actual, testing::AllOfArray(data.get_expected()));

    // This does compile but it doesn't produce the expected resulting checks
    // ASSERT_THAT(actual, ContainsAll(data.get_expected()));
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(KnightTourProblemTests, KnightTourProblemFixture, testing::ValuesIn(
    Loader<KnightTourProblemData>()(find_path("matrices/data/knight_tour_problem.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
