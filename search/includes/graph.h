#if ! defined( __GRAPH_H__)
#define __GRAPH_H__

/**
 * @file graph.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include contains the required classes that can be used to create a graph.
 * @version 0.1
 * @date 2022-03-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */

// ################ include standard libraries ####################################

#include <list>
#include <vector>

// ################ include project libraries #####################################

#include "macros.h"

// required forward definition so that this can be included as part of the node class
template<typename E> class edge;

/**
 * @brief This class is associated to the node of a Graph.  This is used to create a Graph data structure
 * 
 * @tparam E This is the type of object that this node will contain
 */
template <typename E>
class node {
    E m_element;
    std::list<edge<E> > m_edges;

public:
    // required default constructor
    node() {}
    // simple ctor that is passed an element of type E
    // node(E element) : m_element(element) {}
    // simple constructor used to associate node with an element
    node(E& element) : m_element(element) {}
    // required default copy constructor
    node(const node<E>& other) : m_element(other.m_element) { m_edges.insert(m_edges.end(), other.m_edges.begin(), other.m_edges.end()); }
    // This will return the element associated with this node
    E& operator()() { /* cout << "Returning element: " << m_element << endl; */ return m_element; }
    // This is used for comparision of the nodes
    bool operator==(const node& other) { return m_element == other.m_element; }
    // We need to add edges associated with a given node
    void add_edge(const edge<E>& e) { m_edges.push_back(e); }
    // Get a reference to this nodes edges
    const std::list<edge<E> >& edges() { return m_edges; }
    // comparison operator
    bool operator()(const node<E>& other) const { return this->m_element < other.m_element; }
    // this is the friend operator used to compare two elements
    // friend bool operator<(const node<E>& lhs, const node<E>& rhs);
    // this class method will work as well as the above.
    bool operator<(const node<E>& rhs) const { return this->m_element < rhs.m_element; }
    bool operator>(const node<E>& rhs) const { return this->m_element > rhs.m_element; }
    std::ostream& operator<<(std::ostream& os) { os << this->m_element;  return os; }
};

template<typename E>
std::ostream& operator<<(std::ostream& os,const node<E>& n) {
    // TODO: Why do I actually need to use a copy ctor to be able to get around a compiler error
    node<E> other(n);
    E e = other();
    os << "node element: " << e;
    return os;
}

// This is the less than operator that could be used within a set container
// template<typename E>
// bool operator<(const node<E>& lhs, const node<E>& rhs) { return lhs(rhs); }

/**
 * @brief This is the edge that connects two node within a Graph.
 * 
 * @tparam E The type of element that the edges' node is associated with.
 */
template<typename E>
class edge {
    // reference to the node associated with this given edge
    node<E>* m_node;
public:
    // required default constructor
    edge() : m_node(nullptr) {}
    // required default copy constructor
    edge(const edge<E>& other) : m_node(other.m_node) {}
    // simple constructor to assign this edge associated node
    edge(node<E>& n) : m_node(&n) {}
    // return the associated node for this edge
    node<E>& node() { return *m_node; }
    // return the associated node for this edge
    edge<E>& operator()() { return *this; }
};

namespace valhalla {
    namespace search {
        // Here is another attempt at creating the different search algorithms that can be used with a large enough
        // data set that doesn't fit within a processes memory space.

        /**
         * @brief This is an implementation of the depth first search (DFS) that uses templates.  The objective of this
         *      implementation is to be able to provide flexibility to the developer as well as be able to minimize the
         *      amount of memory that is used by the implementation such that one can manage to search through a large
         *      data set.
         *
         *      This implementation will expect some effort from the developer that provides the ability for this
         *      implementation to properlt apply this search on.  The developer is then responsible for the for
         *      providing these different types.  They are the Element, Node, Manager, Path and Edges.   The
         *      Path and Edges types have default definitions while the others are required by the developer.
         *      Let us now explain what each of these types are and how they are used.
         *
         *      The Element type is essentially the type that will be stored within the Node type and is the
         *      information that will be stored within the Path type.
         *
         *      The Node is essentially the type that wraps its associated Element.  This will be used by the
         *      Manager and Checker types.  To be able to get a reference to the wrapping Element, the Node
         *      type will need to implement the () operator that will return a reference to the Element type.
         *
         *          typename Node {
         *              Element& operator()() const;
         *          }
         *
         *      The Manager type will be used to return an instance of Edges that contains all of the nodes
         *      associated with a given Node.  The Manager type will do this using a (Node&) operator that
         *      will return an instance of the Edges type.
         *
         *          typename Manager {
         *              Edges operator()(Node&) const;
         *          }
         *
         *      The Checker type will be used to determine if a given Node has already be processed.  This will
         *      be done using the (Node&) operator.   It will also be responsible of managing the current set
         *      of processed Nodes.  This will be done using the processed(Node&) method that is expected to
         *      be implemented by the Checker type.
         *
         *          typename Checker {
         *              bool operator()(Node&node) const;
         *              void processed(Node&);
         *          }
         *
         *      The Path type will contain the path that was needed to get from the passed root to the given
         *      goal.  This is a list of Element instances that one can then iterate over to see what the
         *      required pass is needed to reach the goal.  This uses the default std::vector<Element> type.
         *
         *      The Edges type will contain all of the Nodes that are associated with the a given Node.  This
         *      container will not reference the Node but will only contain the Nodes that are associated with
         *      the requested Node.  This type uses std::vector<Node> by default.
         *
         * @tparam Element  The type of element that is stored within each node
         * @tparam Node The type of node that will contain a instance of the element
         * @tparam Goal This is used to determine to check if we've reached our goal
         * @tparam Manager A class that will be used to extract the edges associated with a given node
         * @tparam Path The class type that the resulting path will be returned
         * @tparam Edges A class that will be returned when using the Manager class
         * @tparam Checker A class that is used to determine if a given node has already been processed
         */
        template<typename Element, typename Node, typename Goal, typename Manager, typename Checker,
                 typename Path = std::vector<Element>, typename Edges = std::vector<Node> >
        class bfs {
        private:
            bool _search(Node& node, Goal& goal, Path& path, Manager& manager, Checker& checker) {

                if (goal(node)) {
                    // we've found the goal and we are now going to add this node element to the path that will be returned
                    path.insert(path.begin(), node());
                    return true;
                } else {
                    // add the current value to the list of processed values
                    checker(node);

                    // we need to retreive the edges assocuiated with this class.
                    Edges edges = manager(node);

                    for(auto current = edges.begin() ; current != edges.end() ; current++) {
                        if (checker(*current)) {
                            // we've already processed this Element
                            continue;
                        }

                        if (_search(*current, goal, path, manager, checker)) {
                            // we've found the goal that we were looking for.
                            path.insert(path.begin(), node());
                            return true;
                        }
                    }
                }

                return false;
            }

        public:
            bfs() = default; // we don't have anything that needs to be stored within our instance

            /**
             * @brief This is the search method that is called to find the shortest path associated
             *      to the graph that starts at the passed root.  It will use the goal to determine
             *      if we've found the end point of the search.  It will then return the path
             *      associated with the given root and goal.
             *
             * @param root The root of the graph that will be searched
             * @param goal The goal node that we are looking for within the passed graph
             * @param manager The manager instance used to retrieve a nodes edges
             * @param checker The checker instance used to determine if a node was already processed
             * @param path The shortest path required to reach the goal
             *
             * @return True, if a path was found for the given goal, else false
             */
            bool search(Node& root, Goal goal, Manager& manager, Checker& checker, Path& path) {
                return _search(root, goal, path, manager, checker);
            }

        };

        namespace informed {
            namespace bfs {
                /*
                    NOTE: While the design of the new version of the node class for the bfs implementation is better than
                          the original version.  It still has an issue that will become apparent when we are processing a
                          very large graph.  THe associated edges will be avaliable throughout the life of the graph.  This
                          can lead to an exhaustion of heap memory if we have not found the goal while there are still nodes
                          to process.  The solution can be to return a non-reference container of edges.  This would reduce
                          the amount of heap memory that will be used and should provide some relief when the graph is fairly
                          large.  This could still exhaust the heap memory if the is a really large graph that needs to be
                          transversed.

                    NOTE: Even though the following implementation was supposed to be a better version of the original one.
                          I still don't think that this implementation is correct in the sense that it is not useful enough
                          within an environment in which the data space is too large to be placed within a process memory
                          space.  I'd like to be able to create something that would be able to process a much greater set
                          of data before it exhaust the system memory.
                */

                /**
                 * @brief This is the node that the bfs class will be using to store and manipulate.
                 *  It will use the Manager class to retrieve a container with this node edges.  It
                 *  is expected that it will implement a no-args operator() that will return an instance
                 *  of a vector class.
                 *
                 * @tparam E The type that will be referenced by this node
                 * @tparam Manager The class used to retrieve this node associated edges
                 * @tparam Container The container class that will be returned by the Manager class
                 */
                template<class E, class Manager, class Container = std::vector<E> >
                class node {
                    // the key of this node
                    E m_key;
                    // will contain the edges associated with this node key
                    std::vector<node> m_edges;
                    // used to retreive edges associated with this node key
                    Manager m_manager;
                public:
                    // ctor
                    node(E key) : m_key(key) {}
                    node(const node& other) : m_key(other.m_key) { m_edges.insert(m_edges.end(), other.m_edges.begin(), other.m_edges.end()); }

                    // operators
                    CONSTEXPR14 bool operator==(const node& other) const { return m_key == other.m_key; }

                    // user defined methods
                    const std::vector<node>& get_edges() const {
                        if (! m_edges.empty() ) {
                            // we've already generated the edges associated with this node thus return a reference to it.
                            return m_edges;
                        } else {
                            // retreive all of the edges associated within this key
                            Container values = m_manager(m_key);
                            // create nodes associated with these edges
                            for(auto itr = values.begin() ; itr != values.end() ; itr++) {
                                m_edges.push_back(node(*itr));
                            }
                            // return a reference to the generated edges
                            return m_edges;
                        }
                    }
                };
                class bfs {
                public:
                    bfs() = default;
                };
            };

            /**
             * @brief this class will be used within a informed type search where
             *  the containing type will be associated to a key value.  The container
             *  by default will just be the key.  The comparison method will be used
             *  to sort the nodes by key value.
             *
             * @tparam K the type of the key that will be used
             * @tparam C the type of instance that will contain the key
             * @tparam Compare a functional class that will be used to compare instances
             */
            template<class K = int, class C = int, class Compare = std::less<C>>
            class inode {
                C m_data;
                Compare m_cmp;
            public:
                inode(C data) : m_data(data) {}

                /**
                 * @brief This operator will be used to call the equality operator
                 *  of the containing class
                 *
                 * @param other the other instance that we are comparing too.
                 * @return true if the two instances are the same else
                 * @return false if the two instances are not the same
                 */
                bool operator==(const inode<K,C,Compare>& other) {
                    return m_data == other.m_data;
                }

                /**
                 * @brief This operator will return the key associated with the
                 *      instance that is stored within this node.
                 *
                 * @return CONSTEXPR14&  reference to this node key value.
                 */
                CONSTEXPR14 K operator()() const { return m_data(); }

                CONSTEXPR14 bool operator()(const inode<K,C,Compare>& other) const {
                    return false;
                }
            };
        }
        namespace uniformed {
            // forward declaration
            class inode;

            /**
             * @brief This is a generic node that only contains a key that maps to an actual
             *  object that is accessible by the users of this instance.  The idea behind
             *  using a key instead of the data itself is to make it easier to include edges
             *  to this node.  The initial implementation had the added issue of not being
             *  able to create the circular references that a graph can implement.  This
             *  added complexity was not something that should be implemented using a graph.
             *  It became apparent that using key values instead of whole instances is a
             *  better implementation.  This allows for uses to be able to create a seperate
             *  container that maps the keys to the actual instances.  This can be used to
             *  better serve implementations that require updates to current nodes since one
             *  has been selected.  An example is the uniform cost search that requires all
             *  to be explored nodes to be updated whenever a node was selected.
             *
             */
            class inode {
            private:
                int m_key;
                std::vector<inode> m_edges;
            public:
                // #################### ctor ################################
                inode(int key) : m_key(key) {}

                // ################# user defined methods ###################

                /**
                 * @brief This method is used to add a edge to the given node
                 *
                 * @param key integer index of the edge added to this node
                 */
                void add_edge(int key) { m_edges.push_back(inode(key)); }

                /**
                 * @brief This method will return all of the edges associated with this
                 *  node.
                 *
                 * @return const vector<inode>& reference to this node edges
                 */
                const std::vector<inode>& edges() const { return m_edges; }

                // ######################### operators #################################

                /**
                 * @brief Operator used to determine if two nodes are equivalent using only
                 *  the value of the key as a comparision
                 *
                 * @param o a reference to the another inode to compare with
                 * @return true if this and the other inode are the same
                 * @return false if this and the other inode are not the same
                 */
                bool operator==(const inode& o) const { return m_key == o.m_key; }

                /**
                 * @brief Operator used to sort two nodes and will use the key to
                 *  sort any inode instances.
                 *
                 * @param o a reference to the other inode to compare with
                 * @return true if the current inode is less than the other inode
                 * @return false if the current inode is greater than or equal to
                 *      the passed inode
                 */
                bool operator<(const inode& o) const { return m_key < o.m_key; }

                /**
                 * @brief This operator will return this inode key value.
                 *
                 * @return int the key value of this inode
                 */
                int operator()() { return m_key; }

                /**
                 * @brief This method is equivalent to the implemented operator<
                 *  operator of this class
                 *
                 * @param other another instance of inode that we are comparing
                 * @return true if this instance of inode is less than the passed
                 *          instance of inode
                 * @return false if this instance of inode is greater than or equal
                 *          to the passed inode instance
                 */
                bool operator()(const inode& other) const {
                    return m_key < other.m_key;
                }
            };
        }
    }
}
#endif
