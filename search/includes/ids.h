#ifndef __IDS_H__
#define __IDS_H__

/**
 * @file ids.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include file contains an implementation of the iterative deepening search algorithm.
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <list>
#include <map>
#include <set>

#include "graph.h"
#include "dls.h"

/**
 * @brief This an implementation of the iterative deepening search algorithm
 * 
 * @tparam E This is the type of class that the node will be referencing
 * @param root This is the starting point of the search
 * @param goal This is the goal element that we are looking for
 * @param path The result path from the root to the goal
 * @param maxDepth This is the maximum depth that we will be perform the search on
 * @param startDepth This is the start depth that will be used 
 * @return true if we've found the goal within the maximum depth
 * @return false if we didn't find the goal for the given depth
 */
template<typename E>
bool ids(node<E>& root, E& goal, std::list<E>& path, int maxDepth, int startDepth = 0) {
    
    while (startDepth <= maxDepth) {
        if (dls(root, goal, path, startDepth)) {
            // we've found the path at depth startDepth.  This does not mean that startDepth was the minimum
            // depth required to be able to find the path but that it is a ceiling for the returned path
            return true;
        }
        // update the start depth
        startDepth++; // TODO: should we consider a smarter way of increasing the depths?
    }

    return false;
}

#endif
