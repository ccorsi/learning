#ifndef _HEAP_H__
#define __HEAP_H__

#include <algorithm>
#include <iterator>
#include <vector>

namespace valhalla {
    namespace heaps {
        template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
        class heap {
            Container m_data;
            Compare m_cmp;

            void swap(int from, int to) {
                T tmp = m_data[from];
                m_data[from] = m_data[to];
                m_data[to] = tmp;
            }

            inline int parent(int i) { return (i - 1) / 2; }
            inline int left(int i) { return 2 * i + 1; }
            inline int right(int i) { return 2 * i + 2; }

            void heapify() {
                int current = m_data.size() - 1;
                int l_parent = parent(current);
                while (m_cmp(m_data[current], m_data[l_parent])) {
                    swap(current, l_parent);
                    l_parent = parent((current = parent(current), current));
                }
            }

            int find_index(T& value) {
                size_t index = 0;

                // iterate through the heap to search for the entry that contains value
                while (index < m_data.size() && m_data[index] != value) {
                    if (m_data[index] < value) {
                        // the value is located within the left subtree of the heap
                        index = left(index);
                    } else {
                        // the value is located within the right subtree of the heap
                        index = right(index);
                    }
                }

                // we've found the entry if and only if the index is less than the size of the heap
                return (index == m_data.size()) ? -1 : index;
            }

        public:
            template<class T, class Container = std::vector<T>, class Compare = std::less<typename Container::value_type>>
            class iterator : public std::iterator<std::input_iterator_tag, T> {
                Container& m_data;
                size_t m_current;
                // T& m_value;

                inline size_t parent() { return (m_current - 1) / 2; }
                inline size_t left() { return 2 * m_current + 1; }
                inline size_t right() { return 2 * m_current + 2; }

                void increment() {
                    // find the next entry that will be returned
                    if (m_current != m_data.size()) {
                        // we aren't at the end entry
                    }

                }

            public:
                iterator() = default;

                explicit iterator(Container& data) : m_data(data) {
                    // we need to determine what is the minimum value entry.
                    m_current = 0;
                    size_t l_left = left();
                    while (l_left < m_data.size()) {
                        m_current = l_left;
                        l_left = left();
                    }
                    // m_value = m_data[m_current];
                }

                explicit iterator(Container& data, size_t current) : m_data(data), m_current {
                    m_value = (m_current < m_data.size()) ? m_data[m_value] : m_data[0];
                }

                // TBD: the following two operators needs to be fully implemented.
                iterator& operator++() { return *this; }
                iterator operator++(int) { iterator retval = *this; return retval; }
                bool operator==(iterator other) const { return m_current == other.m_current; }
                bool operator!=(iterator other) const { return !(*this == other); }
                // TBD: should I just check if the current entry is within range?
                //      Probably not since it will be done within the container
                reference operator*() const { return m_data[m_current]; }
            };

            iterator<T> begin() { return iterator<T>(m_data); }
            iterator<T> end() { return iterator<T>(m_data, m_data.size()); }

            heap() = default;

            void add(T& value) {
                m_data.push_back(value);
                heapify();
            }

            void add(T value) {
                m_data.push_back(value);
                heapify();
            }

            bool remove(T& value) {
                int index = find_index(value);
                if (index < 0) {
                    // the passed value is not part of this heap
                    return false;
                }

                // remove the indexed entry with the last entry in the heap array
                m_data[index] = m_data.back();
                // remove the last entry from the heap array
                m_data.pop_back();

                // updated heap entry
                int l_left = left(index);
                int l_right = right(index);

                while (l_left < m_data.size() && ( m_cmp(m_data[l_left], m_data[index]) || m_cmp(m_data[l_right], m_data[index]) ) ) {
                    // move the index entry into the correct spot
                    if (m_cmp(m_data[l_left], m_data[l_right])) {
                        swap(l_left, index);
                        index = l_left;
                    } else {
                        swap(l_right, index);
                        index = l_right;
                    }
                    // update the left and right entries
                    l_left = left(index);
                    l_right = right(index);
                }

                return true;
            }

            bool remove(T value) {
                int index = find_index(value);
                if (index < 0) {
                    // the passed value is not part of this heap
                    return false;
                }

                // remove the indexed entry with the last entry in the heap array
                m_data[index] = m_data.back();
                // remove the last entry from the heap array
                m_data.pop_back();

                // updated heap entry
                size_t l_left = left(index);
                size_t l_right = right(index);

                while (l_left < m_data.size() && ( m_cmp(m_data[l_left], m_data[index]) || m_cmp(m_data[l_right], m_data[index]) ) ) {
                    // move the index entry into the correct spot
                    if (m_cmp(m_data[l_left], m_data[l_right])) {
                        swap(l_left, index);
                        index = l_left;
                    } else {
                        swap(l_right, index);
                        index = l_right;
                    }
                    // update the left and right entries
                    l_left = left(index);
                    l_right = right(index);
                }

                return true;
            }

            bool contains(T& value) {
                int start = 0;
                int nodes = 1;

                while (start < m_data.size()) {
                    start = nodes - 1;
                    int end = nodes + start;
                    int count = 0;
                    while (start < m_data.size() && start < end) {
                        if (value == m_data[start]) {
                            return true;
                        } else if(value > m_data[parent(start)] && value < m_data[start]) {
                            count++;
                        }
                        start++;
                    }
                    if (count == nodes) {
                        return false;
                    }
                    nodes *= 2;
                }

                return false;
            }

            bool contains(T value) {
                size_t start = 0;
                size_t nodes = 1;

                while (start < m_data.size()) {
                    start = nodes - 1;
                    size_t end = nodes + start;
                    size_t count = 0;
                    while (start < m_data.size() && start < end) {
                        if (value == m_data[start]) {
                            return true;
                        } else if(value > m_data[parent(start)] && value < m_data[start]) {
                            count++;
                        }
                        start++;
                    }
                    if (count == nodes) {
                        return false;
                    }
                    nodes *= 2;
                }

                return false;
            }

        };
    }
}

#endif
