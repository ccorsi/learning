#include <iostream>
#include <fstream>
#include <vector>

#include "data_loader.h"

// This defines the dataLoader template class
using namespace valhalla::loader;
// This defines the is_character and is_space operators
using namespace valhalla::checkers;

/**
 * @brief This structure will load an integer value from the input stream
 *      and add it to the passed integer vector.
 *
 */
struct vector_reader {
    /**
     * @brief This operator is called by the dataLoader to load the integer
     *      from the input stream.
     *
     * @param in The input stream containing the integer data
     * @param values The integer vector that the integer data will be added
     * @param field Which field is being loaded, field is set to zero in this case
     * @return std::istream& The passed input stream to allow for chaining.
     */
    std::istream & operator()(std::istream & in, std::vector<int> values, int field) {
        int value;
        // Since int implictly defines the input operator we can load it directly
        in >> value;
        // add the loaded integer into the integer vector
        values.push_back(value);
        // return the input stream to provide chaining
        return in;
    }
};

int main(int argc, char** argv) {
    // create an input stream
    std::fstream in("data.txt");

    try {
        std::vector<int> value;

        // define the dataLoader for a integer vector...
        dataLoader<
            std::vector<int>,         // instance type to populate
            char,                     // character trait of input stream
            vector_reader,            // reader
            1,                        // number of fields
            is_character<char, '{'>,  // opening character
            is_character<char, '}'>,  // closing character
            is_space                  // outer space characters
        > loader(value);
        // ...initialize the integer vector
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
