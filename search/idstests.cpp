#include <map>
#include <list>
#include <array>

#include "gtest/gtest.h"

#include "utils.h"
#include "graph.h"
#include "ids.h"

using namespace std;

node<string> create_string_node(string& e) {
    return node<string>(e);
}

TEST(IterativeDepthSearchTestSuite, SimpleIterativeDepthSearchTest) {
    list<array<string,2> > elements = {
        { string("a"), string("b") },
        { string("a"), string("c") },
        { string("b"), string("c") },
        { string("b"), string("e") },
        { string("c"), string("d") },
        { string("e"), string("f") },
        { "e", "g" },
    };

    map<string,node<string> > valueMap;

    create_graph_map(elements, valueMap, create_string_node);

    list<string> expected = { "a", "b", "e", "f" };

    string source = "a";
    string destination = "f";

    list<string> path;

    ASSERT_TRUE(ids(valueMap[source], destination, path, 10));

    ASSERT_EQ(path, expected);

}

TEST(IterativeDepthSearchTestSuite, IterativeDepthSearchNoPathFoundTest) {
    list<array<string,2> > elements = {
        { string("a"), string("b") },
        { string("a"), string("c") },
        { string("b"), string("c") },
        { string("b"), string("e") },
        { string("c"), string("d") },
        { string("e"), string("f") },
        { "e", "g" },
    };

    map<string,node<string> > valueMap;

    create_graph_map(elements, valueMap, create_string_node);

    string source = "a";
    string destination = "f";

    list<string> path;

    ASSERT_FALSE(ids(valueMap[source], destination, path, 2));

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}