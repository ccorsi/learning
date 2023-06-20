/**
 * @file alive_probability.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains a solution to the problem https://www.techiedelight.com/?problem=AliveProbability
 * @version 0.1
 * @date 2023-06-20
 *
 * @copyright Copyright (c) 2023 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

#include "alive_probability.h"

namespace valhalla {
    namespace matrices {
        namespace alive_probability {
            /*

            An island is in the form of an `N × N` square matrix, and a person is standing inside
            the matrix. The person can move one step in any direction (right, left, top, down) in
            the matrix and each step carry equal probability, i.e., 1/4 or 0.25. Calculate the
            probability that the person is alive after walking `n` steps on the island, provided
            that the person dies on stepping outside the matrix.

            Input:

            N = 2			(Matrix dimentions)
            n = 1			(Total number of steps)
            (x, y) = (0, 0)	(Starting coordinates)

            Output: 0.5		(Alive probability)


            Input: N = 3, n = 1, (x, y) = (1, 1)
            Output: 1

            Input: N = 3, n = 3, (x, y) = (0, 0)
            Output: 0.25

            */

            double Solution::findProbability(int N, int n, int x, int y) {
                double probability = -1.0;



                return probability;
            } // findProbability
        }
    }
}
