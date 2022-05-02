/**
 * @file arrays.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief Header file containing the method and class signatures for the different algorithms
 *  that are used to manipulate an array
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __ARRAYS_H__
#define __ARRAYS_H__

#include <iostream>
#include <map>
#include <vector>

namespace valhalla {
    /**
     * @brief This method will find a pair of entries in the passed array that sum to
     *  the passed target value.
     *
     *  Internally, it uses a set to store the current set of integers that were
     *  processed.  It then uses those values to determine if the new entries will
     *  produce a pair that sum to target.  This will then only take O(n) operations
     *  to determine if their exists such a sum.  This technique will also be able to
     *  return the pair of entries that sum to the target value.
     *
     * @return std::pair<int,int>
     */
    bool find_pair(std::vector<int>&, int, std::pair<int,int>&);

    /**
     * @brief This method will find a subarray of one or more entries that sum to zero
     *  within the passed array of entries.  It will return an empty vector if none  were
     *  found.
     *
     *  Internally, this uses a set to determine if any sequence will contain a sum of
     *  entries that will equal zero.
     *
     * @return true, if the passed vector contains entries the sum to zero else false.
     */
    bool find_subarray_with_zero_sum(std::vector<int>&);

    /**
     * @brief This method will print all sub-arrays that add up to zero given the passed
     *  array of entries.
     *
     *  Internally, this uses an unordered_map to store the beginning indexes that would
     *  only take O(n^2).
     *
     * @return the number of sub-arrays that add up to zero
     */
    int print_all_subarrays_with_zero_sum(std::vector<int>&, std::ostream& = std::cout);
}

#endif
