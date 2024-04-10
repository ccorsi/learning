# Point Data Loader Example

This example shows one how to use the data loader template class to initialize
a point instance from an input stream.  It will populate the following class:

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

using the following data input.

```
{ 13 45 }
```

To be able to use the data loader template class to load the point instance.
We will require a reader that will load the data into the point instance.
We thus define a point reader as:

```cpp
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
```

There are a few things to note with the above implementation definition of
the point_reader.  The first thing to notice is that the point_reader
implements the _std::istream& operator()(std::istream&, point&, int)_
operator.  The other not is that it doesn't expect to use the _field_
parameter and will read and load the _x_ and _y_ values directly.  Upon
doing that it will then assign the passed point instance.

The data loader template class will then be defined as:

```cpp
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
```

Upon executing the input operator with the defined loader instance.  The
passed point value will be populated with the data value from the input
stream.
