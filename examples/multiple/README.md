# Multiple Field Data Loader Example

The following example will show you how you can populate an instance
on a per field basis and have the data loader template class manage
the skipping of the delimiters between the instance fields.  We are
then going to populate the following point class.

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

The data loader template class then needs a point reader that will be used
to load the data that will populate a point instance.  We are then going
to use the following point reader.

```cpp
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
```

The above point reader will receive a reference to a point instance that will
be populated.  The third field parameter is used to determine if we are loading
the x or the y value of the point instance.  The passed value is then used to
store the loaded value in the point reader struct.  The same point instance
will be passed for each field value.  Thus, if you expected the data loader
template class to pass the same point instance for the two fields.  The data
loader template class will then pass the same point reference for each
field.

Now that we've defined a point reader that will be used to populate a point
instance.  We can now define the data loader template instance as follows.

```cpp
    point value;

    // define the dataLoader for a point instance...
    dataLoader<
        point,                      // type of instance to populate
        char,                       // type of input stream
        point_reader,               // type of reader used to load data
        2,                          // number of calls per instance
        is_character<char,'{'>,     // the opening character for a point
        is_character<char, '}'>,    // the closing character for a point
        is_space                    // operator used to skip white like spaces
    > loader(value);                // pass a reference to the point instance
    // ...initialize the value
    in >> loader;
```

The above definition will then populate a point instance that can then be
used later in the code.
