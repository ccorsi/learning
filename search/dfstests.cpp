#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <list>
#include <set>

#include <direct.h>

#include "graph.h"
#include "dfs.h"
#include "city.h"

#include "test.h"

#include "dfs.h"

using namespace std;

class test_context {
    string& m_name;
public:
    test_context(string& name) : m_name(name) { cout << "Executing test: " << m_name << endl; }
    ~test_context() { cout << "Completed test: " << m_name << endl; }
};

bool run_test(string& testname, string& source, string& destination, map<string,node<city>>& cities, list<city>& expected) {
    // used to display test information
    test_context c(testname);

    node<city>& start = cities[source];
    list<city> path;
    set<city> visited;

    if (dfs(start, cities[destination], path, visited)) {
        cout << "A path was found: ";
        // we found the required path to the destination
        string sep;
        for (auto current = path.begin() ; current != path.end() ; current++) {
            cout << sep << *current;
            sep = "->";
        }
        cout << endl;
        if (path.size() != expected.size()) {
            cout << "Did not find the correct path" << endl;
            return false;
        } else {
            auto pathItr = path.begin();
            auto expectedItr = expected.begin();
            while (pathItr != path.end() && *pathItr == *expectedItr) {
                pathItr++;
                expectedItr++;
            }
            if (pathItr == path.end()) {
                cout << "Found the expected path" << endl;
                return true;
            } else {
                cout << "Did not find the correct path" << endl;
                return false;
            }
        }
    }
    
    path.clear(); // clear the entries in the generated path.

    cout << "Executing iterative dfs implementation" << endl;

    if (dfs_i(start, cities[destination], path)) {
        cout << "A path was found: ";
        // we found the required path to the destination
        string sep;
        for (auto current = path.begin() ; current != path.end() ; current++) {
            cout << sep << *current;
            sep = "->";
        }
        cout << endl;
        if (path.size() != expected.size()) {
            cout << "Did not find the correct path" << endl;
            return false;
        } else {
            auto pathItr = path.begin();
            auto expectedItr = expected.begin();
            while (pathItr != path.end() && *pathItr == *expectedItr) {
                pathItr++;
                expectedItr++;
            }
            if (pathItr == path.end()) {
                cout << "Found the expected path" << endl;
                return true;
            } else {
                cout << "Did not find the correct path" << endl;
                return false;
            }
        }
    }

    return false;
}

bool run_test_i(string& testname, string& source, string& destination, map<string,node<city>>& cities, list<city>& expected) {
    // used to display test information
    test_context c(testname);

    node<city>& start = cities[source];
    list<city> path;
    set<city> visited;

    if (dfs_i(start, cities[destination], path)) {
        cout << "A path was found: ";
        // we found the required path to the destination
        string sep;
        for (auto current = path.begin() ; current != path.end() ; current++) {
            cout << sep << *current;
            sep = "->";
        }
        cout << endl;
        if (path.size() != expected.size()) {
            cout << "Did not find the correct path" << endl;
            return false;
        } else {
            auto pathItr = path.begin();
            auto expectedItr = expected.begin();
            while (pathItr != path.end() && *pathItr == *expectedItr) {
                pathItr++;
                expectedItr++;
            }
            if (pathItr == path.end()) {
                cout << "Found the expected path" << endl;
                return true;
            } else {
                cout << "Did not find the correct path" << endl;
                return false;
            }
        }
    }

    return false;
}

void create_test_data(list<list<string>>& paths, map<string,node<city>>& cities) {
    // iterate through all of the edges that were defined and provide the different connections
    // NOTE: Our list in this case will only contain two nodes per entry and each will be pointing to each other.
    for(auto itr = paths.begin() ; itr != paths.end() ; itr++) {
        list<string> edges = *itr;
        auto edgesItr = edges.begin();
        string name = *edgesItr++;

        if (cities.find(name) == cities.end()) {
            cities[name] = node<city>(city(name));
        }

        node<city>& src = cities[name];

        name = *edgesItr; // get the name of the destination city node
        if (cities.find(name) == cities.end()) {
            cities[name] = node<city>(city(name));
        }

        node<city>& dest = cities[name];

        // add an edge connection to each other
        src.add_edge(edge<city>(dest));
        dest.add_edge(edge<city>(src));
    }
}

template<typename E, typename V>
void create_test_data(list<list<E>>& elements, map<string,node<V>>& valueMap, node<V> (*create_node)(E&)) {
    // iterate through all of the edges that were defined and provide the different connections
    // NOTE: Our list in this case will only contain two nodes per entry and each will be pointing to each other.
    for(auto itr = elements.begin() ; itr != elements.end() ; itr++) {
        list<E> edges = *itr;
        auto edgesItr = edges.begin();
        string element = *edgesItr++;

        if (valueMap.find(element) == valueMap.end()) {
            valueMap[element] = node<V>(create_node(element));
        }

        node<V>& src = valueMap[element];

        element = *edgesItr; // get the name of the destination city node
        if (valueMap.find(element) == valueMap.end()) {
            valueMap[element] = node<V>(create_node(element));
        }

        node<V>& dest = valueMap[element];

        // add an edge connection to each other
        src.add_edge(edge<V>(dest));
        dest.add_edge(edge<V>(src));
    }
}

node<string> create_string_node(string& value) {
    return node<string>(value);
}

struct stringNode {
    node<string> operator()(string& name) { return node<string>(name); }
};

void create_string_graph() {
    list<list<string>> names = {
        {"a", "b"},
        {"a", "c"},
        {"b", "c"},
    };
    map<string,node<string>> namesMap;

    create_test_data(names, namesMap, create_string_node);

    for( auto v = namesMap.begin() ; v != namesMap.end() ; v++) {
        node<string>& n = (*v).second;
        cout << (*v).first << " --> " << n() << " with edges: ";
        auto edges = n.edges();
        for(auto edge = edges.begin() ; edge != edges.end() ; edge++) {
            auto e = (*edge);
            string name = e.node()();
            cout << name << " ";
        }
        cout << endl;
    }
}

void test_one() {
/*
    Boston,Montreal
    Boston,New York,Buffalo
    New York,Boston
    Buffalo,New York,Boston,Montreal
    Montreal,Buffalo
*/

    list<list<string>> paths = {
        {"Boston",     "New York"},
        {"Boston",     "Buffalo"},
        {"Buffalo",    "Montreal"},
        {"New York",   "Washington"},
        {"Washington", "Philadelphia"},
    };

    map<string,node<city>> cities;

    create_test_data(paths, cities);

    list<city> expected = {city("Boston"), city("Buffalo"), city("Montreal")};

    string source = "Boston";
    string destination = "Montreal";

    run_test(string("Simple DFS Test"), source, destination, cities, expected);
    run_test_i(string("Simple Iterative DFS Test"), source, destination, cities, expected);

}

int main(int argc, char **argv) {
    cout << "Called graphtest" << endl;

    test_one();

    create_string_graph();

    return 0;
}