/**
 * @file contains_one_of.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains GoogleTest test checking classes
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#ifndef __CONTAINS_ONE_OF_H__
#define __CONTAINS_ONE_OF_H__

namespace valhalla {
    namespace utils {
        namespace testing {
            /**
             * @brief This class is used to determine if the passed vector entries are
             *      contained with at least one of the sets included reference by
             *      this class.
             *
             * @tparam E The type of elements that are contained within each set
             * @deprecated This class is not required and was replaced with the use of
             *      the ASSERT_THAT macro and the testing::AnyOfArray class instead.
             */
            template<typename E>
            class ContainsOneOf {
                std::vector<std::vector<E>> m_values;
            public:
                ContainsOneOf() = default;
                ContainsOneOf(std::vector<std::vector<E>> const & values) : m_values(values) {}

                bool operator()(std::vector<E>& values) {
                    bool contains =  false;

                    for(std::vector<E> cmp : m_values) {
                        if (cmp.size() == values.size()) {
                            bool allFound = true;
                            for(size_t idx = 0 ; allFound && idx < cmp.size() ; idx++)
                                allFound &= cmp[idx] == values[idx];
                            contains |= allFound;
                        }
                    }

                    return contains;
                }
            };
        }
    }
}

#endif
