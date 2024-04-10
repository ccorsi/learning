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
 * @brief This reader will load the x and y values of the passed point
 *      within a single call instead of two seperate calls.
 *
 */
struct point_reader {
    std::istream & operator()(std::istream & in, point & p, int field) {
        int x;
        // load data for the x field
        in >> x;

        int y;
        // load data for the y field
        in >> y;

        // initialize the passed point with the loaded x & y data
        p = point(x,y);

        return in;
    }
};

int main(int argc, char** argv) {
    std::cout << "Calling single reader example\n";

    try {
        // create an input stream
        std::fstream in("data.txt");

        point value;

        // define the dataLoader for a point instance...
        dataLoader<
            point,
            char,
            point_reader,
            1,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space
        > loader(value);
        // ...initialize the point value
        in >> loader;

        std::cout << "value = " << value << "\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An exception was caught: " << ex.what() << "\n";
        return 1;
    } // catch (std::exception & ex)
}
