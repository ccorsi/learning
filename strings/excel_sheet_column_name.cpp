/**
 * @file excel_sheet_column_name.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=ExcelSheetColumnName
 * @version 0.1
 * @date 2023-02-13
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>

#include "excel_sheet_column_name.h"

/*

Given a positive number, convert the number to the corresponding Excel column name.

Input: 1
Output: "A"

Input: 27
Output: "AA"

Input: 1001
Output: "ALM"

Input: 26
Output: "Z"

Note: Excel supports upto 2^14 columns, i.e. 16,384 columns.

*/

std::string valhalla::strings::excel_sheet_column_name::Solution::getColumnName(int n) {
    std::string name;
    const char abc[] = "ZABCDEFGHIJKLMNOPQRSTUVWXY";

    while (n > 0) {
        int rem = (n % 26);
        name.insert(0, 1, abc[rem]);
        n /= 26;
        // std::cout << "Before n: " << n << ", rem: " << rem << std::endl;
        if (rem == 0) n--;
        // std::cout << "After n: " << n << ", name: " << name << std::endl;
    }

    return name;
}
