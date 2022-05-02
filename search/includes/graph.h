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
        namespace uniformed {
            // forward declaration
            class inode;

            /**
             * @brief This is a generic node that only contains a key that maps to an actual
             *  object that is accessible by the users of this instance.
             *
             */
            class inode {
            private:
                int m_key;
                std::vector<inode> m_edges;
            public:
                inode(int key) : m_key(key) {}
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
                /**
                 * @brief Operator used to determine if two nodes are equivalent using only
                 *  the value of the key as a comparision
                 *
                 * @param o a reference to the another inode to compare with
                 * @return true if this and the other inode are the same
                 * @return false if this and the other inode are not the same
                 */
                bool operator==(const inode& o) const { return m_key == o.m_key; }
                bool operator<(const inode& o) const { return m_key < o.m_key; }
            };
        }
    }
}
#endif
