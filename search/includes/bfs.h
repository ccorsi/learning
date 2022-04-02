#ifndef __BFS_H__
#define __BFS_H__

#include <list>
#include <set>

#include "graph.h"

// TODO: wrap all of the different search implementations within the following namespace.
namespace valhalla {
    namespace search {
        namespace uniformed {

        }
    }
}

/*
function breath-first-search(initialState, goalTest)
    returns SUCCESS or FAILURE

    frontier = Queue.new(initialState)
    explored = Set.new()

    while not frontier.isEmpty():
        state = frontier.dequeue()
        explored.add(state)

        if goalTest(state):
            return SUCCESS(state)

        for neighbor in state.neighbors():
            if neighbor not in frontier and exploted:
                frontier.enqueue(neighbor)

    return FAILURE
*/

/**
 * @brief Recursive implementation of the breadth first search algorithm.  The issue with this implementation is that it 
 *  can generate a stack overflow for the instructions since it does not expand and contract as it reaches the end of the
 *  graph.  The larger that graph and the further away the goal the deeper the stack will be.
 * 
 * @tparam E The element that we are looking for, i.e., the goal
 * @param current 
 * @param goal 
 * @param path 
 * @param frontier 
 * @param visited 
 * @return true 
 * @return false 
 */
template<typename E>
bool bfs(node<E>& current, E& goal, std::list<E>& path, std::list<node<E> >& frontier = std::list<node<E> >(), std::set<E>& visited = std::set<E>()) {
    // check if the current not is the goal
    if (goal == current()) {
        // we are done, add the current node element to the path and return
        E& element = current();
        path.push_front(element);
        return true;
    }

    // add the current node to the visited set
    visited.insert(current());

    // get a reference to the edges
    const std::list<edge<E> >& edges = current.edges();

    // add the current node edges to the fronrier
    for( auto itr = edges.begin() ; itr != edges.end() ; itr++) {
        auto e = *itr;
        auto n = e.node();
        auto element = n();
        // only add the node if it hasn't already been processed.
        if (visited.find(element) != visited.end())
            frontier.push_back(n);
    }

    if ( ! frontier.empty() ) {
        node<E>& next = frontier.front();
        frontier.pop_front();
        return bfs(next, goal, path, frontier, visited);
    }

    return false;
}

template<typename E>
bool bfs_i(node<E>& root, E& goal, std::list<E>& path) {
    // This contains all the nodes that have already been visited/processed
    std::set<E>& visited;
    // This contains the nodes that are going to be visited/processed next
    // NOTE: this is going to be used like a queue
    std::list<node<E>& > frontier;
    // Add the root element to the frontier container
    frontier.push_back(root);
    // The following will produce a reference between the current and edge nodes
    std::map<E,E> parents;

    while ( ! frontier.empty() ) {
        // get a reference to the next node to be processed
        node<E>& current = frontier.front();
        // remove the reference to the retrieved node
        frontier.pop_front();
        // get a reference to the element that the node is referencing
        E& element = current();

        // check if we've reached the goal
        if (goal == current) {
            // we are done, we've found our destination
            E& prior = element;
            path.push_front(prior);
            // Generate the path using the parents map
            for(auto next = parents.find(prior); next != parents.end(); next = parents.find(prior) ) {
                prior = next->second;
                path.push_front(prior);
            }
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
            if (visited.find(c) == visited.end()) {
                // add the node to the frontiers
                frontier.push_back(next);
                // add a link between the element and c instances
                parents[c] = element;
            }
        }

    }

    // we were unable to find the goal from the pass root
    return false;
}

#endif
