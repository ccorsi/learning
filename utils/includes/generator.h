/**
 * @file generator.h
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief This contains different templates to generate dynamic test data
 * @version 0.1
 * @date 2025-04-16
 *
 * @copyright Copyright (c) 2025 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

 /**
  * @brief This file containes two types of templates that can be used to populate a
  *     container instance or a map instance.
  * 
  * @details The container template and the map template generators will populate a
  *     container or map instance given an element generator.  The two different
  *     generators expects that one of the different standard containers and maps.
  *     While this is the case at the moment, it is hoped that in the future these
  *     can also be replaced and/or added that allows the generating of the container
  *     or map more flexible.
  * 
  * @class container_generator  This template can be used to create a container populated by
  *         specifically stated elements using an element generator
  * 
  * @class map_generator This template can be used to create a map populated by specifically
  *         stated elements using an element generator
  */

#ifndef __GENERATOR_H__
#define __GENERATOR_H__

#include <vector>
#include <deque>
#include <forward_list>
#include <list>
#include <set>
#include <unordered_set>
#include <stack>
#include <queue>
#include <type_traits>

namespace valhalla {

namespace utils {

namespace generator {

/**
 * @brief This is the default class that will be used to allocate an instance
 *      using the instance Type operator()().
 *
 * @tparam Type The class type that will be return by this class Type operator()() operator
 */
template<typename Type>
class element_generator {
    Type m_generator;
public:
    element_generator() = default;

    Type & operator()() {
        return m_generator();
    }
}; // class element_generator

template<
    typename GeneratorType,
    typename Generator
>
class generator {
protected:
    Generator m_allocator;
public:
    virtual GeneratorType operator()(int count) = 0;
};

/**
 * @brief This template is used to generate a Map with the expected key/value pair using
 *  the defined generator.
 * 
 * @tparam Map The type of map to be populated
 * @tparam Map::key_type The key associated with the map
 * @tparam Map::mapped_type The value associated with the map
 * @tparam element_generator<typename Map::value_type> The type that will generate instances for the map
 */
template<typename Map,
    typename Key = typename Map::key_type,
    typename Value = typename Map::mapped_type,
    typename Generator = element_generator<typename Map::value_type>
>
class map_generator : public generator<Map, Generator> {
    // Generator m_allocator;
public:
    map_generator() = default;

    /**
     * @brief This operator will generate instances using the generated Generator that are then
     *  added to the Map type.  It will then return the populated Map to the caller.
     * 
     * @param count The number of key/value pairs to be added to the Map
     * @return Map The map that contains the generated key/value pairs
     */
    Map operator()(int count) override {
        Map dictionary;

        while (count-- > 0) {
            dictionary.insert(this->m_allocator());
        } // while (count-- > 0)

        return dictionary;
    }
}; // class map_generator

/**
 * @brief This template will generate a container with the defined value type.  It
 *  will use the defined Generator to generate instances that will be added to the
 *  expected Container.  It will the return the generated Container using the
 *  operator()(int) operator call.
 * 
 * @tparam Container The type of container that will be generated and returned
 * @tparam Type The type of instance in the Container
 * @tparam Generator This will be used to generate instances of type Type to be added to the Container
 */
template<typename Container,
    typename Type = typename Container::value_type,
    typename Generator = element_generator<Type>
>
class container_generator : public generator<Container, Generator> {
    // Generator m_allocator;
public:
    container_generator() = default;

    /**
     * @brief This operator is used to populate the expected Container using the defined
     *  Generator.
     * 
     * @param count The number of entries to add to the Container
     * @return Container The Container that contains the expected number of instances
     */
    Container operator()(int count) override {
        Container container;

        while (count-- > 0) {
            if constexpr (std::is_same_v<Container, std::vector<typename Container::value_type>> ||
                std::is_same_v<Container, std::deque<typename Container::value_type>> ||
                std::is_same_v<Container, std::list<typename Container::value_type>>) {
                container.push_back(this->m_allocator());
            } else if constexpr (std::is_same_v<Container, std::forward_list<typename Container::value_type>>) {
                container.push_front(this->m_allocator());
            } else if constexpr (std::is_same_v<Container, std::set<typename Container::value_type>> ||
                std::is_same_v<Container, std::multiset<typename Container::value_type>> ||
                std::is_same_v<Container, std::unordered_multiset<typename Container::value_type>> ||
                std::is_same_v<Container, std::unordered_set<typename Container::value_type>>) {
                container.insert(this->m_allocator());
            } else if constexpr (std::is_same_v<Container, std::queue<typename Container::value_type>> ||
                std::is_same_v<Container, std::stack<typename Container::value_type>> ||
                std::is_same_v<Container, std::priority_queue<typename Container::value_type>>) {
                container.push(this->m_allocator());
            }
        } // while (count-- > 0)

        return container;
    }
}; // container_generator

} // namespace generator

} // namespace utils

} // namespace valhalla

#endif
