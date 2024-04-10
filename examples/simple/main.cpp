#include <iostream>
#include <fstream>

#include "data_loader.h"

using namespace valhalla::loader;

int main(int argc, char** argv) {
    std::cout << "Calling simple reader example\n";

    try {
        // create an input stream
        std::fstream in("data.txt");

        int value;

        // define the dataLoader for a int primitive...
        dataLoader<int,char> loader(value);
        // ...initialize the value
        in >> loader;

        std::cout << "value = " << value << "\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An exception was caught " << ex.what() << "\n";
        return 1;
    } // catch (std::exception & ex)
}
