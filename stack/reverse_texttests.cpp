/**
 * @file reverse_texttests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests for the problem https://www.techiedelight.com/?problem=ReverseText
 * @version 0.1
 * @date 2025-02-07
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
#include "reverse_text.h"

using namespace valhalla::utils::loaders;
using namespace valhalla::utils::paths;
using namespace valhalla::utils::readers;
using namespace valhalla::utils;
using namespace valhalla::stack::reverse_text;

// Test Fixture Data Class
class ReverseTextData {
   std::string m_input;
   std::string m_expected;
public:
   ReverseTextData() = default;

   std::string const & get_input() { return m_input; }
   std::string const & get_expected() { return m_expected; }

   friend std::ostream& operator<<(std::ostream&, const ReverseTextData &);
   friend std::istream& operator>>(std::istream&, ReverseTextData &);

};

std::ostream& operator<<(std::ostream& out, const ReverseTextData & data) {
   out << "ReverseTextData [ input=\"" << data.m_input << "\", expected=\"";
   out << data.m_expected << "\"" << " ]";

   return out;
}

std::istream& operator>>(std::istream& in, ReverseTextData &data) {
   ::loaders::loader::v6::dataLoader<
      std::string,
      char,
      StringReader,
      1,
      ::checkers::is_character<char, '"'>,
      ::checkers::is_character<char, '"'>,
      ::checkers::is_space_or<','>,
      ::checkers::is_space_noop<char>
   > InputLoader(data.m_input);
   in >> InputLoader;

   ::loaders::loader::v6::dataLoader<
      std::string,
      char,
      StringReader,
      1,
      ::checkers::is_character<char, '"'>,
      ::checkers::is_character<char, '"'>,
      ::checkers::is_space_or<','>,
      ::checkers::is_space_noop<char>
   > ExpectedLoader(data.m_expected);
   in >> ExpectedLoader;

   return in;
}

// Test Fixture Class
class ReverseTextFixture :
   public testing::TestWithParam<ReverseTextData> {
};

// Parameterized Test Definition
TEST_P(ReverseTextFixture, ReverseTextTests) {
   ReverseTextData data = GetParam();

   Solution solution;

   std::string s = data.get_input();

   solution.reverseText(s);

   ASSERT_EQ(data.get_expected(), s);
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ReverseTextTests, ReverseTextFixture, testing::ValuesIn(
   Loader<ReverseTextData>()(find_path("stack/data/reverse_text.txt"))
));

int main(int argc, char** argv) {
   ::testing::InitGoogleTest(&argc, argv);
   return RUN_ALL_TESTS();
}
