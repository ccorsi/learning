#include <iostream>
#include <list>
#include <array>
#include <map>
#include <string>

#include "gtest/gtest.h"

#include "graph.h"
#include "dls.h"

#include "utils.h"

using namespace std;

node<string> create_string_node(string& e) {
    return node<string>(e);
}

TEST(DepthLimitedSearchTestSuite, SimpleDepthLimitedSearchTest) {
    list<array<string,2>> elements = {
        { string("a"), string("b") },
        { string("a"), string("c") },
        { string("b"), string("c") },
        { string("b"), string("e") },
        { string("c"), string("d") },
        { string("e"), string("f") },
        { "e", "g" },
    };

    map<string,node<string>> valueMap;

    create_graph_map(elements, valueMap, create_string_node);

    // for( auto itr = valueMap.begin() ; itr != valueMap.end() ; itr++) {
    //     cout << (*itr).first << " ==> "; 
    //     auto edges = (*itr).second.edges();
    //     for(auto edgeItr = edges.begin(); edgeItr != edges.end() ; edgeItr++) {
    //         cout << (*edgeItr).node()() << " ";
    //     }
    //     cout << endl;
    // }

    list<string> expected = { "a", "b", "e", "f" };

    string source = "a";
    string destination = "f";

    list<string> path;

    // if (dls(valueMap[source], destination, path, 10)) {
    //     cout << "Found path: ";

    //     for (auto itr = path.begin() ; itr != path.end() ; itr++)
    //         cout << *itr << " ";
        
    //     cout << endl;

    // }

    ASSERT_TRUE(dls(valueMap[source], destination, path, 10));

    ASSERT_EQ(path, expected);

}


TEST(DepthLimitedSearchTestSuite, LimitReachedDepthLimitedSearchTest) {
    list<array<string,2>> elements = {
        { string("a"), string("b") },
        { string("a"), string("c") },
        { string("b"), string("c") },
        { string("b"), string("e") },
        { string("c"), string("d") },
        { string("e"), string("f") },
        { "e", "g" },
    };

    map<string,node<string>> valueMap;

    create_graph_map(elements, valueMap, create_string_node);

    list<string> expected = { "a", "b", "e", "f" };

    string source = "a";
    string destination = "f";

    list<string> path;

    ASSERT_FALSE(dls(valueMap[source], destination, path, 2));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}