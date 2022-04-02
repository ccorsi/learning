#ifndef __DFS__
#define __DFS__

/**
 * @file dfs.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief include file that contain an template implementation of depth first search 
 * @version 0.1
 * @date 2022-03-10
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/*
function depth-first-search(initialState, goalTest)
    returns SUCCESS or FAILURE

    frontier = Stack.new(initialState)
    explored = Set.new()

    while not frontier.isEmpty():
        state = frontier.pop()
        explored.add(state)

        if goalTest(state):
            return SUCCESS(state)

        for neighbor in state.neighbors():
            if neighbor not in frontier and exploted:
                frontier.push(neighbor)

    return FAILURE
*/

#include <list>
#include <set>
#include <map>

#include "debug.h"

/**
 * @brief This is a recursive implementation of the depth first search algorithm.
 * 
 * @tparam E the type of element that it part of the graph
 * @param current the current node that we are checking
 * @param goal the goal that we are searching for
 * @param path the path that will contain the path of the goal path
 * @param visited the elements that have already visited
 * @param frontier the nodes that we are going to be checked next
 * @return true if we are able to find the goal
 * @return false unable to find the goal
 */
template<typename E>
bool dfs_r(node<E>& current, node<E>& goal, std::list<E>& path, std::set<E> visited = std::set<E>(), std::list<node<E>> frontier = std::list<node<E>>()) {
    // Check if the current node is the goal we are searching for
    if (goal == current) {
        DEBUGMSHG("found path");
        // we found the goal so add it to the path and return true.
        path.push_front(current()); 
        return true;
    }

    // add the current node edges to the frontier
    std::list<edge<E>>& edges = current.edges();

    for (auto itr = edges.begin() ; itr != edges.end() ; itr++) {
        // get a reference to the node of this edge
        node<E>& next = (*itr)();
        // get a reference to the node's element
        E& element = next();
        if (visited.find(element) != visited.end()) {
            // add the current node to the frontier
            frontier.push_front(next);
        }
    }

    if ( ! frontier.empty() ) {
        // we still have some entries to check
        node<E>& next = frontier.front();
        frontier.pop_front();
        return dfs_r(next, goal, path, visited, frontier);
    }

    return false;
}

/**
 * @brief 
 * 
 * @tparam E 
 * @param root 
 * @param goal 
 * @param path 
 * @return true 
 * @return false 
 */
template<typename E>
bool dfs_i(node<E>& root, node<E>& goal, std::list<E>& path) {
    std::set<E> visited;
    std::list<node<E>> frontier;
    std::map<E,E> parents;
    frontier.push_front(root);

    while ( ! frontier.empty() ) {
        // Get a reference to the next node
        node<E> current = frontier.front();
        // Remove the referenced node from the stack
        frontier.pop_front();

        // Get a reference to the current node element
        E& currentElement = current();

        // Check if the current node is the goal we are searching for
        if (goal == current) {
            DEBUGMSHG("found path");
            E& prior = currentElement;
            path.push_front(prior);
            // Generate the path using the parents map
            for(auto next = parents.find(prior); next != parents.end(); next = parents.find(prior) ) {
                prior = next->second;
                path.push_front(prior);
            }
            // we are done so return true.
            return true;
        }

        visited.insert(currentElement);

        // Store all of the current node neighbors
        // bool found = false;
        // get a reference to all of this nodes edges
        auto edges = current.edges();

        for( auto itr = edges.begin() ; itr != edges.end() ; itr++ ) {
            edge<E>& edge = *itr;
            node<E>& next = edge.node();
            E& element = next();
            if (visited.find(element) == visited.end()) {
                frontier.push_back(next);
                parents[element] = currentElement;
            }
        }
    }

    // none of the path contained the destination.
    return false;
}

/**
 * @brief This method implement depth first search recursively.
 * 
 * @tparam E The element contained within the node class
 * @param current This is the current node we are looking at
 * @param goal This is a class that implements the operator== implemented by the E class
 * @param path This will contain the path to the goal
 * @param visited This contains all of the nodes that have been processed
 * @return true if we found the goal
 * @return false if no goal was found
 */
template<typename E>
bool dfs(node<E>& current, node<E>& goal, std::list<E>& path, std::set<E>& visited) {
    E& element = current();
    if (goal == current) {
        // we are done, we've found the required path
        path.push_front(element);
        return true;
    }
 
    // add the current node to the visited container
    visited.insert(element);
 
    // get a reference to edges associated with this node
    auto edges = current.edges();
    for (auto itr = edges.begin() ; itr != edges.end() ; itr++) {
        edge<E>& edge = *itr;
        node<E>& next = edge.node();
        E& c = next();
        if (visited.find(c) == visited.end() && dfs(next, goal, path, visited)) {
            // we are done, we've found the required path
            path.push_front(element);
            return true;
        }
    }

    // The current is the end of the line so we return false
    return false;
};

#endif
