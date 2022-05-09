#include <iostream>
#include <list>

#include "gtest/gtest.h"

#include "graph.h"
#include "bfs.h"

#include "city.h"

using namespace std;

int main(int argc, char** argv) {
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

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 