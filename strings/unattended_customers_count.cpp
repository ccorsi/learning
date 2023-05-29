/**
 * @file unattended_customers_count.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This is a solution to the problem https://www.techiedelight.com/?problem=UnattendedCustomersCount
 * @version 0.1
 * @date 2023-05-19
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */


#include "unattended_customers_count.h"

#include <set>
#include <list>
#include <vector>
#include <queue>
#include <iostream>

namespace valhalla {
    namespace strings {
        namespace unattended_customers_count {
            /*

            Given an integer representing the capacity of a cyber cafe and a sequence representing
            entry/exit logs of customers, find the total number of customers who could not get any
            computer.

            The first occurrence in the given sequence indicates the arrival, and the second
            occurrence indicates the departure for a customer. A customer cannot be serviced when
            the cafe capacity is full (when all computers are allocated).

            Input:

            sequence = "ABCDDCEFFEBGAG"
            capacity = 3

            Output: 2

            Explanation: Customers 'D' and 'F' left unattended


            Input:

            sequence = "ABCDDCBEFFEGAG"
            capacity = 2

            Output: 3

            Explanation: Customers 'C', 'D', and 'F' left unattended

            */

            int Solution::findUnattendedCustomers(std::string sequence, int capacity) {
                int unattended = 0;
                std::set<char> customers;
                std::list<char> unserviced;

                for (char chr : sequence) {
                    if (customers.erase(chr) == 0) {
                        std::list<char>::size_type size = unserviced.size();
                        unserviced.remove(chr);
                        if (unserviced.size() == size) {
                            // This is a new customer that is looking to be serviced
                            if (static_cast<int>(customers.size()) < capacity) {
                                // There is space for this customer
                                customers.insert(chr);
                            } else {
                                // Unable to service this customer for lack of space
                                unserviced.push_back(chr);
                            }
                        } else {
                            // A waiting customer has had enough of waitiung and is leaving
                            unattended++;
                        }
                    } else {
                        // The customer that was being service left so let us determine if we have
                        // anyone waiting
                        if (unserviced.empty() == false) {
                            customers.insert(unserviced.front());
                            unserviced.pop_front();
                            unattended++;
                        }
                    }
                }

                /*
                    The following solution doesn't know how to handle the following case:

                        String: EDAEBCCBAD
                        Capacity: 1
                        Output: 3

                    The above case generates an output of 4 instead of 3.

                std::priority_queue<int, std::vector<int>, std::greater<int>> unserviced;

                for (char chr : sequence) {
                    if (customers.erase(chr) == 0) {
                        customers.insert(chr);
                        if (static_cast<int>(customers.size()) > capacity) {
                            unattended++;
                        }
                    }
                }

                for (std::string::size_type i = 0; i < sequence.size(); i++)
                {
                    unserviced.push(static_cast<int>(i));
                }

                while (unserviced.empty() == false) {
                    std::cout << " " << unserviced.top();
                    unserviced.pop();
                }

                std::cout << std::endl;
                */

                return unattended;
            } // findUnattendedCustomers
        }
    }
}
