#include <iostream>
#include <fstream>

#include "data_loader.h"

using namespace valhalla::loader;
using namespace valhalla::checkers;

class point {
    int m_x, m_y;
public:
    point() = default;
    point(int x, int y) : m_x(x), m_y(y) {}

    friend std::ostream & operator<<(std::ostream & out, const point & pt) {
        return out << "point[x=" << pt.m_x << ",y=" << pt.m_y << "]";
    }
};

/**
 * @brief The data loader reader used to load the x and y fields into
 *      the passed point instance.
 *
 */
struct point_reader {
    int x;
    std::istream & operator()(std::istream & in, point & p, int field) {
        switch(field) {
            case 0: // load data for x field
                in >> x;
                break;
            case 1: // load data for y field
                {
                    int y;
                    in >> y;
                    // initialize the passed point with the loaded x & y data
                    p = point(x,y);
                }
                break;
            default:
                throw std::runtime_error("INVALID field");
        }
        return in;
    }
};

int main(int argc, char** argv) {
    // create an input stream
    std::fstream in("data.txt");

    try {
        point value;

        // define the dataLoader for a point instance...
        dataLoader<
            point,
            char,
            point_reader,
            2,
            is_character<char,'{'>,
            is_character<char, '}'>,
            is_space
        > loader(value);
        // ...initialize the value
        in >> loader;

        std::cout << "value = " << value << "\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An exception was caught: " << ex.what() << "\n";
        return 1;
    }
}
