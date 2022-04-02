/**
 * @file dls.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief 
 * @version 0.1
 * @date 2022-03-17
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef __DLS_H__
#define __DLS_H__

#include <list>
#include <map>
#include <set>

/*
function depth-limited-search(initialState, goalTest, depthLimit)
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

/**
 * @brief This is an implementation of the depth limited search algorithm.
 * 
 * @tparam E this is the type of the element of the object we are looking for
 * @param current this is the current node that we are checking 
 * @param goal this is used to check if we've reached the goal
 * @param depth This is the current depth of the search
 * @param path This will contain the path to the goal
 * @return true If we've found the goal
 * @return false If we didn't find the goal
 */
template<typename E>
bool dls_r(node<E>& root,E& goal, std::list<E>& path, int depth, std::set<E>& visited = std::set<E>(),
           std::list<std::pair<node<E>,int> > frontier = std::list<std::pair<node<E>,int> >()) {

    // TODO: The following implementation is incomplete and needs to be updated or removed from the source code.
    // check if we've reach the limit of the search
    if (depth < 1) {
        // we've reach the limit of our search without finding the goal destination
        return false;
    }

    // Check if the current node is the goal we are searching for
    if (goal == current) {
        // we found the goal so add it to the path and return true.
        path.push_front(current()); 
        return true;
    }

    // we need to decrement the current depth
    depth--;

    // add the current node edges to the frontier
    std::list<edge<E> >& edges = current.edges();

    for (auto itr = edges.begin() ; itr != edges.end() ; itr++) {
        // get a reference to the node of this edge
        node<E>& next = (*itr)();
        // get a reference to the node's element
        E& element = next();
        if (visited.find(element) != visited.end()) {
            // add the current node to the frontier
            frontier.push_front(std::make_pair(next, depth));
        }
    }

    if ( ! frontier.empty() ) {
        // we still have some entries to check
        std::pair<node<E>,int>& next = frontier.front();
        depth = next.second;
        frontier.pop_front();
        return dls_r(next.first, goal, path, depth, visited, frontier);
    }

    return false;
}

/**
 * @brief This is an implementation of the iterative version of the depth first limited search algorithm.
 * 
 * @tparam E The type of object that is containerd within the node
 * @param root The starting element of the search
 * @param goal The element used to check for the destination node 
 * @param path The path used to get from the source to the destination
 * @param depth The maximum depth that that search is allowed to perform
 * @return true If we've found our goal
 * @return false else false
 */
template<typename E>
bool dls(node<E>& root, E& goal, std::list<E>& path, int depth) {
    std::set<E> visited;
    std::list<std::pair<node<E>,int> > frontier;
    std::map<E,E> parents;
    frontier.push_front(make_pair(root, 1));
    visited.insert(root());

    while ( ! frontier.empty() ) {
        std::pair<node<E>,int> front = frontier.front();
        // Get a reference to the next node
        node<E> current = front.first;
        // Remove the referenced node from the stack
        frontier.pop_front();

        // Get a reference to the current node element
        E& currentElement = current();

        // Check if the current node is the goal we are searching for
        if (goal == currentElement) {
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

        // Store all of the current node neighbors
        // bool found = false;
        // get a reference to all of this nodes edges
        auto edges = current.edges();

        // Get the popped entry depth
        int currentDepth = front.second;

        if (currentDepth++ < depth) {
            for( auto itr = edges.begin() ; itr != edges.end() ; itr++ ) {
                edge<E>& edge = *itr;
                node<E>& next = edge.node();
                E& element = next();
                if (visited.find(element) == visited.end()) {
                    frontier.push_back(make_pair(next, currentDepth));
                    parents[element] = currentElement;
                    visited.insert(element);
                }
            }
        }
    }

    // none of the path contained the destination.
    return false;
}

#endif
