/**
 * @file arrays.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is an implementation of the two sum array problem at
 * 		  https://www.techiedelight.com/find-pair-with-given-sum-array/).
 * 
 * @version 0.1
 * @date 2022-12-26
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <map>
#include <vector>

using namespace std;

#include "two_sum.h"

pair<int,int> valhalla::arrays::two_sum::Solution::find_pair(const vector<int> &values, const int target) {
	map<int,int> sums;
	
	for (auto itr = values.begin() ; itr != values.end() ; itr++) {
		int value =  *itr;
		int key = target - value;
		if (sums.count(value) == 1) {
			return pair<int,int>(key, value);		
		} else {
			sums[key] = value;
		}
	}
	
	return pair<int,int>(-1,-1);
}; // find_pair
