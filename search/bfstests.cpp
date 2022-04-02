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

    // return 0;

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 