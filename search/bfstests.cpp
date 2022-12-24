#include <iostream>
#include <list>
#include <unordered_set>

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "graph.h"
#include "bfs.h"

#include "city.h"

using namespace std;

namespace valhalla {
    namespace search {

        template<typename E>
        class node {
            E& m_element;
        public:
            node(E& element) : m_element(element) {}

            E& operator()() const { return m_element; }
        };

        template<typename E>
        class manager {
        public:
            manager() = default;

            std::vector<node<E>> operator()(node<E>& n) const {
                std::vector<node<E>> edges;

                return edges;
            }
        };

        template<typename E>
        class checker {
            // TODO: Replace this implementation with something that will work and then replace it with this container
            // std::unordered_set<E> processed;
            std::vector<E> processed;

        public:
            checker() = default;

            bool operator()(node<E>& node) const {
                // get a reference to the element that is stored within the node
                auto element = node();

                // determine if the given element has already been processed
                for (auto itr =  processed.begin() ; itr != processed.end() ; itr++) {
                    if (*itr == element) {
                        cout << "Element: " << element << " was found." << endl;
                        return true;
                    }
                }

                // E value = element;

                // TODO: fix this!!!!
                // processed.push_back(value);

                cout << "Element: " << element << " was not found." << endl;

                return false;

                // TODO: this needs to be fixed to allow for a real type of example.

                // if (processed.find(element) != processed.begin()) {
                //     return true;
                // }

                // processed.insert(processed.begin(), element);

                // return false;
            }
        };

        template<typename E>
        class Goal {
            E& m_element;
        public:
            Goal(E& element) : m_element(element) {}
            bool operator()(node<E>& node) const {
                E& element = node();
                return element == m_element;
            }
        };

        TEST(bfs, root_is_goal) {
            // checker<std::string> chk;
            // manager<std::string> mgr;

            // bfs<std::string, node<std::string>, Goal<std::string>, manager<std::string>, checker<std::string>> BFS;

            // std::string name = "Boston";
            // node<std::string> root(name);
            // Goal<std::string> goal(name);

            checker<int> chk;
            manager<int> mgr;

            bfs<int, node<int>, Goal<int>, manager<int>, checker<int>> BFS;

            int value = 101;
            node<int> root(value);
            Goal<int> goal(value);
            std::vector<int> path;

            ASSERT_TRUE(BFS.search(root, goal, mgr, chk, path)) << "the goal path was not found";

            cout << "path = [";
            for (auto itr = path.begin() ;  itr != path.end() ; itr++) {
                cout << " " << *itr;
            }
            cout << " ]" << endl;

        }

        class inode {
            int m_value;
            std::vector<int> m_edges;
        public:
            inode(int value) : m_value(value) {}

            int operator()() const { return m_value; }
        };

        class imanager {
            std::map<int,std::vector<int>> m_edges;
        public:
            imanager() = default;

            imanager(std::map<int, std::vector<int>>& edges) {
                m_edges = edges;
            }

            std::vector<inode> operator()(const inode& node) const {
                std::vector<inode> edges;

                int key = node();

                auto range = m_edges.equal_range(key);
                for ( auto& found = range.first ; found != range.second ; found++) {
                    auto values = found->second;
                    for (auto itr = values.begin() ; itr != values.end() ; itr++) {
                        int value = *itr;
                        edges.push_back(inode(value));
                    }
                }

                return edges;
            }
        };

        class ichecker {
            std::unordered_set<int> processed;
        public:
            ichecker() = default;

            bool operator()(inode& node) {
                int value = node();
                // cout << "checking for value: " << value;
                if (processed.find(value) != processed.end()) {
                    // cout << " was found" << endl;
                    return true;
                }

                processed.insert(processed.begin(), value);
                // cout << " was not found" << endl;

                return false;
            }
        };

        class igoal {
            int m_value;
        public:
            igoal(int value) : m_value(value) {}

            bool operator()(inode& node) const {
                int value = node();

                return m_value == value;
            }
        };

        TEST(bfs, use_inode) {

            bfs<int, inode, igoal, imanager, ichecker> ibfs;

            std::map<int, std::vector<int>> graph;

            graph[1] = { 2, 3 };
            graph[2] = { 1 };
            graph[3] = { 1 };

            inode iroot = inode(1);

            igoal g = igoal(3);
            imanager imgr(graph);
            ichecker ichk;
            std::vector<int> path;

            ASSERT_TRUE(ibfs.search(iroot, g, imgr, ichk, path)) << "the goal path was not found";

            cout << "path = [";
            for (auto itr = path.begin() ;  itr != path.end() ; itr++) {
                cout << " " << *itr;
            }
            cout << " ]" << endl;

            std::vector<int> expected = {1, 3};

            ASSERT_THAT(path, ::testing::ContainerEq(expected)) << "The returned path was incorrect";
        }

        class strnode {
            std::string m_value;
            std::vector<std::string> m_edges;
        public:
            strnode(std::string& value) : m_value(value) {}

            const std::string& operator()() const { return m_value; }

            void add(std::string& value) { m_edges.push_back(value); }

            std::vector<std::string> edges() const { return m_edges; }
        };

        class strmanager {
        public:
            strmanager() = default;

            std::vector<strnode> operator()(const strnode& node) const {
                std::vector<strnode> edges;

                auto values = node.edges();

                for (auto itr = values.begin() ; itr != values.end() ; itr++) {
                    edges.push_back(strnode(*itr));
                }

                return edges;
            }
        };

        class strchecker {
            std::unordered_set<std::string> processed;
        public:
            strchecker() = default;

            bool operator()(strnode& node) {
                std::string value = node();

                if (processed.find(value) != processed.end()) {
                    return true;
                }

                processed.insert(processed.begin(), value);

                return false;
            }
        };

        class strgoal {
            std::string m_value;
        public:
            strgoal(std::string value) : m_value(value) {}

            bool operator()(strnode& node) const {
                std::string value = node();

                return m_value == value;
            }
        };
    }
}

int main(int argc, char** argv) {
    /*
    list<int> data;

    for (auto cnt = 0 ; cnt < 10 ; cnt++) {
        data.push_back(cnt);
    }

    list<int> data2;

    for (auto cnt = 10 ; cnt < 20 ; cnt++) {
        data2.push_back(cnt);
    }

    list<int> data3(data2);
    
    cout << "Data2 before insert" << endl;

    for (auto itr = data2.begin() ; itr != data2.end() ; itr++) 
        cout << " " << *itr << endl;

    data2.insert(data2.begin(), data.begin(), data.end());

    cout << "Data2 after insert" << endl;

    for (auto itr = data2.begin() ; itr != data2.end() ; itr++) 
        cout << " " << *itr << endl;
    
    cout << "Data3 before insert" << endl;

    for (auto itr = data3.begin() ; itr != data3.end() ; itr++) 
        cout << " " << *itr << endl;

    data3.insert(data3.end(), data.begin(), data.end());

    cout << "Data3 after insert" << endl;

    for (auto itr = data3.begin() ; itr != data3.end() ; itr++) 
        cout << " " << *itr << endl;
        
    city g("Boston");

    node<city> n = node<city>(g);

    list<city> path;

    // bfs(n, g, path);

    int v = 13;

    node<int> i(v);

    int vv = 14;

    node<int> ii(vv);

    if (i < ii) {
        cout << "It worked." << endl;
    }

    set<node<city> > visited;

    visited.insert(n);

    valhalla::search::uniformed::inode l_inode(10);

    valhalla::search::informed::inode<int> i_inode(11);

    class distance {
        int m_key;
        int m_distance;
    public:
        distance(int key, int distance) : m_key(key), m_distance(distance) {}

        bool operator<(const distance& other) { return m_key < other.m_key; }
        bool operator==(const distance& other) { return m_key == other.m_key; }
        CONSTEXPR14 int operator()() const { return m_key; }
        CONSTEXPR14 bool operator()(const distance& other) const { return false; }
    };

    valhalla::search::informed::inode<int, distance> d_inode(distance(10,120));
    valhalla::search::informed::inode<int, distance> e_inode(distance(10,125));

    std::cout << "Equality: " << (d_inode == e_inode) << std::endl;

    std::cout << "Key: " << d_inode() << std::endl;

    // return 0;
    */

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 