/**
 * @file employees_manager_mapping.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=EmployeesManagerMapping
 * @version 0.1
 * @date 2023-06-01
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#include <iostream>

#include "employees_manager_mapping.h"

namespace valhalla {
    namespace dynamic_programming {
        namespace employees_manager_mapping {
            /*

            Given a map containing employee to manager mappings, find all employees under each
            manager who directly or indirectly reports him.

            Input : {'A': 'A', 'B': 'A', 'C': 'B', 'D': 'B', 'E': 'D', 'F': 'E'}
            Output: {'A': ['E', 'C', 'B', 'D', 'F'], 'B': ['D', 'E', 'C', 'F'],
                     'C': [], 'D': ['E', 'F'], 'E': ['F'], 'F': []}
            Explanation: The input represents the following employee-manager pairs:

            'A' —> 'A'
            'B' —> 'A'
            'C' —> 'B'
            'D' —> 'B'
            'E' —> 'D'
            'F' —> 'E'

            Here, 'A' reports to himself, i.e., 'A' is head of the company and is the manager of
            employee 'B'. 'B' is the manager of employees 'C' and 'D', 'D' is the manager of
            employee 'E', 'E' is the manager of employee 'F', 'C', and 'F' is not managers of
            any employee. i.e.,

            'A' —> ['B', 'D', 'C', 'E', 'F']
            'B' —> ['D', 'C', 'E', 'F']
            'C' —> []
            'D' —> ['E', 'F']
            'E' —> ['F']
            'F' —> []

            */

            std::unordered_map<char, std::unordered_set<char>> Solution::findMapping(std::unordered_map<char, char> & employeeToManagerMappings) {
                std::unordered_map<char, std::unordered_set<char>> mappings;

                for (std::pair<char,char> connection : employeeToManagerMappings) {
                    std::cout << connection.first << " works for " << connection.second << std::endl;
                    if (connection.first != connection.second) {
                        mappings[connection.first].insert(connection.second);
                    } else {
                        mappings[connection.first];
                    }
                } // for

                for(std::pair<char,std::unordered_set<char>> p : mappings) {
                    std::cout << "'" << p.first << "' -> [";
                    for (char value : p.second) {
                        std::cout << " '" << value << "'";
                    }
                    std::cout << " ]" << std::endl;
                }

                return mappings;
            } // findMapping
        }
    }
}
