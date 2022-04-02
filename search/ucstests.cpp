// standard libraries
#include <vector>

// google tests library
#include "gtest/gtest.h"

// generally defined search and helper libraries
#include "graph.h"
#include "ucs.h"
#include "city.h"
#include "utils.h"

using namespace std;

/**
 * @brief This is used to store the different city and distance information
 *      that will be used to generate the required data structures used by
 *      the tests.
 */
struct city_data {
    string from;
    string to;
    int distance;
};

typedef struct city_data city_data;

/**
 * @brief This is used to create the necessary data structures that will be used by the
 *      tests.
 * 
 * @param data  This contains the city/distance information that will be used to populate the distances 
 * @param distances This will be populated with the information that was passed by the data
 * @param cities This will be populated with the information that was passed by the data
 */
void create_graph(vector<city_data>& data, map<string,map<string,int>>& distances, list<array<string,2>>& cities) {
    // populate the map so that we can use this information to determine the different distances between the two cities.
    for(auto itr = data.begin() ; itr != data.end() ; itr++) {
        auto data = *itr;
        // update the distances map
        map<string,int> source = distances[data.from];
        source[data.to] = data.distance;
        source = distances[data.to];
        source[data.from] = data.distance;
        // add to the cities list
        cities.push_back({ data.from, data.to });
    }    
}

node<city> create_city_node(string& name) {
    return node<city>(city(name));
}

class cmp {
private:
    map<string,map<string,int>>& m_distances;
public:
    cmp(map<string,map<string,int>>& distances) : m_distances(distances) {}
};

TEST(UniformCostSearchTestSuite, SimpleUniformCostSearchTest) {
    map<string,map<string,int>> distances;
    list<array<string,2>> cities;
    vector<city_data> data = {
        { "Duluth", "Sault Ste. Marie", 110 },
        { "Sault Ste. Marie", "Toronto", 90 },
        { "Toronto", "Pittsburgh", 80 },
        { "Duluth", "Chicago", 157 },
        { "Chicago", "Pittsburgh", 81 },
    };
    
    create_graph(data, distances, cities);

    node<city> root;
    list<city> path;
    map<string,node<city>> valueMap;

    create_graph_map(cities, valueMap, create_city_node);

    list<string> expected = { "a", "b", "e", "f" };

    string source = "Duluth";
    string destination = "Pittsburgh";

    // ASSERT_TRUE(ucs(valueMap[source], destination, path, cmp(distances)));

    // ASSERT_EQ(path, expected);

}

TEST(NodeTestSuite, NodeTest) {
    string data("Foo");
    
    node<string> n(data);

    string name = n();

    cout << "name: " << name << endl;
}

struct key_data {
    string name;
    int key;
};

typedef struct key_data key_data;

TEST(PriorityQueueExtendedTestSuite, PriorityQueueExtendedTest) {
    vector<string> data = { "foo", "bar", "joe", "tony" };
    vector<int> keys = { 11, 6, 88, 13 };
    vector<node<string>> nodes;
    priority_queue_ex<wrapper<string,int>> pq;

    auto keyItr = keys.begin();

    for (auto dataItr = data.begin() ; dataItr != data.end() ; dataItr++, keyItr++) {
        string& name = *dataItr;
        int key  = *keyItr;
        nodes.push_back(node<string>(name));
        {
            node<string>& n = nodes.back();
            pq.push(wrapper<string,int>(n, key));
        }
        // cout << "Added name: " << name << " with key: " << key << endl;
        const wrapper<string,int>& top = pq.top();
        const node<string>& n = top.node();
        // cout << "##################### Current top name: " << n() << ", key: " << top.key() << endl;
        // cout << "##################### Current top: " << top << endl;
    }

    while ( ! pq.empty() ) {
        cout << "Processing a priority queue entry" << endl;
        // cout << "Before calling top" << endl;
        wrapper<string,int> top = pq.top(); pq.pop();
        // cout << "After calling top" << endl;

        // const node<string>& n = top.node();
        // cout << "After calling top node" << endl;

        // const string& name = n();
        
        // cout << "After calling node operatior()" << endl;

        cout << "Top: " << top << endl;
    }
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
