/**
 * @file ball_arrangements.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BallArrangements
 * @version 0.1
 * @date 2023-03-11
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <iostream>
#include <memory>
#include <cmath>
#include <set>

#include "ball_arrangements.h"

void valhalla::dynamic_programming::ball_arrangements::Solution::findNext(int r, int b, int g, char last, int & count, char * combo, std::set<std::string> & found) {
    findNextMax(r, b, g, last, count, combo, found);
    findNextMin(r, b, g, last, count, combo, found);

    if ( last == ' ') {
        // we need to process the middle one
        if (r != b && b != g && r != g) {
            // we need to determine the mid point
            if (r < b && b < g) {
                // mid point is b
                combo[0] = 'b'; combo[1] = '\0';
                findNext(r, b-1, g, 'b', count, combo, found);
                combo[0] = '\0';
            } else if (b < g && g < r) {
                // mid point is g
                combo[0] = 'g'; combo[1] = '\0';
                findNext(r, b, g-1, 'g', count, combo, found);
                combo[0] = '\0';
            } else {
                // mid point is r
                combo[0] = 'r'; combo[1] = '\0';
                findNext(r-1, b, g, 'r', count, combo, found);
                combo[0] = '\0';
            }
        }
    }
}

void valhalla::dynamic_programming::ball_arrangements::Solution::findNextMax(int r, int b, int g, char last, int & count, char * combo, std::set<std::string> & found) {
    int largest;

    switch(last) {
        case 'r':
            largest = std::max(b, g);
            break;
        case 'b':
            largest = std::max(r, g);
            break;
        case 'g':
            largest = std::max(r, b);
            break;
        default:
            largest = std::max(r, std::max(b, g));
    } // switch

    if (largest > 0) {
        while (true) {
            if (last != 'r' && r == largest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'r'; combo[idx+1] = '\0';
                findNext(r-1, b, g, 'r', count, combo, found);
                combo[idx] = '\0';
            }
            if (last != 'b' && b == largest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'b'; combo[idx+1] = '\0';
                findNext(r, b-1, g, 'b', count, combo, found);
                combo[idx] = '\0';
            }
            if (last != 'g' && g == largest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'g'; combo[idx+1] = '\0';
                findNext(r, b, g-1, 'g', count, combo, found);
                combo[idx] = '\0';
            }
            break;
        } // while
        return; // we are done
    } // if

    if (r+b+g == 0) {
        // we've completed a combination
        if (found.insert(combo).second)
            count++;
    } // if
}

void valhalla::dynamic_programming::ball_arrangements::Solution::findNextMin(int r, int b, int g, char last, int & count, char * combo, std::set<std::string> & found) {
    int smallest;

    switch(last) {
        case 'r':
            smallest = std::min(b, g);
            break;
        case 'b':
            smallest = std::min(r, g);
            break;
        case 'g':
            smallest = std::min(r, b);
            break;
        default:
            smallest = std::min(r, std::min(b, g));
    } // switch

    if (smallest > 0) {
        while (true) {
            if (last != 'r' && r == smallest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'r'; combo[idx+1] = '\0';
                findNext(r-1, b, g, 'r', count, combo, found);
                combo[idx] = '\0';
            }
            if (last != 'b' && b == smallest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'b'; combo[idx+1] = '\0';
                findNext(r, b-1, g, 'b', count, combo, found);
                combo[idx] = '\0';
            }
            if (last != 'g' && g == smallest) {
                int idx = 0;
                while (combo[idx] != '\0') idx++;
                combo[idx] = 'g'; combo[idx+1] = '\0';
                findNext(r, b, g-1, 'g', count, combo, found);
                combo[idx] = '\0';
            }
            break;
        } // while
        return; // we are done
    } // if

    if (r+b+g == 0) {
        // we've completed a combination
        if (found.insert(combo).second)
            count++;
    } // if
}

/*

Given r red, b blue, and g green balls, find the total number of arrangements in a row
such that no two balls of the same color end up together.

Input: r = 1, b = 2, g = 1
Output: 6
Explanation: The arrangements are [bgbr, bgrb, brbg, brgb, gbrb, rbgb]

Input: r = 2, b = 3, g = 1
Output: 10
Explanation: The arrangements are [bgbrbr, bgrbrb, brbgbr, brbgrb, brbrbg, brbrgb, brgbrb,
gbrbrb, rbgbrb, rbrbgb]

*/

int valhalla::dynamic_programming::ball_arrangements::Solution::totalWays(int r, int b, int g) {
    int total = r + b + g;

    int count = 0;

    if (total > 0) {
        std::unique_ptr<char[]> combo(new char[total+1]);
        combo[0] = '\0'; // end of string
        std::set<std::string> found;

        findNext(r, b, g, ' ', count, combo.get(), found);

        std::cout << "Found:";
        for (std::string str : found)
            std::cout << " " << str;
        std::cout << std::endl;
    } // if

    return count;
}
