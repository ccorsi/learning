/**
 * @file pr_queue.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This file contains the implementation of the template priority queue that is used by
 *      the different search algorithms.  This is basically a sub-class of the standard
 *      priority queue implementation.  It offers the ability to update entries within the
 *      priority queue.  This is required for several of the different search algorithms.
 * @version 0.1
 * @date 2022-04-06
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */
#ifndef __PR_QUEUE_H__
#define __PR_QUEUE_H__

/*
TODO: The following extension of the standard priority queue implementation was implemented to be
    able to manage the case that the entries within the priority queue can be updated and resorted
    within the container.  This is required for algorithms that are being implemented.  The standard
    implementation uses the heap features that are applied to an underlying container, in this case
    the vector container.  The standard implementation does lend itself to easily update those
    entries but the unerlying container can be accessed by a subclass of the priority queue
    implementation.  This is why the following subclass was implemented.  Thus, the question now
    is if I should consider implementing my own priority queue that doesn't extend the standard
    version?  I think that creating such an implementation might not actually be worth the
    effort.  The only advantage to this exercise is just that an exercise in implementing a
    priority queue.  Hopefully, I have some time in the future to see if it is actually worth
    implementing one.
*/

#include <queue>

/**
 * @brief This class extends the standard priority queue implementation to allow for entry updates that is
 *      required for the uniform cost search algorithm.  The other difference between the default implementation
 *      of the priority queue and this extension is that the entries are ordered using the greater function object
 *      instead of the less function object.  The main reason is that the current set of algorithms that are
 *      being implemented will expect to return the entry with the smallest key value and not the one with the
 *      greatest key value.  For instance, the uniform cost search expects to retreive the one with the smallest
 *      value in the priority queue instead of the largest.  This is just one of the algorithms that expects this
 *      ordering.
 *
 * @tparam _Type The type of object that will be added to this container
 * @tparam _Container defaults to std::vector<_Type>  The underlining container that will be used
 * @tparam _Pr defaults to std::less<typename _Container::value_type>  The functional object that will be used to
 *              sort the underlining container
 */
template<class _Type, class _Container = std::vector<_Type>, class _Pr = std::greater<typename _Container::value_type> >
class priority_queue_ex : public std::priority_queue<_Type, _Container, _Pr> {
public:
    // default ctor
    priority_queue_ex() = default;

    /**
     * @brief This method is used to find entries that will require updates
     *
     * @tparam InputIt The type of iterator that this method will return that will reference the found entry
     * @param object The object that will be searched within the underlying container
     * @return constexpr InputIt The iterator to the found object or it will return the underlying end instance
     */
    template<class InputIt>
    constexpr InputIt find(const _Type& object) { return std::find(c.begin(), c.end(), object); }

    void update(const _Type& object) {
        auto it = find(object);
        // if the entry was found we need to erase it
        if (it != c.end()) {
            // we found an equivalent entry in the underlying container so we need to remove it
            // so that it can then be updated correctly.
            // TODO: determine if the underlying priority queue can automatically update an added entry.
            c.erase(it);
        }
        // add the entry to the underlining priority_queue
        push(object);
    }

    /**
     * @brief This just returns the end entry of the underlying container c
     *
     * @tparam InputIt This is the type of iterator that will be returned from this call
     * @return constexpr InputIt The associated iterator for the underlying container c
     */
    template<class InputIt>
    constexpr InputIt end() { return c.end(); }

};

#endif
