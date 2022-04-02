#ifndef __SEARCH_UTILS_H__
#define __SEARCH_UTILS_H__

#include <list>
#include <map>
#include <array>

#include "graph.h"

/**
 * @brief Create a graph map object using the passed list and create node method.  The map that will be created
 *   will create a bidirectional map.  The passed list is supposed to contain a list of lists that only contain
 *   two entries.  The first entry in the list will be the key of the map and the second element of the list
 *   will be passed to the create_node method to create the node object.
 * 
 * @todo Maybe replace the list<E> with an array<E,2> instead to insure that the passed list of array will only
 *   contain two entries per array in the list.
 * 
 * @tparam E The type of elements that are part of the list in the list
 * @tparam V The type of instances that will be created using the create_node method
 * @param elements The list of list that will be used to populate the valueMap
 * @param valueMap The map that will be created using the passed elements and create_node method
 * @param create_node This is used to create the node assiciated with the passed elements.
 */
template<typename E, typename V>
void create_graph_map(std::list<std::array<E,2>>& elements, std::map<E,node<V>>& valueMap, node<V> (*create_node)(E&)) {
    // iterate through all of the edges that were defined and provide the different connections
    // NOTE: Our list in this case will only contain two nodes per entry and each will be pointing to each other.
    for(auto itr = elements.begin() ; itr != elements.end() ; itr++) {
        std::array<E,2> edges = *itr;
        auto edgesItr = edges.begin();
        E element = *edgesItr++;

        if (valueMap.find(element) == valueMap.end()) {
            valueMap[element] = node<V>(create_node(element));
        }

        node<V>& src = valueMap[element];

        element = *edgesItr; // get the name of the destination city node
        if (valueMap.find(element) == valueMap.end()) {
            valueMap[element] = node<V>(create_node(element));
        }

        node<V>& dest = valueMap[element];

        // add an edge connection to each other
        src.add_edge(edge<V>(dest));
        dest.add_edge(edge<V>(src));
    }
}

#endif
