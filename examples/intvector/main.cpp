#include <iostream>
#include <fstream>
#include <vector>

#include "data_loader.h"

using namespace valhalla::loader;
using namespace valhalla::checkers;

struct vector_reader {
    std::istream & operator()(std::istream & in, std::vector<int> values, int field) {
        int value;
        in >> value;
        values.push_back(value);
        return in;
    }
};

int main(int argc, char** argv) {
    // create an input stream
    std::fstream in("data.txt");

    try {
        std::vector<int> value;

        // define the dataLoader for a int primitive...
        dataLoader<
            std::vector<int>,
            char,
            vector_reader,
            1,
            is_character<char, '{'>,
            is_character<char, '}'>,
            is_space
        > loader(value);
        // ...initialize the value
        in >> loader;

        std::cout << "{ ";
        for (auto v : value)
            std::cout << "value = " << v << " ";
        std::cout << "}\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An exception was caught: " << ex.what() << "\n";
        return 1;
    }

}
