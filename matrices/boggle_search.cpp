/**
 * @file boggle_search.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=BoggleSearch
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <utility>
#include <set>
#include <list>
#include <map>
#include <cmath>
#include <stdexcept>
#include <iostream>

#include "boggle_search.h"

namespace valhalla {
    namespace matrices {
        namespace boggle_search {

            bool Solution::check_for_word(std::vector<std::vector<char>> const & board,
                                          std::string const & word, const int row,
                                          const int col, const int idx,
                                          std::set<std::pair<int,int>> & chars) {
                if (word.size() == idx) {
                    // std::cout << "Found word: " << word << " at ";
                    // for (auto point : chars)
                    //     std::cout << "(" << point.first << "," << point.second << ") = " << board[point.first][point.second] << " ";
                    // std::cout << std::endl;
                    return true;
                } // if (word.size() == idx)

                const char chr = word[idx];
                std::list<std::pair<int,int>> points;

                if (row > 0) {
                    const int crow = row - 1;
                    if (col > 0 && board[crow][col-1] == chr) {
                        points.push_back(std::pair(crow,col-1));
                    } // if (col > 0 && board[crow][col-1] == chr)

                    if (board[crow][col] == chr) {
                        points.push_back(std::pair(crow,col));
                    } // if (board[crow][col] == chr)

                    if (col + 1 < board[crow].size() && board[crow][col+1] == chr) {
                        points.push_back(std::pair(crow,col+1));
                    } // if (col + 1 < board[crow].size() && board[crow][col+1] == chr)
                } // if (row > 0)

                if (col > 0 && board[row][col-1] == chr) {
                    points.push_back(std::pair(row,col-1));
                } // if (col > 0 && board[row][col-1] == chr)

                if (col + 1 < board[row].size() && board[row][col+1] == chr) {
                    points.push_back(std::pair(row,col+1));
                } // if (col + 1 < board[row].size() && board[row][col+1] == chr)

                if (row + 1 < board.size()) {
                    const int crow = row + 1;
                    if (col > 0 && board[crow][col-1] == chr) {
                        points.push_back(std::pair(crow,col-1));
                    } // if (col > 0 && board[crow][col-1] == chr)

                    if (board[crow][col] == chr) {
                        points.push_back(std::pair(crow,col));
                    } // if (board[crow][col] == chr)

                    if (col + 1 < board[crow].size() && board[crow][col+1] == chr) {
                        points.push_back(std::pair(crow,col+1));
                    } // if (col + 1 < board[crow].size() && board[crow][col+1] == chr)
                } // if (row + 1 < board.size())

                for (auto & next : points) {
                    if (chars.insert(next).second) {
                        if (check_for_word(board, word, next.first, next.second, idx+1, chars)) {
                            // chars.erase(next);
                            return true;
                        } // if (check_for_word(board, word, next.first, next.second, idx+1, chars))
                        chars.erase(next);
                    } // if (chars.insert(next).second)
                } // for (auto & next : points)

                return false;
            } // bool check_for_word(board, word, row, col, idx, found) {


            bool Solution::find_next_letter(std::vector<std::vector<char>> const & board,
                                            std::string const & word,
                                            const int idx, std::set<std::pair<int,int>> & chars,
                                            std::pair<int,int> const & point) {
                if (idx == word.size()) {
                    // This will always be the case so this check is not necessary but I added it nonetheless
                    return chars.size() == word.size();
                }

                const auto rows = board.size(), cols = board[point.first].size();
                const auto chr = word[idx];
                std::list<std::pair<int,int>> points;

                // Solution 1:  This works but it performs more checks than necessary.

                // if (point.first > 0 && point.second > 0 && board[point.first-1][point.second-1] == chr) {
                //     points.push_back(std::pair(point.first-1,point.second-1));
                // }

                // if (point.first > 0 && board[point.first-1][point.second] == chr) {
                //     points.push_back(std::pair(point.first-1,point.second));
                // }

                // if (point.first > 0 && point.second + 1 < board[point.first].size()
                //     && board[point.first-1][point.second+1] == chr) {
                //     points.push_back(std::pair(point.first-1,point.second+1));
                // }

                // if (point.second > 0 && board[point.first][point.second-1] == chr) {
                //     points.push_back(std::pair(point.first,point.second-1));
                // }

                // if (point.second + 1 < board[point.first].size() && board[point.first][point.second+1] == chr) {
                //     points.push_back(std::pair(point.first,point.second+1));
                // }

                // if (point.first + 1 < board.size() && point.second > 0 && board[point.first+1][point.second-1] == chr) {
                //     points.push_back(std::pair(point.first+1,point.second-1));
                // }

                // if (point.first + 1 < board.size() && board[point.first+1][point.second] == chr) {
                //     points.push_back(std::pair(point.first+1,point.second));
                // }

                // if (point.first + 1 < board.size() && point.second + 1 < board[point.first].size()
                //     && board[point.first+1][point.second+1] == chr) {
                //     points.push_back(std::pair(point.first+1,point.second+1));
                // }

                // Solution 2:  This solution removes a few checks that should slightly improve the
                //              performance of the implementation.

                if (point.first > 0) {
                    if (point.second > 0 && board[point.first-1][point.second-1] == chr) {
                        points.push_back(std::pair(point.first-1,point.second-1));
                    }

                    if (board[point.first-1][point.second] == chr) {
                        points.push_back(std::pair(point.first-1,point.second));
                    }

                    if (point.second + 1 < board[point.first].size()
                        && board[point.first-1][point.second+1] == chr) {
                        points.push_back(std::pair(point.first-1,point.second+1));
                    }
                }

                if (point.second > 0 && board[point.first][point.second-1] == chr) {
                    points.push_back(std::pair(point.first,point.second-1));
                }

                if (point.second + 1 < board[point.first].size() && board[point.first][point.second+1] == chr) {
                    points.push_back(std::pair(point.first,point.second+1));
                }

                if (point.first + 1 < board.size()) {
                    if (point.second > 0 && board[point.first+1][point.second-1] == chr) {
                        points.push_back(std::pair(point.first+1,point.second-1));
                    }

                    if (board[point.first+1][point.second] == chr) {
                        points.push_back(std::pair(point.first+1,point.second));
                    }

                    if (point.second + 1 < board[point.first].size()
                        && board[point.first+1][point.second+1] == chr) {
                        points.push_back(std::pair(point.first+1,point.second+1));
                    }
                }

                for (auto & next : points) {
                    if (chars.insert(next).second) {
                        if (find_next_letter(board, word, idx+1, chars, next)) {
                            // chars.erase(next);
                            return true;
                        } // if (find_next_letter(board, word, idx+1, chars, next))
                        chars.erase(next);
                    } // if (chars.insert(next).second)
                } // for (auto & next : points)

                return false;
            }

            /*

            Given an `M × N` boggle board, find a list of all possible words that can be formed
            by a sequence of adjacent characters on the board.

            You are allowed to search a word in all eight possible directions,
            i.e., North, West, South, East, North-East, North-West, South-East, South-West, but
            a word should not have multiple instances of the same cell.

            Input:

            board =
            [
                ['M', 'S', 'E'],
                ['R', 'A', 'T'],
                ['L', 'O', 'N']
            ]

            words = ["STAR", "NOTE", "SAND", "STONE"]

            Output: {"STAR", "NOTE"}

            */

            std::unordered_set<std::string> Solution::searchBoggle(std::vector<std::vector<char>> const & board,
                std::unordered_set<std::string> const & words) {
                std::unordered_set<std::string> boggles;

                if (board.empty()) return boggles;

                const auto rows = board.size(), cols = board[0].size();

                // for (auto & word : words) {
                //     if (word.empty()) continue;
                //     std::set<std::pair<int,int>> chars;
                //     const auto size = word.size();
                //     for (auto row = 0 ; row < rows && boggles.find(word) == boggles.end() ; row++) {
                //         for (auto col = 0 ; col < cols && boggles.find(word) == boggles.end() ; col++) {
                //             if (word[0] == board[row][col]) {
                //                 const std::pair<int,int> point(row,col);
                //                 chars.insert(point); // add found point
                //                 // check surrounding characters for remaining letters
                //                 if (find_next_letter(board, word, 1, chars, point)) {
                //                     boggles.insert(word);
                //                 } // if (find_next_letter(board, word, 1, chars, point))
                //                 chars.clear(); // clear current set of entries
                //                 // chars.erase(point); // remove found point
                //             } // if (word[0] == board[row][col])
                //         } // for (auto col = 0 ; col < cols && boggles.find(word) == boggles.end() ; col++)
                //     } // for (auto row = 0 ; row < rows && boggles.find(word) == boggles.end() ; row++)
                // } // for (auto & word : words)

                // Solution 3:  We create a map of character to each word and then use that to check for
                //              neighboring points for each character of the words.  We use this map to
                //              be able to process the board matric only once instead of checking the
                //              first letter of each board entry to each word.
                //
                //  NOTE: This solution is a better solution for the case that the board is large and for
                //        the case when the number of words to find is large.  It has a more linear
                //        performance degradation compared to solution 1&2.

                std::map<char,std::list<std::string>> wordMap;

                for (auto & word : words) {
                    wordMap[word[0]].push_back(word);
                } // for (auto word : words)

                std::set<std::pair<int,int>> points;
                std::map<char,std::list<std::string>>::const_iterator itr;

                for (auto row = 0 ; row < rows ; row++) {
                    for (auto col = 0 ; col < cols ; col++) {
                        if ((itr = wordMap.find(board[row][col])) != wordMap.end()) {
                            for (auto & word : (*itr).second) {
                                if (boggles.find(word) == boggles.end()) {
                                    // initially add current row/col pair for first character
                                    points.insert(std::pair(row,col));
                                    if (check_for_word(board, word, row, col, 1, points)) {
                                        boggles.insert(word);
                                    } // if (check_for_word(board, word, row, col, 1, points))
                                    // clear current entries
                                    points.clear();
                                } // if (boggles.find(word) != boggles.end())
                            } // for (auto & word : (*itr).second)
                        } // if ((itr = wordMap.find(board[row][col])) != wordMap.end())
                    } // for (auto col = 0 ; col < cols ; col++)
                } // for (auto row = 0 ; row < rows ; row++)

                // std::cout << "{\n";
                // for (auto & boggle : boggles)
                //     std::cout << '"' << boggle << "\" ";
                // std::cout << "\n}\n";

                return boggles;
            } // searchBoggle
        }
    }
}
