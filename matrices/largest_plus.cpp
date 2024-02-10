/**
 * @file largest_plus.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=LargestPlus
 * @version 0.1
 * @date 2023-06-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "largest_plus.h"

#include <iostream>
#include <set>
#include <list>

namespace valhalla {
    namespace matrices {
        namespace largest_plus {
            /*
                This Center struct is used to store the current center value of the plus sign within the
                square matrix.
            */
            struct Center {
                size_t m_x, m_y;
                Center() = default;
                Center(size_t x, size_t y) : m_x(x), m_y(y) {}
                friend std::ostream& operator<<(std::ostream&, Center&);
                Center & operator()(size_t x, size_t y) {
                    m_x = x; m_y = y;
                    return *this;
                }
                friend std::ostream & operator<<(std::ostream& out, Center & center) {
                    return out << "Center(" << center.m_x << "," << center.m_y << ")";
                };
                bool operator==(const struct Center & other) {
                    return m_x == other.m_x && m_y == other.m_y;
                }
            };

            class Point {
                size_t m_x, m_y;
            public:
                Point() = default;
                Point(size_t x, size_t y) : m_x(x), m_y(y) {}
                Point(size_t c) : m_x(c), m_y(c) {}
                // Point(Point & other) : m_x(other.m_x), m_y(other.m_y) {}
                friend std::ostream & operator<<(std::ostream& out, const Point & point) {
                    return out << "Point[" << point.m_x << "," << point.m_y << "]";
                }
                Point& operator=(const Point & other) {
                    if (this == &other) {
                        return *this;
                    }

                    m_x = other.m_x;
                    m_y = other.m_y;
                    return *this;
                }
                bool operator==(const Point & other) {
                    return m_x == other.m_x && m_y == other.m_y;
                }
                bool operator!=(const Point & other) {
                    return ! ( *this == other );
                }
                bool operator<(const Point & other) {
                    return (m_x == other.m_x && m_y < other.m_y) ||
                        (m_x < other.m_x);
                }
                friend bool operator<(const Point & lhs, const Point & rhs) {
                    return (lhs.m_x == rhs.m_x && lhs.m_y < rhs.m_y) ||
                        (lhs.m_x < rhs.m_x);
                }
                size_t x() const { return m_x; }
                size_t y() const { return m_y; }
                size_t operator[](size_t fld) {
                    switch(fld) {
                        case 0: return m_x;
                        case 1: return m_y;
                    }
                    throw std::out_of_range("invalid field range, the only valid options are 0 or 1");
                }
            };

            // class Perimeter {
            //     const size_t m_len;
            //     std::list<Point> m_points;
            //     Point m_top, m_bottom, m_end, m_current;
            // public:
            //     Perimeter(size_t len) : m_len(len) {
            //         size_t start = ( m_len - 1 ) / 2;
            //         // add the common point.
            //         m_points.push_back(Point(start, start));
            //         if (m_len % 2 != 1) {
            //             m_points.push_back(Point(start, 1 + start));
            //             m_points.push_back(Point(1 + start, start));
            //             m_points.push_back(Point(1 + start, 1 + start));
            //         }
            //         std::cout << "Perimeter size: " << m_points.size() << " for length: " << m_len << " with entries:" << std::endl;
            //         for(Point point : m_points)
            //             std::cout << point << std::endl;
            //     }

            //     bool operator==(const Point& current) {
            //         return &m_current == &current;
            //     }

            //     const Point & end() { return m_end; }

            //     const std::list<Point> & get() { return m_points; }
            // };

            // class perimeter_iterator {
            //     std::list<Point> m_points;
            //     Point & m_top, & m_end, & m_current;
            //     size_t m_size;
            // public:
            //     perimeter_iterator() = default;
            //     perimeter_iterator(std::list<Point> & points, Point & end, size_t size) : m_points(points), m_end(end), m_size(size) {
            //         if (m_points.empty()) {
            //             m_current = m_end;
            //         } else {
            //             m_current = m_points.front();
            //         }
            //     }

            //     bool operator==(const Point & other) {
            //         return &m_current == &other;
            //     }

            //     Point& operator*() {
            //         return m_current;
            //     }

            //     perimeter_iterator& operator++() {
            //         m_points.pop_front();
            //         if (m_points.empty()) {
            //             if (m_top.x() < 2) {
            //                 m_current = m_end;
            //             } else {
            //                 m_top = Point(m_top.x() - 1, m_top.y() - 1);
            //                 m_size += 2;
            //                 size_t end = m_top.x() + m_size;
            //                 size_t fixed = m_top.x();
            //                 for(size_t cnt = m_top.x() ; cnt < end ; cnt++) {
            //                     m_points.push_back(Point(fixed, cnt));
            //                     m_points.push_back(Point(fixed + m_size, cnt));
            //                 }
            //             }
            //         } else {
            //             m_current = m_points.front();
            //         }
            //         return *this;
            //     }
            // };

            // class perimeter {
            //     Point m_top, m_end;
            //     std::list<Point> m_points;
            //     size_t m_size;
            // public:
            //     perimeter() = default;
            //     perimeter(size_t len) {
            //         size_t start = ( len - 1 ) / 2;
            //         m_top = Point(start, start);
            //         // add the common point.
            //         m_points.push_back(m_top);
            //         m_size = 1;
            //         if (len % 2 != 1) {
            //             m_points.push_back(Point(start, 1 + start));
            //             m_points.push_back(Point(1 + start, start));
            //             m_points.push_back(Point(1 + start, 1 + start));
            //             m_size++;
            //         }
            //         std::cout << "Perimeter size: " << m_points.size() << " for length: " << len << " with entries:" << std::endl;
            //         for(Point point : m_points)
            //             std::cout << point << std::endl;
            //     }

            //     perimeter_iterator begin() { return perimeter_iterator(m_points, m_end, m_size); }
            // };
            class Perimeter {
                Point m_top, m_end;
                std::list<Point> m_points;
            public:
                Perimeter() = default;
                Perimeter(Point & point) : m_top(point), m_end(point) {
                    m_points.push_back(m_top);
                }
                Perimeter(Point & top, Point & end) {
                    if (top == end) {
                        m_end = top;
                        m_top = top;
                        m_points.push_back(m_top);
                    } else {
                        if (top < end) {
                            m_top = top;
                            m_end = end;
                        } else {
                            m_top = end;
                            m_end = top;
                        }
                        // populate m_points
                        for(size_t row = m_top.x() ; row <= m_end.x() ; row++) {
                            m_points.push_back(Point(row, m_top.y()));
                        }
                        for(size_t col = m_top.y() + 1 ; col <= m_end.y() ; col++) {
                            m_points.push_back(Point(m_end.x(), col));
                        }
                        for(size_t row = m_top.x() ; row < m_end.x() ; row++) {
                            m_points.push_back(Point(row, m_end.y()));
                        }
                        for(size_t col = m_top.y() + 1; col < m_end.y() ; col++) {
                            m_points.push_back(Point(m_top.x(), col));
                        }
                    }
                }
                bool contains(Point & point) {
                    return m_top.x() <= point.x() && m_top.y() <= point.y() &&
                        m_end.x() >= point.x() && m_end.y() >= point.y();
                }
                std::list<Point>::const_iterator cbegin() {
                    return m_points.cbegin();
                }
                std::list<Point>::const_iterator cend() {
                    return m_points.cend();
                }
                std::list<Point>::iterator begin() {
                    return m_points.begin();
                }
                std::list<Point>::iterator end() {
                    return m_points.end();
                }
                Perimeter & operator++() {
                    if (m_top.x() == 0) {
                        throw std::exception("Unable to expand perimeter");
                    }
                    *this = Perimeter(Point(m_top.x() - 1, m_top.y() - 1),Point(m_end.x() + 1, m_end.y() + 1));
                    return *this;
                }
                Perimeter operator++(int) {
                    if (m_top.x() == 0) {
                        throw std::exception("Unable to expand perimeter");
                    }
                    Perimeter original = *this;
                    *this = Perimeter(Point(m_top.x() - 1, m_top.y() - 1),Point(m_end.x() + 1, m_end.y() + 1));
                    return original;
                }
                bool can_expand() {
                    return m_top.x() > 0;
                }
            };
            /*

            Given a square matrix of 0’s and 1’s, calculate the size of the largest plus
            formed by 1’s.

            Input:

            grid = [
                [1, 0, 1, 1, 1, 1, 0, 1, 1, 1],
                [1, 0, 1, 0, 1, 1, 1, 0, 1, 1],
                [1, 1, 1, 0, 1, 1, 0, 1, 0, 1],
                [0, 0, 0, 0, 1, 0, 0, 1, 0, 0],
                [1, 1, 1, 0, 1, 1, 1, 1, 1, 1],
                [1, 1, 1, 1, 1, 1, 1, 1, 1, 0],
                [1, 0, 0, 0, 1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 1, 1, 0, 0, 1, 1],
                [1, 1, 0, 0, 1, 0, 1, 0, 0, 1],
                [1, 0, 1, 1, 1, 1, 0, 1, 0, 0]
            ]

            Output: 17

            Explanation: The largest plus of 1’s is marked below, having size 17.


                1  0  1  1  1  1  0  1  1  1
                1  0  1  0  |  1  1  0  1  1
                1  1  1  0  |  1  0  1  0  1
                0  0  0  0  |  0  0  1  0  0
                1  1  1  0  |  1  1  1  1  1
                –  –  –  –  |  –  –  –  –  0
                1  0  0  0  |  0  0  1  0  1
                1  0  1  1  |  1  0  0  1  1
                1  1  0  0  |  0  1  0  0  1
                1  0  1  1  |  1  0  1  0  0


            Input:

            [
                [1, 1, 1, 1, 1, 1],
                [1, 0, 1, 1, 0, 1],
                [0, 1, 1, 0, 0, 1],
                [1, 1, 1, 1, 1, 1],
                [1, 0, 0, 1, 0, 1],
                [1, 0, 1, 1, 0, 0]
            ]

            Output: 0

            Explanation: No largest plus of 1’s can be constructed.

            */

            int Solution::findLargestPlus(std::vector<std::vector<int>> const & grid) {
                if (grid.size() < 3) {
                    // We need at least three rows and three columns to create a plus sign
                    return 0;
                }

                int llen = 0;
                struct Center center;

                const size_t rows = grid.size(), rlast = rows - 1; // rlasts will always be greater than 0
                const size_t cols = grid.size(), clast = cols - 1; // clasts will always be greater than 0

                // Solution 1: simple implementation

                // for(size_t row = 1 + llen; row + llen < rlast ; row++) {
                //     for (size_t col = 1 + llen; col + llen < clast ; col++) {
                //         if (grid[row][col] == 1) {
                //             // Check for a plus sign
                //             if (grid[row][col-1] == 1 && grid[row-1][col] == 1 && grid[row+1][col] == 1 && grid[row][col+1] == 1) {
                //                 // Okay we have a plus sign within the grid then we need to determine its size
                //                 size_t max = std::min(std::min(std::min(row-1,rows-row-1),col-1),cols-col-1), count = 0;
                //                 int len = 1; // initial length of the current plus sign
                //                 size_t tcol = col - 1;
                //                 while (tcol-- > 0 && grid[row][tcol] == 1 && count++ < max) len++;
                //                 tcol = col + 1;
                //                 int tlen = 1;
                //                 count = 0;
                //                 while (tcol++ < clast && grid[row][tcol] == 1 && count++ < max) tlen++;
                //                 len = std::min(len, tlen);
                //                 size_t trow = row - 1;
                //                 tlen = 1;
                //                 count = 0;
                //                 while (trow-- > 0 && grid[trow][col] == 1 && count++ < max) tlen++;
                //                 len = std::min(len, tlen);
                //                 trow = row + 1;
                //                 tlen = 1;
                //                 count = 0;
                //                 while (trow++ < rlast && grid[trow][col] == 1 && count++ < max) tlen++;
                //                 len = std::min(len, tlen);
                //                 if (len > llen) {
                //                     // update the len
                //                     llen = len;
                //                     // update the center value
                //                     center(row,col);
                //                 }
                //             } // if grid[row][col-1] ...
                //         } // if grid[row][col]
                //     } // for col
                // } // for row

                // Solution 2: compact solution 1 implementation
                // NOTE: This solution is twice as fast as solution 1

                for(size_t row = 1 + llen; row + llen < rlast ; row++) {
                    for (size_t col = 1 + llen; col + llen < clast ; col++) {
                        if (grid[row][col] == 1) {
                            // Check for a plus sign
                            // Okay we have a plus sign within the grid then we need to determine its size
                            size_t max = std::min(std::min(std::min(row,rlast-row),col),clast-col);
                            // check the current max is greater than the currently found plus sign
                            if (llen >= max) {
                                // there are no possible plus sign greater than the current one that was found
                                continue;
                            }
                            int len = 0; // initial length of the current plus sign
                            // Check for a plus sign
                            while (len < max && grid[row][col-len-1] == 1 && grid[row-len-1][col] == 1 && grid[row+len+1][col] == 1 && grid[row][col+len+1] == 1) {
                                len++;
                            }
                            if (len > llen) {
                                // update the len
                                llen = len;
                                // update the center value
                                center(row,col);
                            }
                        } // if grid[row][col]
                    } // for col
                } // for row

                /*
                    Solution 3:

                    Instead of iterating through the matrix we can take into consideration that the largest plus sign will be centered
                    within the matrix.  While the next largest will be circularly spanned out from the center.  Thus, starting from the
                    center of the matrix and moving away from that point should simplify the checking process.  While performing this
                    task we can also determine which points can and cannot be used by looking at the current plus checks.  This should
                    reduce the number of checks that will be performed and increase the performance of the algorithm.  The other 
                    improvement is that when a plus sign was found.  We can use this information as a termination conditions if the
                    found plus is the largest one for the current perimeter.  While anyone that is smaller than the greater plus for
                    a given point can be used to determine when to stop expanding the perimeter to that plus sign length.

                    NOTE: This solution is actually much slower than solution 1 which is terrible!
                */
                // // NOTE: Removing the use of the exclude set more than doubles the performance of this implementation but still slower than solution 1!
                // // std::set<Point> exclude; // This will contain all of the center points that can not be used to check for a plus sign
                // Point point;
                // Perimeter perimeter;
                // const size_t size = grid.size(), max = (size - 1) / 2;

                // // create a perimeter instance that will be used to extract the next set of perimeter entries
                // if (size % 2 == 1) {
                //     size_t x = (size - 1) / 2, y = x;
                //     point = Point(x, y);
                //     perimeter = Perimeter(point);
                // } else {
                //     size_t x = (size - 1) / 2, y = x;
                //     point = Point(x, y);
                //     perimeter = Perimeter(point, Point((size - 1) / 2 + 1, (size - 1) / 2 + 1));
                // }

                // while (llen < max) {
                //     for (const auto & point : perimeter) {
                //         size_t x = point.x(), y = point.y();
                //         if (grid[x][y] == 0) {
                //             // This can be used to look for a plus sign so can't the surrounding
                //             // points so let us add them to the exclude set for increased performance
                //             // if (x > 0) {
                //             //     Point p(x-1,y);
                //             //     if ( !perimeter.contains(p))
                //             //         exclude.insert(p);
                //             //     p = Point(x+1,y);
                //             //     if ( !perimeter.contains(p))
                //             //         exclude.insert(p);
                //             //     p = Point(x,y+1);
                //             //     if ( !perimeter.contains(p))
                //             //         exclude.insert(p);
                //             //     p = Point(x,y-1);
                //             //     if ( !perimeter.contains(p))
                //             //         exclude.insert(p);
                //             // } // if (x > 0)
                //             continue;
                //         // } else if (exclude.find(point) != exclude.end()) {
                //         //     exclude.erase(point);
                //         //     continue;
                //         }
                //         size_t current = 0;
                //         size_t max_count = std::min(std::min(x,y), std::min(size - x - 1, size - y - 1));
                //         while ((max_count - current) > 0 && grid[x-current-1][y] && grid[x+current+1][y] && grid[x][y-current-1] && grid[x][y+current+1]) current++;
                //         if (current > llen) {
                //             llen = static_cast<int>(current);
                //             center = Center(x,y);
                //         }
                //     } // for (const auto & point...)
                //     if ( ! perimeter.can_expand() ) break;
                //     perimeter++;
                // } // while (longest < max)

                // Solution 4: trying to take advantage of the performance information gained between solution 1-3
                //             and trying to combined this into a faster implementation.
                //
                //             This solution is comparable to Solution 2 but it contains extra code that might be
                //             causing it to be just as fast as solution 2.

                // const size_t mid = rlast / 2;

                // for (size_t row = mid ; row > 0 && row > llen ; row--) {
                //     for (size_t col = 1 ; col < clast ; col++) {
                //         if (grid[row][col] == 1) {
                //             // Okay we have a plus sign within the grid then we need to determine its size
                //             size_t max = std::min(std::min(std::min(row,rlast-row),col),clast-col);
                //             // check the current max is greater than the currently found plus sign
                //             if (llen >= max) {
                //                 // there are no possible plus sign greater than the current one that was found
                //                 continue;
                //             }
                //             int len = 0; // initial length of the current plus sign
                //             // Check for a plus sign
                //             while (len < max && grid[row][col-len-1] == 1 && grid[row-len-1][col] == 1 && grid[row+len+1][col] == 1 && grid[row][col+len+1] == 1) {
                //                 len++;
                //             }
                //             if (len > llen) {
                //                 // update the len
                //                 llen = len;
                //                 // update the center value
                //                 center(row,col);
                //                 // check if we already found the largest possible one for the given row
                //                 if (llen >= row) break;
                //             } // if (len > llen)
                //         } // if grid[row][col]
                //     } // for (size_t col = 1...)
                // } // for (size_t row = mid...)

                // for (size_t row = mid + 1 ; row < rlast && rlast - row > llen ; row++) {
                //     for (size_t col = 1 ; col < clast ; col++) {
                //         if (grid[row][col] == 1) {
                //             // Okay we have a plus sign within the grid then we need to determine its size
                //             size_t max = std::min(std::min(std::min(row,rlast-row),col),clast-col);
                //             // check the current max is greater than the currently found plus sign
                //             if (llen >= max) {
                //                 // there are no possible plus sign greater than the current one that was found
                //                 continue;
                //             }
                //             int len = 0; // initial length of the current plus sign
                //             // Check for a plus sign
                //             while (len < max && grid[row][col-len-1] == 1 && grid[row-len-1][col] == 1 && grid[row+len+1][col] == 1 && grid[row][col+len+1] == 1) {
                //                 len++;
                //             }
                //             if (len > llen) {
                //                 // update the len
                //                 llen = len;
                //                 // update the center value
                //                 center(row,col);
                //                 // check if we already found the largest possible one for the given row
                //                 if (llen >= rlast - row) break;
                //             } // if (len > llen)
                //         } // if grid[row][col]
                //     } // for (size_t col = 1...)
                // } // for (size_t row = mid...)

                if (llen > 0) std::cout << "Largest center is located at " << center << " with length " << llen << std::endl;
                return (llen > 0) ? (4 * llen + 1) : 0;
            } // findLargestPlus
        }
    }
}
