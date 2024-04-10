#include <iostream>
#include <fstream>
#include <string>

#include "data_loader.h"

using namespace valhalla::loader;
using namespace valhalla::checkers;

/**
 * @brief This string reader will read in the whole string altogether.
 *
 */
struct string_reader {
    std::istream & operator()(std::istream & in, std::string & str, int field) {
        char chr = in.get();
        while (chr != std::string::traits_type::eof() && chr != '"') {
            chr = in.get();
            if (chr == '\\') {
                chr = in.get();
                if (chr == std::string::traits_type::eof()) {
                    return in;
                } // if (chr == std::string::traits_type::eof())
            } // if (chr == '\\')
            str += chr;
        } // while (chr != std::string::traits_type::eof() && chr != '"')
        return in;
    }
};

/**
 * @brief This string reader will read a single character at the time unless it
 *  encounters an escape character.
 *
 * This reader requires that the is_space_noop inner space operator is used.  If
 * not then the spaces will be removed from the string.
 *
 */
struct string_single_character_reader {
    std::istream & operator()(std::istream & in, std::string & str, int field) {
        char chr = in.get();
        if (chr != std::string::traits_type::eof()) {
            if (chr == '\\') {
                chr = in.get();
                if (chr == std::string::traits_type::eof()) {
                    return in;
                } // if (chr == std::string::traits_type::eof())
            } // if (chr == '\\')
            str += chr;
        } // if (chr != std::string::traits_type::eof())

        return in;
    }
};

int main(int argc, char** argv) {
    std::cout << "Calling string reader example\n";

    try {
        // create an input stream
        std::fstream in("data.txt");

        std::string value;

        // define the dataLoader for a string...
        dataLoader<
            std::string,
            char,
            string_single_character_reader,
            1,
            is_character<char,'\'','"'>,
            is_character<char,'\'','"'>,
            is_space,
            is_space_noop<char> // This is required when using the string_single_character_reader reader
        > loader(value);
        // ...initialize the string value
        in >> loader;

        std::cout << "value = " << value << "\n";

        return 0;
    } catch (std::exception & ex ) {
        std::cout << "An exception was caught: " << ex.what() << "\n";
        return 1;
    } // catch (std::exception & ex )// try
}
