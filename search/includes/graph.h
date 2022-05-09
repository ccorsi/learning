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

#include <list>
#include <vector>

#include "macros.h"

template<typename E>
class edge;

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
        namespace informed {
            namespace bfs {
                /**
                 * @brief This is the node that the bfs class will be used to store and manipulate.
                 *  It will use the Manager class to retrieve a container with this node edges.  It
                 *  is expected that it will implement a no-args operator() that will return an instance
                 *  of a vector class.
                 *
                 * @tparam E The type that will be referenced by this node
                 * @tparam Manager The class used to retrieve this node edges
                 */
                template<class E, class Manager>
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
                            return m_edges;
                        } else {
                            // retreive all of the edges associated within this key
                            vector<E> values = m_manager(m_key);
                            // create nodes associated with these edges
                            for(auto itr = values.begin() ; itr != values.end() ; itr++) {
                                m_edges.push_back(node(*itr));
                            }
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
