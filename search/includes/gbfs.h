/**
 * @file gbfs.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include file contains a template implementation of the Greedy Best First Search algorithm.
 * @version 0.1
 * @date 2022-04-05
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __GBFS_H__
#define __GBFS_H__

/**
 * @brief This include will contain an implementation of the Greedy Best First Search algorithm.
 *
 */

/*
function Greedy-Best-First-Search(initialState, goalTest)
    returns SUCCESS or FAILURE: // Cost f(n) = h(n)

    frontier = Heap.new(initialState)
    explored = Set.new()

    while not frontier.isEmpty():
        state = frontier.deleteMin()
        explored.add(state)

        if goalTest(state):
            return SUCCESS(state)

        for neighbor in state.neighbors():
            if neighbor not in frontier or explored:
                frontier.insert(neighbor)
            else if neighbor in frontier:
                frontier.decreaseKey(neighbor)

    return FAILURE
*/

template<typename E, typename K>
bool gbfs(node<E>& root, E& goalTest) {
    return false;
}

#endif
