/**
 * @file kth_smallest_elementtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains tests to the problem https://www.techiedelight.com/?problem=KthSmallestElement
 * @version 0.1
 * @date 2026-04-22
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
 #include "kth_smallest_element.h"
 
 using namespace valhalla::utils::loaders;
 using namespace valhalla::utils::paths;
 using namespace valhalla::utils;
 using namespace valhalla::arrays::kth_smallest_element;
 using namespace valhalla::utils::readers;
 
 // Test Fixture Data Class
 class KthSmallestElementData {
    std::vector<int> m_input;
    int m_k, m_expected;
 public:
    KthSmallestElementData() = default;
 
    int get_k() { return m_k; }
    std::vector<int> const & get_input() { return m_input; }
    int get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const KthSmallestElementData &);
    friend std::istream& operator>>(std::istream&, KthSmallestElementData &);
 
    friend struct CombinedReader;
 };
 
 std::ostream& operator<<(std::ostream& out, const KthSmallestElementData & data) {
    out << "KthSmallestElementData [ input=[";
    for (int value : data.m_input)
        out << " " << value;
    out << " ] k=" << data.m_k << " expected=" << data.m_expected;
    out << " ]";
 
    return out;
 }

 struct CombinedReader {
   std::basic_istream<char> & operator()(std::basic_istream<char> & in, KthSmallestElementData & data, int state) {
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
            > VectorLoader(data.m_input);
            in >> VectorLoader;
         }
         break;
         case 1:
            in >> data.m_k;
         break;
         case 2:
            in >> data.m_expected;
         break;
         default:
            std::cout << "INVALID STATE\n";
            throw std::runtime_error("INVALID STATE");
      } // switch (state)

      return in;
   }
 };

 std::istream& operator>>(std::istream& in, KthSmallestElementData &data) {
    ::loaders::loader::v6::dataLoader<
        KthSmallestElementData,
        char,
        CombinedReader,
        3,
        ::checkers::is_character<char, '{'>,
        ::checkers::is_character<char, '}'>,
        ::checkers::is_space_or<','>,
        ::checkers::is_space_or<','>
    > DataLoader(data);
    in >> DataLoader;

    return in;
 }
 
 // Test Fixture Class
 class KthSmallestElementFixture :
    public testing::TestWithParam<KthSmallestElementData> {
 };
 
 // Parameterized Test Definition
 TEST_P(KthSmallestElementFixture, KthSmallestElementTests) {
    KthSmallestElementData data = GetParam();
 
    Solution solution;

   ASSERT_EQ(solution.findKthSmallest(data.get_input(), data.get_k()), data.get_expected());
 }
 
 // Parameter Test Parameters
 INSTANTIATE_TEST_SUITE_P(KthSmallestElementTests, KthSmallestElementFixture, testing::ValuesIn(
    Loader<KthSmallestElementData>()(find_path("arrays/data/kth_smallest_element.txt"))
 ));
 
 int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
 }
 