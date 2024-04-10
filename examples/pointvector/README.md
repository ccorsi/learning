# A Point Vector Data Loader Example

The following example will show you how to use the data loader template class
to load a vector of point instances.  The data loader template class provides
the ability to dynamically load zero or more entries into a point vector.  In
this example, the data loader template class will populate the following point
class.

```cpp
class point {
    int m_x, m_y;
public:
    point() = default;
    point(int x, int y) : m_x(x), m_y(y) {}

    friend std::ostream & operator<<(std::ostream & out, const point & pt) {
        return out << "point[x=" << pt.m_x << ",y=" << pt.m_y << "]";
    }
};
```

To populate the point above, the data loader template class will require the
definition of a point reader.  We then define the following point reader.

```cpp
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
```

While the above point reader will be used to populate point instances.  We
still require a reader that will populate the point vector.  We then define
the following point vector reader.

```cpp
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
```

The above point vector reader can then be used by the data loader template
class to load point instances into a point vector.  We can then define the
data loader template class that will populate the point vector as.

```cpp
    std::vector<point> points;

    // define the dataLoader for a int primitive...
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
    // ...initialize the points vector
    in >> loader;
```

We now have defined a data loader template class above that is capable of
loading point instances into a point vector instance.  Where the point
instance have the format { <x_value> <y_value>} and the point vector has
the format [ <point> ... ].  The data loader template class removes the
need to worry about implementing the need to check for the different
delimiters used and allow one to focus on how to format and load the
data into the point vector.
