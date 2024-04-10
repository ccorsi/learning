#include <iostream>
#include <fstream>
#include <vector>

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

struct point_reader {
    int m_x;
    std::istream & operator()(std::istream & in, point & pt, int field) {
        switch (field) {
            case 0: // load x
                in >> m_x;
                break;
            case 1: // load y and initialize pt
            {
                int y;
                in >> y;
                pt = point(m_x,y);
                break;
            }
        }
        return in;
    }
};

struct point_vector_reader {
    std::istream & operator()(std::istream & in, std::vector<point> & vec, int field) {
        point pt;

        // define the dataLoader template class
        dataLoader<
            point,
            char,
            point_reader,
            2,
            is_character<char,'{'>,
            is_character<char,'}'>,
            is_space_or<','>
        > loader(pt);
        // initialize the point pt with the input data
        in >> loader;

        // add the point to the passed vector
        vec.push_back(pt);

        return in;
    }
};

int main(int argc, char** argv) {
    std::cout << "Calling point vector reader example\n";

    try {
        // create an input stream
        std::fstream in("data.txt");

        std::vector<point> points;

        // define the dataLoader for a point vector...
        dataLoader<
            std::vector<point>,
            char,
            point_vector_reader,
            1,
            is_character<char,'['>,
            is_character<char,']'>,
            is_space,
            is_space_or<','>
        > loader(points);
        // ...initialize the point vector
        in >> loader;

        std::cout << "points = [ ";
        for (auto & pt : points)
            std::cout << pt << " ";
        std::cout << "]\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An expection was caught: " << ex.what() << "\n";
        return 1;
    }
}
