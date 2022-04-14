/**
 * @file ucs.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This include an implementation of the uniform cost search algorithm
 * @version 0.1
 * @date 2022-03-28
 * 
 * @copyright Copyright (c) 2022 Claudio Corsi
 * 
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __UCS_H__
#define __UCS_H__

/*
function uniform-cost-search(initialState, goalTest)
    returns SUCCESS or FAILURE  // Cost f(n) = g(n)

    frontier = Heap.new(initialState)
    explored = Set.new()

    while not frontier.isEmpty():
        state = frontier.deleteMin()
        explored.add(state)

        if goalTest(state):
            return SUCCESS(state)

        for neighbor in state.neighbors():
            if neighbor not in frontier and explored:
                frontier.insert(neighbor)
            else if neighbor in frontier:
                frontier.decreaseKey(neighbor)

    return FAILURE
*/

#include <ostream>
#include <list>
#include <map>
#include <set>

#include "macros.h"
#include "graph.h"
#include "pr_queue.h"

/**
 * @brief The class is used to wrap a node and its key that is used by the priority queue
 * 
 * @tparam E This is type of element that the node contains
 * @tparam K This is the type of the key that is used to sort by the priority queue
 */
template<typename E, typename K>
class wrapper {
private:
    node<E>& m_node;
    K        m_key;
public:
    // default ctor
    wrapper() {}

    /**
     * @brief Default copy construct for a new wrapper object
     * 
     * @param other A reference to the other wrapper instance that will be copied to this instance
     */
    wrapper(const wrapper<E,K>& other) : m_node(other.m_node), m_key(other.m_key) {
        // cout << "Calling default copy ctor for wrapper. Copied: " << other.m_node() << " to " << m_node() << endl;
    }
    
    // default move ctor
    /**
     * @brief Default move construct for a new wrapper object
     * 
     * @param other A reference to the other wrapper instance that will be moved to this instance
     */
    // TODO: does removing the default move implementation resolve the exception that I am seeing?
    wrapper(const wrapper<E,K>&& other) noexcept : m_node(std::move(other.m_node)), m_key(std::move(other.m_key)) {
        // cout << "Calling default move ctor for wrapper. Moved: " << other.m_node() << " to " << m_node() << endl;
    }
    
    // user specific ctor
    /**
     * @brief Construct for a new wrapper object that will set the node and key values that are used by the
     *      priority queue container
     * 
     * @param n A reference to the node instance that wraps the element
     * @param key The value of the key that this node should be referenced as
     */
    wrapper(node<E>& n, K key) : m_node(n), m_key(key) {
        // cout << "Calling user specific ctor for wrapper setting m_node from " << n() << " to " << m_node() << " and m_key: " << m_key << endl;
    }
    
    // This is used by the priority queue to sort the entries within the container
    CONSTEXPR14 bool operator<(const wrapper<E,K>& other) const { return this->m_key < other.m_key; }

    // This is used by the priority queue to sort the entries within the container
    CONSTEXPR14 bool operator>(const wrapper<E,K>& other) const { return this->m_key > other.m_key; }
    
    // The next four operators are used to update the key value whenever this wrapper is found within the priority queue container
    wrapper<E,K> operator+(const wrapper<E,K>& other) { m_key += other.m_key; return *this; }
    wrapper<E,K> operator-(const wrapper<E,K>& other) { m_key -= other.m_key; return *this; }
    wrapper<E,K> operator+(const K& key) { m_key += key; return *this; }
    wrapper<E,K> operator-(const K& key) { m_key -= key; return *this; }
    
    /**
     * @brief This method will return a reference to the wrapping node
     * 
     * @return const node<E>& 
     */
    const node<E>& node() const { return m_node; }
    
    /**
     * @brief This will return a reference to the wrapping key
     * 
     * @return const K& 
     */
    const K& key() const { return m_key; } 

    /**
     * @brief This operator is used to determine if the other wrapper contains the same node as this one
     * 
     * @param other 
     * @return CONSTEXPR14 
     */
    CONSTEXPR14 bool operator==(const wrapper<E,K>& other) { return m_node == other.m_node; }

    /**
     * @brief This operator is used to assign the values from another wrapper to this wrapper instance.
     * 
     * @param other This is the wrapper instance that will be assigned to this wrapper
     * @return wrapper<E,K>& returns a reference to this wrapper
     */
    wrapper<E,K>& operator=(const wrapper<E,K>& other) { if (this != &other) { m_node = other.m_node; m_key = other.m_key; } return *this; }

    /**
     * @brief This operator will be used to output the element and its key for this wrapper
     * 
     * @param os 
     * @return ostream& 
     */
    std::ostream& operator<<(std::ostream& os) { os << "node: " << m_node() << ", key: " << m_key; return os; }
};

template<typename E,typename K>
std::ostream& operator<<(std::ostream& os, const wrapper<E,K>& w) {
    const node<E>& n = w.node();
    os << n;
    os << w.key();
    // os << "node: " << n();
    // os << ", key: " << w.key();
    return os;
}

/**
 * @brief This is supposed to replace the standard priority queue implementation but it seems to much
 *      for what is required by the ucs algorithm
 * 
 * @tparam _Type 
 * @tparam _Container 
 * @tparam std::less<typename _Container::value_type> 
 */
// template<class _Type, class _Container = std::vector<_Type>, class _Pr = std::less<typename _Container::value_type> >
// class priority_queue {
// public:
//     using value_type      = typename _Container::value_type;
//     using reference       = typename _Container::reference;
//     using const_reference = typename _Container::const_reference;
//     using size_type       = typename _Container::size_type;
//     using container_type  = _Container;
//     using value_compare   = _Pr;


//     static_assert(is_same_v<_Ty, value_type>, "container adaptors require consistent types");

//     priority_queue() = default;

//     explicit priority_queue(const _Pr& _Pred) noexcept(
//         is_nothrow_default_constructible_v<_Container>&& is_nothrow_copy_constructible_v<value_compare>) // strengthened
//         : c(), comp(_Pred) {}

//     priority_queue(const _Pr& _Pred, const _Container& _Cont) : c(_Cont), comp(_Pred) {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     priority_queue(const _Pr& _Pred, _Container&& _Cont) : c(_STD move(_Cont)), comp(_Pred) {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _InIt>
//     priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred, const _Container& _Cont) : c(_Cont), comp(_Pred) {
//         c.insert(c.end(), _First, _Last);
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _InIt>
//     priority_queue(_InIt _First, _InIt _Last) : c(_First, _Last), comp() {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _InIt>
//     priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred) : c(_First, _Last), comp(_Pred) {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _InIt>
//     priority_queue(_InIt _First, _InIt _Last, const _Pr& _Pred, _Container&& _Cont) : c(_STD move(_Cont)), comp(_Pred) {
//         c.insert(c.end(), _First, _Last);
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     explicit priority_queue(const _Alloc& _Al) noexcept(is_nothrow_constructible_v<_Container, const _Alloc&>&&
//             is_nothrow_default_constructible_v<value_compare>) // strengthened
//         : c(_Al), comp() {}

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     priority_queue(const _Pr& _Pred, const _Alloc& _Al) noexcept(is_nothrow_constructible_v<_Container, const _Alloc&>&&
//             is_nothrow_copy_constructible_v<value_compare>) // strengthened
//         : c(_Al), comp(_Pred) {}

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     priority_queue(const _Pr& _Pred, const _Container& _Cont, const _Alloc& _Al) : c(_Cont, _Al), comp(_Pred) {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     priority_queue(const _Pr& _Pred, _Container&& _Cont, const _Alloc& _Al) : c(_STD move(_Cont), _Al), comp(_Pred) {
//         _STD make_heap(c.begin(), c.end(), comp);
//     }

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     priority_queue(const priority_queue& _Right, const _Alloc& _Al) : c(_Right.c, _Al), comp(_Right.comp) {}

//     template <class _Alloc, std::enable_if_t<std::uses_allocator_v<_Container, _Alloc>, int> = 0>
//     priority_queue(priority_queue&& _Right, const _Alloc& _Al) noexcept(
//         is_nothrow_constructible_v<_Container, _Container, const _Alloc&>&&
//             is_nothrow_move_constructible_v<value_compare>) // strengthened
//         : c(_STD move(_Right.c), _Al), comp(_STD move(_Right.comp)) {}

//     _NODISCARD bool empty() const noexcept(noexcept(c.empty())) /* strengthened */ {
//         return c.empty();
//     }

//     _NODISCARD size_type size() const noexcept(noexcept(c.size())) /* strengthened */ {
//         return c.size();
//     }

//     _NODISCARD const_reference top() const noexcept(noexcept(c.front())) /* strengthened */ {
//         return c.front();
//     }

//     void push(const value_type& _Val) {
//         c.push_back(_Val);
//         _STD push_heap(c.begin(), c.end(), comp);
//     }

//     void push(value_type&& _Val) {
//         c.push_back(_STD move(_Val));
//         _STD push_heap(c.begin(), c.end(), comp);
//     }

//     template <class... _Valty>
//     void emplace(_Valty&&... _Val) {
//         c.emplace_back(_STD forward<_Valty>(_Val)...);
//         _STD push_heap(c.begin(), c.end(), comp);
//     }

//     void pop() {
//         _STD pop_heap(c.begin(), c.end(), comp);
//         c.pop_back();
//     }

//     void swap(priority_queue& _Right) noexcept(
//         _Is_nothrow_swappable<_Container>::value&& _Is_nothrow_swappable<_Pr>::value) {
//         _Swap_adl(c, _Right.c);
//         _Swap_adl(comp, _Right.comp);
//     }

// protected:
//     _Container c{};
//     _Pr comp{};
// };

/**
 * @brief 
 * 
 * @tparam E The is the type of the element that the node reference
 * @tparam K This is the type of the key associated with the node's element
 * @tparam C This is the operation that is used to do something that I don't remember
 * @param root This referenvce the starting node
 * @param goal This will be used to determine if we've reached the goal
 * @param path This will contain the path that is required to get from the source to the destination
 * @param c This is the operator that will be used to determine something
 * @return true If we were able to find the goal given the passed root node
 * @return false This is returned if we were unable to find the goal for the given root
 */
template<typename E, typename K, typename C>
bool ucs(node<E>& root, E& goal, std::list<E>& path, C& c) {
    std::set<E> visited;
    priority_queue_ex<wrapper<E,K>> frontier;
    std::map<E,E> parents;
    node<E>& current = root;

    visited.insert(current);
    frontier.push(wrapper<E,K>(current));

    while ( ! frontier.empty() ) {
        wrapper<E,K> w = frontier.top(); // get the next element 
        frontier.pop(); // remove the top element from the priority queue
        node<E>& current = w.node(); // get a reference to the wrapped node
        E currentElement = n(); // get a reference to the node element
        K currentKey = w.key(); // get current wrapper key value

        if (currentElement == goal) {
            E& prior = currentElement;
            path.push_front(prior);
            // Generate the path using the parents map
            for(auto next = parents.find(prior); next != parents.end(); next = parents.find(prior) ) {
                prior = next->second;
                path.push_front(prior);
            }
            // we found the goal so we are done.
            return true;
        }

        // get a reference to all of this nodes edges
        auto edges = current.edges();

        for( auto itr = edges.begin() ; itr != edges.end() ; itr++ ) {
            edge<E>& edge = *itr;
            node<E>& next = edge.node();
            E& element = next();
            auto itr = frontier.find(wrapper<E,K>(next));
            if (visited.find(element) == visited.end()) {
                frontier.push_back(wrapper<E,K>(next, currentKey));
                parents[element] = currentElement;
            } else if (itr != frontier.end()) {
                
            }
        }

    }

    return false;
}

#endif
