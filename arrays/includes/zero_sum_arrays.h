/**
 * @file zero_sum_arrays.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-12-26
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include <vector>
#include <set>

namespace valhalla {
    namespace arrays {
        namespace zero_sum_arrays {
            class Solution {
            public:
                std::set<std::vector<int>> find_zero_subarrays(const std::vector<int> &values);
            };
        }
    }
}

#include <iostream>

template<typename E>
std::ostream& operator<<(std::ostream& out, const vector<E>& values) {
    out << "[";
    
    for(E value : values) {
        out << " " << value;
    }

    out << " ]";

    return out;
}

template<typename E>
std::ostream& operator<<(std::ostream& out, const set<E>& values) {
    out << "{";

    for (E value : values) {
        cout << " " << value;
    }

    out << " }";

    return out;
}
