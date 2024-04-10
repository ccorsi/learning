#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "data_loader.h"

using namespace valhalla::loader;
using namespace valhalla::checkers;

class point {
    uint16_t m_x, m_y;
public:
    point() = default;
    point(uint16_t x, uint16_t y) : m_x(x), m_y(y) {}

    friend std::ostream& operator<<(std::ostream& out, const point & pt) {
        return out << "(" << pt.m_x << "," << pt.m_y << ")";
    }
};

class header {
    uint16_t m_major_version,
        m_minor_version,
        m_patch_version;
    std::vector<point> m_points;
public:
    header() = default;
    header(uint16_t major, uint16_t minor, uint16_t patch, std::vector<point> & points) :
        m_major_version(major), m_minor_version(minor), m_patch_version(patch),
        m_points(points) {}

    friend std::ostream& operator<<(std::ostream& out, const header & hdr) {
        out << "header[major=" << hdr.m_major_version << ",minor="
            << hdr.m_minor_version << ", patch=" << hdr.m_patch_version
            << ", points=[ ";
        for (auto & pt : hdr.m_points)
            out << pt << " ";
        return out << "]]";
    }
};

const uint8_t magic[]{
    static_cast<uint8_t>(0x12),
    static_cast<uint8_t>(0x34),
    static_cast<uint8_t>(0x56),
    static_cast<uint8_t>(0x78)
};

std::istream& load_uint16_t(std::istream & in, uint16_t & value) {
    // clear the current quantity of the passed value;
    value = 0;

    for (int cnt = 0 ; cnt < 2 ; cnt++) {
        // get the next byte from the input stream...
        uint8_t chunk = in.get();
        // ...determine if you've reached the eof
        if (in.eof()) {
            throw std::runtime_error("Insufficent data to produce uint16_t value");
        } // if (in.eof())
        // multiple by 256...
        value >>= 8;
        // ...add current chunk of the value
        value += chunk;
    } // for (int cnt = 0 ; cnt < 2 ; cnt++)

    return in;
}

struct point_reader {
    uint16_t x, y;

    std::istream& operator()(std::istream& in, point & pt, int field) {
        switch(field) {
            case 0: // load x
                return load_uint16_t(in, x);
            case 1: // load y
            {
                load_uint16_t(in, y);
                pt = point(x,y);
                // std::cout << "created point: " << pt <<"\n";
                return in;
            }
                // return (load_uint16_t(in, y), pt = point(x,y), in);
            default:
                throw std::runtime_error("invalid field");
        } // switch(field)

        return in;
    }
};

struct header_reader {
    uint16_t major, minor, patch, count;
    std::vector<point> points;

    std::istream& operator()(std::istream& in, header & hdr, int field) {
        switch(field) {
            case 0: // read header
            {
                const int size = (sizeof(magic) / sizeof(magic[0]));

                for (auto v : magic)
                    if (static_cast<uint8_t>(in.get()) != v)
                        throw std::runtime_error("Invalid header type");

                return in;
            }
            case 1: // read major
                return load_uint16_t(in, major);
            case 2: // read minor
                return load_uint16_t(in, minor);
            case 3: // read patch
                return load_uint16_t(in, patch);
            case 4: // read count
                return load_uint16_t(in, count);
            case 5: // read point
            {
                // std::cout << "count = " << count << "\n";
                while (count-- > 0) {
                    point pt;
                    // initialize a point data loader instance...
                    dataLoader<
                        point,
                        char,
                        point_reader,
                        2,
                        is_character_noop<char>,
                        is_no_character<char>,
                        is_space_noop<char>
                    > loader(pt);
                    // ... populate the point instance
                    in >> loader;

                    // add the populated point instance to the point vector
                    points.push_back(pt);
                } // while (count-- > 0)

                hdr = header(major, minor, patch, points);

                return in;
            }
            default:
                throw std::runtime_error("Invalid field");
        }
    }
};

void store_uint16_t(uint16_t v, std::fstream &out) {
    uint8_t e = (v & 0xff) >> 8;
    out.put(e);
    // std::cout << "Stored: '0x" << std::hex << static_cast<uint16_t>(e) << std::dec;
    e = v & 0xff;
    // std::cout << "', '0x" << std::hex << static_cast<uint16_t>(e) << std::dec << "'\n";
    out.put(e);
}

void create_data_file()
{
    std::fstream out{"data", out.binary | out.out | out.trunc};

    const int size = (sizeof(magic) / sizeof(magic[0]));

    for (auto v : magic) {
        out.put(v);
        // std::cout << "Stored: '0x" << std::hex << static_cast<uint32_t>(v) << std::dec << "\n";
    } // for (auto v : magic)

    const uint16_t
        major = 1,
        minor = 3,
        patch = 13;

    store_uint16_t(major, out);
    store_uint16_t(minor, out);
    store_uint16_t(patch, out);

    std::vector<uint16_t> points = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10
    };

    uint16_t count = static_cast<uint16_t>(points.size()) / 2;

    store_uint16_t(count, out);

    for (uint16_t v : points) {
        store_uint16_t(v, out);
    } // for (uint16_t v : points)

    out.close();
}

int main(int argc, char** argv) {
    std::cout << "Calling protocol reader example\n";

    try {
        create_data_file();

        // create an input stream
        std::fstream in{ "data", in.binary | in.in };

        // std::cout << "magic size = " << size << "\n";

        if (in.peek() == std::char_traits<char>::eof()) {
            std::cout << "Input file is empty.\n";
            return 1;
        } // if (in.peek() == std::char_traits<char>::eof())

        header value;

        // define the dataLoader for a header instance...
        dataLoader<
            header,
            char,
            header_reader,
            6,
            is_character_noop<char>,
            is_no_character<char>,
            is_space_noop<char>
        > loader(value);
        // ...initialize the header value
        in >> loader;

        std::cout << "value = " << value << "\n";

        return 0;
    } catch (std::exception & ex) {
        std::cout << "An exception was caught: " << ex.what() << "\n";
        return 1;
    }
}
