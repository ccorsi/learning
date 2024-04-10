# Continuously Processing Point Instance Data Loader Example

The following example will how the data loader template class can really
shine.  The use case that we are showing here is where you are loading
data from an input stream and processing each populated instance as they
are populated.  You can consider the case of a producer consumer
archetecture.  The data loader template class can be used as a consumer
that will process the input stream and forward the instantiated instance
to another thread.

While this example isn't performing the type of action mentioned above.
It will nonetheless show how you can use the data loader template class
to perform such a task.  In this example we will be populating a point
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

using the following point reader.

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

The above point reader uses the field parameter to determine which point field
is being loaded from the input stream.  In this case, the field passed as 0 is
associated with the x value of the point instance and the field passed as 1 is
associated with the y value of the point instance.

Each populated point will then be added to a point vector using the following
point vector reader.

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

You will notice that the defined data loader template class within the
_point\_vector\_reader_ sets the fields to _2_.  This tells the data loader
template class that the passed _point\_reader_ reader will be called twice,
once for the x value and another time for the y value.   This is useful in
the case that the different values of the instance are separated by
non-standard white spaces like ','.  Which is the case in the above example.
The _is\_space\_or&lt;','&gt;_ will insure that not only standard white spaces
will be skipped but also the ',' character will also be skipped when loading
the x and y values of the point instance.

Finally, the top-level data loader template class definition will be the
following.

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
        is_space_or<','>
    > loader(points);
    // ...initialize the points
    in >> loader;
```

The vector will then be forwarded to a method that will then consume the
points.
