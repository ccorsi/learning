#include <iostream>
#include <assert.h>

#include "gtest/gtest.h"

#include "linkedlists.h"

namespace valhalla {
    namespace lists {

        class node {
        private:
            node* m_next;
            int   m_value;
            static node m_end;
        public:
            node(int value, node* next = nullptr) : m_value(value), m_next(next) {}
            int operator()() { return m_value; }
            node* next() const { return m_next; }
            int value() const { return m_value; }
            ~node() { if (m_next != nullptr) { delete m_next; } }
            const node* const set_next(node* next) { m_next = next; return m_next; }
            friend class linkedlist;
            std::ostream& operator<<(std::ostream& os) {
                os << ", ";
                os << m_value;
                if (m_next != nullptr) {
                    m_next->operator<<(os);
                }
                return os;
            }
            node* operator->() { std::cout << "Calling operator->"; return this; }
            node& operator*() { std::cout << "Calling operator*"; return *this; }
        };

        class linkedlist {
        private:
            node* m_head, *m_tail;
            static node m_end;
        public:
            linkedlist() : m_head(nullptr), m_tail(nullptr) {}
            void add(int value) {
                if (m_head == nullptr) {
                    m_tail = m_head = new node(value);
                } else {
                    m_tail = m_tail->m_next = new node(value);
                }
            }
            node* head() const { return m_head; }
            std::ostream& operator<<(std::ostream& os) {
                std::cout << "Calling linkedlist operator<<" << std::endl;
                os << m_head;
                return os;
            }

            // class iterator : std::iterator<std::input_iterator_tag, node, node, const node*, node> {
            //     node* m_node;
            // public:
            //     explicit iterator(node* n = &m_end) : m_node(n) {}
            //     iterator& operator++() { if (m_node->m_next != nullptr) m_node = m_node->m_next; return *this; }
            //     iterator& operator++(int) { iterator retval = *this; ++(*this); return retval; }
            //     bool operator==(iterator o) const { return m_node == o.m_node; }
            //     bool operator!=(iterator o) const { return !(*this == o); }
            //     reference operator*() const { return m_node; }
            // };
            // iterator begin() { return iterator(m_head); }
            // iterator end() { return iterator(m_end); }
        };

        std::ostream& operator<<(std::ostream& os, const node& n) {
            os << n.value();
            if (n.next() != nullptr) {
                return n.next()->operator<<(os);
            }
            return os;
        }

        std::ostream& operator<<(std::ostream& os, const linkedlist& ll) {
            node* n = ll.head();
            os << *n; // would just passing n not work!!!
            return os;
        }

        TEST(SINGLY_LINKED_LIST_TEST_SUITE, SIMPLE_SINGLY_LINKED_LIST_TEST) {
            linkedlist ll;
            ll.add(1);
            ll.add(2);

            node* head = ll.head();

            while (head != nullptr) {
                int value = head->value();
                std::cout << " [ " << value << " == " << (*head)() << " ]";
                head = head->next();
            }
            std::cout << std::endl;

            head = ll.head();

            node n = *head; // what is the calling if it is not calling operator*()

            std::cout << "Linked List: [ " << n << " ] " << std::endl;
            std::cout << "Linked List: [ " << ll << " ] " << std::endl;
            std::cout << "[" << *head << "]" << std::endl;

            // singly_linked_list<int> sll;

            // sll.add(1);
            // sll.add(2);

            // std::cout << "Singly Linked List: [ " << sll << " ] " << std::endl;

            std::vector<int> ii;

            std::cout << "vector::begin() == vector::end(): " << (ii.begin() == ii.end()) << std::endl;

            doubly_linked_list<int> dll;
            dll.add(1);
            dll.add(2);

            // NOTE: the assert call will only be used when compiled in debug mode
            assert(dll.contains(1));

            std::cout << dll << std::endl;

            for( auto itr = dll.begin(); itr != dll.end() ; itr++) {
                std::cout << *itr << std::endl;
            }

        }

        TEST(LinkedListTestSuite, AvlTest) {

            bst<int> bl;

            for(int cnt = 0 ; cnt < 100 ; cnt++) {
                bl.insert(cnt);
            }

            bl.insert(100);

            ASSERT_TRUE(bl.remove(10)) << "We were unable to remove the added 10 entry from the avl instance";

        }
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}