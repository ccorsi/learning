/**
 * @file shortest_path_threetests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=ShortestPathIII
 * @version 0.1
 * @date 2023-06-15
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
#include "shortest_path_three.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils;
using namespace valhalla::matrices::shortest_path_three;

// Test Fixture Data Class
class ShortestPathThreeData {
    std::vector<std::vector<char>> m_input;
    std::vector<std::vector<int>> m_expected;
public:
    ShortestPathThreeData() = default;

    std::vector<std::vector<char>> const & get_input() { return m_input; }
    std::vector<std::vector<int>> const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ShortestPathThreeData &);
    friend std::istream& operator>>(std::istream&, ShortestPathThreeData &);

};

std::ostream& operator<<(std::ostream& out, const ShortestPathThreeData & data) {
    out << "ShortestPathThreeData [ input=[";
    for (std::vector<char> values : data.m_input) {
        out << " [";
        for (char value : values) {
            out << " '" << value << "'";
        } // for
        out << " ]";
    } // for
    out << " ] expected=[";
    for (std::vector<int> values : data.m_expected) {
        out << " [";
        for (int value : values) {
            out << " " << value;
        } // for
        out << " ]";
    } // for
    out << " ] ]";

    return out;
}

template<typename Type, typename IsOpenChar, typename IsCloseChar>
struct VectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<Type> & type, int state) {
     Type entry;

     ::loaders::loader::v4::dataLoader<
       Type,
       char,
       ::loaders::loader::v4::reader<Type,char>,
       1,
       IsOpenChar,
       IsCloseChar,
       ::checkers::is_space_or<','>
     > inputLoader(entry);
     in >> inputLoader;

     type.push_back(entry);

     return in;
   }
};

template<typename Type, typename IsOpenChar, typename IsCloseChar>
struct VectorVectorReader {
  std::basic_istream<char> & operator()(std::basic_istream<char> & in, std::vector<std::vector<Type>> & type, int state) {
     std::vector<Type> entry;

     ::loaders::loader::v4::dataLoader<
       std::vector<Type>,
       char,
       VectorReader<Type, IsOpenChar, IsCloseChar>,
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

std::istream& operator>>(std::istream& in, ShortestPathThreeData &data) {
    ::loaders::loader::v4::dataLoader<
      std::vector<std::vector<char>>,
      char,
      VectorVectorReader<char,::checkers::is_character<char,'\''>,::checkers::is_character<char,'\''>>,
      1,
      ::checkers::is_character<char,'['>,
      ::checkers::is_character<char,']'>,
      ::checkers::is_space_or<','>
    > inputLoader(data.m_input);
    in >> inputLoader;

    ::loaders::loader::v4::dataLoader<
      std::vector<std::vector<int>>,
      char,
      VectorVectorReader<int,::checkers::is_character_noop<char>,::checkers::is_no_character<char>>,
      1,
      ::checkers::is_character<char,'['>,
      ::checkers::is_character<char,']'>,
      ::checkers::is_space_or<','>
    > expectedLoader(data.m_expected);
    in >> expectedLoader;

    return in;
}

// Test Fixture Class
class ShortestPathThreeFixture :
    public testing::TestWithParam<ShortestPathThreeData> {
};

// Parameterized Test Definition
TEST_P(ShortestPathThreeFixture, ShortestPathThreeTests) {
    ShortestPathThreeData data = GetParam();

    Solution solution;

    std::vector<std::vector<int>> actual = solution.updateShortestDistance(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ShortestPathThreeTests, ShortestPathThreeFixture, testing::ValuesIn(
    Loader<ShortestPathThreeData>()(find_path("matrices/data/shortest_path_three.txt"))
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
