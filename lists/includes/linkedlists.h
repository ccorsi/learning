#ifndef __LINKED_LISTS_H__
#define __LINKED_LISTS_H__

#include <sstream>

#include <assert.h>

#include "debug.h"

namespace valhalla {
    namespace lists {
        template<typename E>
        class doubly_linked_list {
        public:
            template<typename D = E>
            class doubly_node {
            private:
                D m_data;
                doubly_node *m_prior, *m_next;
            public:
                // ctor & dtor
                doubly_node() = default;
                doubly_node(D& data, doubly_node<E>* prior = nullptr, doubly_node<D>* next = nullptr) : m_data(data), m_prior(prior), m_next(next) {
                    if (m_prior != nullptr) {
                        m_prior->m_next = this;
                    }
                    if (m_next != nullptr) {
                        m_next->m_prior = this;
                    }
                }
                ~doubly_node() { if (m_next != nullptr) { delete m_next; } }

                // operators implementations
                bool operator==(const doubly_node<E>& o) const { return m_data == o.m_data; }
                bool operator<(const doubly_node<E>& o) const { return m_data < o.m_data; }
                std::ostream& operator<<(std::ostream&os) { os << m_data;  return os; }
                D operator()() const { return m_data; }

                // user defined methods
                doubly_node* next() const { return m_next; }
            };

        private:
            doubly_node<E> *m_head, *m_tail, *m_end;
        public:
            // ctor & dtor
            doubly_linked_list() : m_head(nullptr), m_tail(nullptr) {
                m_end = new doubly_node<E>();
            }

            ~doubly_linked_list() {
                if (m_head != nullptr) {
                    delete m_head;
                    m_head = m_tail = nullptr;
                }
                delete m_end;
            }

            // operators
            // friend std::ostream& operator<<(std::ostream&, const doubly_linked_list<E>&);

            // user defined methods
            void add(E& element) {
                if (m_head == nullptr) {
                    m_tail = m_head = new doubly_node<E>(element);
                    return;
                }
                // add the new entry to the end of the linked list
                m_tail = m_tail->m_next = new doubly_node<E>(element, m_tail);
            }

            void add(E element) {
                if (m_head == nullptr) {
                    m_tail = m_head = new doubly_node<E>(element);
                    return;
                }
                // add the new entry to the end of the linked list
                m_tail = new doubly_node<E>(element, m_tail);
            }

            bool contains(E& element) const {
                for(doubly_node<E>* current = m_head ; current != nullptr ;  current = current->m_next) {
                    if (current->m_data == element) {
                        return true;
                    }
                }

                return false;
            }

            bool contains(E element) const {
                for(doubly_node<E>* current = m_head ; current != nullptr ;  current = current->next()) {
                    if ((*current)() == element) {
                        return true;
                    }
                }

                return false;
            }

            // const doubly_node<E>* const head() const { return m_head; }

            template<typename E>
            class iterator {
            private:
                doubly_node<E>* m_current, *m_end;
            public:
                iterator() = default;
                explicit iterator(doubly_node<E>* current, doubly_node<E>* end) {
                    m_end = end;
                    if (current == nullptr) {
                        m_current = m_end;
                    } else {
                        m_current = current;
                    }
                }

                E operator*() const {
                    // assert( m_current != nullptr );
                    if (m_current == nullptr) throw "can't dereference value-initialized doubly linked list iterator";

                    return (*m_current)();
                }

                // prefixed interator operator
                iterator<E>& operator++() {
                    if (m_current == nullptr) {
                        throw "can't increment value-initialized doubly linked list iterator";
                    }
                    if (m_current != nullptr && m_current->next() != nullptr) {
                        m_current = m_current->next();
                    } else {
                        m_current = m_end;
                    }
                    return *this;
                }

                // postfixed interator operator
                iterator<E> operator++(int v) {
                    iterator<E> retval = *this;
                    if (m_current == nullptr) {
                        throw "can't increment value-initialized doubly linked list iterator";
                    }
                    if (m_current != nullptr && m_current->next() != nullptr) {
                        m_current = m_current->next();
                    } else {
                        m_current = m_end;
                    }
                    return retval;
                }

                bool operator==(const iterator& o) const { return m_current == o.m_current; }
                bool operator!=(const iterator& o) const { return !(*this == o); }
            };

            iterator<E> begin() const { return iterator<E>(m_head, m_end); }
            iterator<E> end() const { return iterator<E>(m_end, m_end); }
        };

        template<typename E>
        std::ostream& operator<<(std::ostream& os, const doubly_linked_list<E>& dll) {
            os << "[";
            auto itr = dll.begin();
            if (itr != dll.end()) {
                os << " " << *itr;
                for( itr++ ; itr != dll.end() ; itr++) {
                    os << ", " << *itr;
                }
            }
            os << " ]";

            return os;
        }

        // template<typename E> class singly_linked_list;

        // template<typename E>
        // std::ostream& operator<<(std::ostream& os, const singly_linked_list<E>& sll) {
        //     os << "[";
        //     os << " ]";
        //     return os;
        // }

        template<typename E>
        class singly_linked_list {
        public:
            /**
             * @brief This is a singly linked list node that will reference an instance of an element.
             *  It will not copy the referencing element so that the user
             *
             * @tparam E the type of element that this node will be storing/referencing
             */
            template<typename E>
            class singly_node {
            private:
                E m_data;
                singly_node* m_next;
            public:
                singly_node(E& data) : m_data(data), m_next(nullptr) {}
                singly_node(E& data, singly_node<E>* prior) : m_data(data) { if (prior != nullptr) prior->m_next = this; }
                bool operator==(const singly_node<E>& o) const { return m_data == o.m_data; }
                bool operator<(const singly_node<E>& o) const { return m_data < o.m_data; }
                /**
                 * @brief Destroy the singly node object that will recursively delete the next
                 *  node in the list.
                 *
                 */
                ~singly_node() { if (m_next != nullptr) { delete m_next; } }
                std::ostream& operator<<(std::ostream&os) { os << m_data;  return os; }
                singly_node* next() const { return m_next; }
            };

        private:
            singly_node<E>* m_head;
            singly_node<E>* m_tail;
        public:
            singly_linked_list() : m_head(nullptr), m_tail(nullptr) {}
            ~singly_linked_list() { if (m_head != nullptr) delete m_head; }

            /**
             * @brief This method will insert the passed element to the end of the
             *  singly linked list.
             *
             * @param element The element that will be added to the singly linked
             *  list.
             */
            void add(E& element) {
                if (m_head == nullptr) {
                    m_tail = m_head = new singly_node<E>(element);
                } else {
                    m_tail->m_next = new singly_node<E>(element);
                    m_tail = m_tail->m_next;
                }
            }

            /**
             * @brief This method is useful whenever we are using primitive values that are passed
             *      to the add method that are not referencable.  For instance, you are passing an
             *      explicit integer value instead of a integer variable.
             *
             * @param element The value that is being added to this linked list
             */
            void add(E element) {
                if (m_head == nullptr) {
                    m_tail = m_head = new singly_node<E>(element);
                } else {
                    m_tail = new singly_node<E>(element, m_tail);
                }
            }

            /**
             * @brief Implementation of this linked list ostream for the
             *      entries in this list.  For some reason this is not
             *      being called.
             *
             * @param os the ostream that the entries of this list will
             *      be piped too.
             *
             * @return std::ostream& returning the passed referenced ostream
             */
            std::ostream& operator<<(std::ostream& os) {
                os << "[";
                if (m_head != nullptr) {
                    singly_node<E>* current = m_head;
                    os << *current;
                    current = current->next();
                    while(current != nullptr) {
                        os << ", " << *current;
                        current = current->next();
                    }
                }
                os << " ]";
            }

            /**
             * @brief This method will determine if the given element is part of the current
             *      list.
             *
             * @param element the element that we are looking for in this list
             * @return true if we've found the passed element in the list
             * @return false if the passed element was not part of this list
             */
            bool contains(E& element) const {

                for(singly_node<E>* current = m_head ; current != nullptr ; current = current->m_next) {
                    if (current->m_data == element) return true;
                }

                return false;
            }

            /**
             * @brief This method will determine if the given element is part of the current
             *      list.
             *
             * @param element the element that we are looking for in this list
             * @return true if we've found the passed element in the list
             * @return false if the passed element was not part of this list
             */
            bool contains(E element) const {

                for(singly_node<E>* current = m_head ; current != nullptr ; current = current->m_next) {
                    if (current->m_data == element) return true;
                }

                return false;
            }

            /**
             * @brief This method will remove the element passed if found
             *
             * @param element the element that we want to remove from this list
             * @return true if the element was found and removed from the list
             * @return false if the element was not found within this list
             */
            bool remove(E& element) const {
                // case 1: empty list
                if (m_head == nullptr) {
                    // nothing to do
                    return false;
                }

                // case 2: single entry list
                if (m_head->m_data == element) {
                    singly_node<E>* tmp = m_head;
                    if (m_head == m_tail) {
                        // I could of easily have just set them to nullptr instead
                        m_tail = m_head = m_head->m_next;
                    } else {
                        m_head = m_head->m_next;
                    }
                    // the list was updated so we return true
                    return true;
                }

                // case 3: multiple entries within the list
                for(singly_node<E>* current = m_head ; current->m_next != nullptr ; current = current->m_next) {
                    if (current->m_next->m_data == element) {
                        // remove the current m_next entry from this list.
                        singly_node<E>* removed = current->m_next;
                        if (removed != m_tail) {
                            // removed is not the tail entry in this list
                            current->m_next = removed->m_next;
                        } else {
                            // remove is the tail entry in this list
                            current->m_next = nullptr;
                            // update the tail entry to point to the current entry instead
                            m_tail = current;
                        }
                        // we've updated the list so return true
                        return true;
                    }
                }

                return false;
            }
            // friend std::ostream& operator<<(std::ostream&, const singly_linked_list<E>&);
        };

        // template<typename E>
        // std::ostream& operator<<(std::ostream& os, const singly_linked_list<E>& sll) {
        //     os << "[";
        //     singly_node<E>* current = sll.m_head;
        //     if (current != nullptr) {
        //         os << current->m_data;
        //         for( current = current->m_next; current != nullptr ; current = current->m_next) {
        //             os << ", " << current->m_data;
        //         }
        //     }
        //     os << " ]" << os.endl;
        //     return os;
        // }

        /**
         * @brief This is an implementation of a binary search tree.  Each node will contain a
         *      value that is added to the binary search tree.
         *
         * @tparam E the type of elements that will be stored within the binary search tree
         */
        template<typename E>
        class bst {
        private:
            /**
             * @brief This is the node that is associated with the binary search tree
             *
             * @tparam E the type of element that will be stored within the binary search
             *          tree node
             */
            template<typename E>
            class bst_node {
            private:
                E m_data;
                bst_node<E> *m_left, *m_right;
            public:
                // ctor & dtor
                explicit bst_node(E& data, bst_node<E>* left = nullptr, bst_node<E>* right = nullptr) : m_data(data), m_left(left), m_right(right) {}
                ~bst_node() {
                    if (m_left != nullptr) {
                        // recursively delete the children nodes
                        delete m_left;
                        m_left = nullptr;
                    }
                    if (m_right != nullptr) {
                        // recursively delete the children nodes
                        delete m_right;
                        m_right = nullptr;
                    }
                }

                // ================= operators ========================

                E& operator()() const { return m_data; }
                bool operator==(const E& data) const { return m_data == data; }
                bool operator==(const bst_node<E>& o) const { return m_data == o.m_data; }

                // ================== user methods ====================

                void insert(E&value) {
                    if (value < m_data) {
                        if (m_left == nullptr) {
                            m_left = new bst_node<E>(value);
                        } else {
                            m_left->insert(value);
                        }
                    } else {
                        if (m_right == nullptr) {
                            m_right = new bst_node<E>(value);
                        } else {
                            m_right->insert(value);
                        }
                    }
                }

                bool contains(E& value) {
                    if (value == m_data) {
                        return true;
                    } else if (value < m_data) {
                        if (m_left == nullptr) {
                            return false;
                        } else {
                            return m_left->contains(value);
                        }
                    } else {
                        if (m_right == nullptr) {
                            return false;
                        } else {
                            return m_right->contains(value);
                        }
                    }
                }

                bst_node<E>* find(E& value) {
                    if (value == m_data) {
                        return this;
                    }

                    if (value < m_data) {
                        if (m_left != nullptr) {
                            return m_left->find(value);
                        }
                        return nullptr;
                    } else {
                        if (m_right != nullptr) {
                            return m_right->find(value);
                        }
                        return nullptr;
                    }
                }

                bst_node<E>* find_parent(E& value) {
                    if (value == m_data) {
                        return nullptr;
                    }

                    if (value < m_data) {
                        if (m_left == nullptr) {
                            return nullptr;
                        } else if (m_left->m_data == value) {
                            return this;
                        } else {
                            return m_left->find_parent(value);
                        }
                    } else {
                        if (m_right == nullptr) {
                            return nullptr;
                        } else if (m_right->m_data == value) {
                            return this;
                        } else {
                            return m_right->find_parent(value);
                        }
                    }
                }

                bool remove(bst_node<E>* nodeToRemove) {
                    if (m_left != nodeToRemove && m_right != nodeToRemove) {
                        // we will only make changes if the nodeToRemove is ones of the child nodes
                        throw "can't update child references unless passed node is one of its child nodes";
                    }
                    if (m_right == nodeToRemove) {
                        if (nodeToRemove->m_data < m_data) {
                            m_left = nodeToRemove->m_right;
                        } else {
                            m_right = nodeToRemove->m_right;
                        }
                    } else if (m_left == nodeToRemove) {
                        if (nodeToRemove->m_data < m_data) {
                            m_left = nodeToRemove->m_left;
                        } else {
                            m_right = nodeToRemove->m_left;
                        }
                    } else {
                        return false;
                    }
                    return false;
                }

                bool is_leaf() {
                    return m_left == nullptr && m_right == nullptr;
                }

                bool has_single_child() {
                    return ( m_left == nullptr && m_right != nullptr ) ||
                        ( m_left != nullptr && m_right == nullptr );
                }

                /**
                 * @brief This method will pull the largest value from the left subtree to
                 *  this node and delete the largest value node.
                 *
                 */
                void pull_and_remove() {
                    if (m_left == nullptr) {
                        // this method is being called when the left leaf doesn't exists.
                        throw "can't call remove_and_pull unless left leaf exists";
                    }

                    bst_node<E>* largestValue = m_left;

                    while (largestValue->m_right != nullptr) {
                        // find the largest value in the left subtree
                        largestValue = largestValue->m_right;
                    }

                    // set the parents' right reference of the largestValue to nullptr
                    find_parent(largestValue->m_data)->m_right = nullptr;

                    // replace this node value with the largestValue node found
                    m_data = largestValue->m_data;

                    // clear the child node references prior to delete the node
                    largestValue->clear();

                    // delete the largestValue node instead of this node
                    delete largestValue;
                }

                /**
                 * @brief This method clears the left and right node references so
                 *      that this instance can be safely deleted.
                 *
                 */
                void clear() {
                    m_left = m_right = nullptr;
                }

                E find_min() {
                    if (m_left == nullptr) {
                        return m_data;
                    }

                    return m_left->find_min();
                }

                E find_max() {
                    if (m_right == nullptr) {
                        return m_data;
                    }

                    return m_right->find_max();
                }

                template<typename C>
                void preorder(C& c) {
                    c(m_data);
                    if (m_left != nullptr) {
                        m_left->preorder();
                    }
                    if (m_right != nullptr) {
                        m_right->preorder();
                    }
                }

                template<typename C>
                void postorder(C& c) {
                    if (m_left != nullptr) {
                        m_left->postorder();
                    }
                    if (m_right != nullptr) {
                        m_right->postorder();
                    }
                    c(m_data);
                }

                template<typename C>
                void inorder(C& c) {
                    if (m_left != nullptr) {
                        m_left->inorder();
                    }
                    c(m_data);
                    if (m_right != nullptr) {
                        m_right->inorder();
                    }
                }
            };
        private:
            // data
            bst_node<E>* m_root;
            int m_count;

        public:
            // ctor & dtor
            explicit bst() : m_count(0), m_root(nullptr) {}
            ~bst() {
                if (m_root != nullptr) {
                    delete m_root;
                }
            }

            // operators

            // user defined methods

            // NOTE: The following method doesn't work when trying to pass an explicit value to this bsl instance like
            //       a primitive integer bsl.insert(1).
            //
            // void insert(E& value) {
            //     if (m_root == nullptr) {
            //         m_root = new bsl_node<E>(value);
            //     } else {
            //         m_root->insert(value);
            //     }
            // }

            void insert(E value) {
                if (m_root == nullptr) {
                    m_root = new bst_node<E>(value);
                } else {
                    m_root->insert(value);
                }
                m_count++;
            }

            bool contains(E value) {
                if (m_root == nullptr) {
                    return false;
                }
                return m_root->contains(value);
            }

            bool remove(E value) {
                /*
                There are four possible cases that we can see when removing a value from the avl tree.

                    1 - the value to remove is a leaf node

                    2 - the value to remove has a right subtree, but no left subtree

                    3 - the value to remove has a left subtree, but no right subtree

                    4 - the value to remove has both a left and right subtree in which case we promote the
                        largest value in the left subtree

                Each of the above cases will be dealt with in the following method.
                */

                if (m_root == nullptr) {
                    // we have nothing to remove therefore we are done
                    return false;
                }

                bst_node<E>* nodeToRemove = m_root->find(value);

                if (nodeToRemove == nullptr) {
                    // the value to remove doesn't exist thus we are done
                    return false;
                }

                bst_node<E>* parentToNode = m_root->find_parent(value);

                if (m_count == 1) {
                    // The node to remove is the root node and there is only a single node in the avl
                    m_count = 0;
                    delete m_root;
                    m_root = nullptr;
                    return true;
                } else if (nodeToRemove->is_leaf()) {
                    // case #1
                    parentToNode->remove(nodeToRemove);
                    // clear the nodeToRemove child references
                    nodeToRemove->clear();
                    // now safely delete the node
                    delete nodeToRemove;
                } else if (nodeToRemove->has_single_child()) {
                    // case #2 or case #3 - only one of the child nodes is not null
                    parentToNode->remove(nodeToRemove);
                    // clear the nodeToRemove child references
                    nodeToRemove->clear();
                    // now safely delete the node
                    delete nodeToRemove;
                } else {
                    // case #4 - both child nodes exist so we replace this node with
                    // the largest value from the left node
                    nodeToRemove->pull_and_remove();
                    // nodeToRemove will now contain the largest value of the left subtree
                    // and the largest value node will be deleted within the pull_and_remove
                    // call.
                }

                // decrement the count
                m_count--;

                // return true to signify that we've updated this avl tree.
                return true;
            }

            E find_min() {
                if (m_root == nullptr) {
                    throw "Unable to find min using an empty tree";
                }

                return m_root->find_min();
            }

            E find_max() {
                if (m_root == nullptr) {
                    throw "Unable to find max using an empty tree";
                }

                return m_root->find_max();
            }

            template<typename C>
            void preorder(C& c) {
                if (m_root != nullptr) {
                    m_root->preorder(c);
                }
            }

            template<typename C>
            void postorder(C& c) {
                if (m_root != nullptr) {
                    m_root->postorder(c);
                }
            }

            template<typename C>
            void inorder(C& c) {
                if (m_root != nullptr) {
                    m_root->inorder(c);
                }
            }
        };
    }
}

#endif