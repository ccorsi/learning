/**
 * @file excel_sheet_column_nametests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "excel_sheet_column_name.h"

using namespace valhalla::strings::excel_sheet_column_name;

// Test Fixture Data Class
class ExcelSheetColumnNameData {
    int m_input;
    std::string m_expected;

public:
     ExcelSheetColumnNameData() = default;
     ExcelSheetColumnNameData(int n, std::string expected) : m_input(n), m_expected(expected) {}

     int get_input() { return m_input; }
     std::string const & get_expected() { return m_expected; }

    friend std::ostream& operator<<(std::ostream&, const ExcelSheetColumnNameData&);

};

std::ostream& operator<<(std::ostream& out, const ExcelSheetColumnNameData &data) {
    out << "ExcelSheetColumnNameData [ input=" << data.m_input << " expected=\"" << data.m_expected << "\" ]";

    return out;
}

// Test Fixture Class
class ExcelSheetColumnNameFixture :
    public testing::TestWithParam<ExcelSheetColumnNameData> {
};

// Parameterized Test Definition
TEST_P(ExcelSheetColumnNameFixture, ExcelSheetColumnNameTests) {
    ExcelSheetColumnNameData data = GetParam();

    Solution solution;

    std::string actual = solution.getColumnName(data.get_input());

    ASSERT_EQ(actual, data.get_expected());
}

// Parameter Test Parameters
INSTANTIATE_TEST_SUITE_P(ExcelSheetColumnNameTests, ExcelSheetColumnNameFixture, testing::Values(
    ExcelSheetColumnNameData(1, "A"),
    ExcelSheetColumnNameData(27, "AA"),
    ExcelSheetColumnNameData(28, "AB"),
    ExcelSheetColumnNameData(1001, "ALM"),
    ExcelSheetColumnNameData(18, "R"),
    ExcelSheetColumnNameData(26, "Z")
));

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
