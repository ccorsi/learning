# Data Loader

This project contains a flexible data loader that can be used to load data
from an input stream into an instance of a class.  The data loader provides
different ways that a user can load data into their objects.

Before diving into any specifics about the data loader template class.  We
should start by describing the motiviation behind this class.  The
incarnation of the data loader template class was inspired by how one can
initialize a complex data type within a C++ source code file.  For instance,
we can initialize a std::vector&lt;int&gt; by using the following syntax,

```cpp
    ...
    std::vector<int> data = { 1, 2, 3, 4, 5 };
    ...
```

While the above is fairly simple to add within a C++ source file.  We will not
need to use the data loader template class to perform such an initialization.
The benefit of the data loader template class is when you have multiple
instances of data that we'd like to load during runtime.  This is when you
start to see the benefit of using the data loader template class.  It allows
one to be able to alter the data file without having to apply any changes to
the source file itself.  Now that we have the inspiration of the data loader
template class.  We turn to describing its definition and use cases.

The first thing that the data loader template class needs is its template
parameters. The data loader template class requires at least two out of eight
template parameters.  The first template parameter is the **Type** of instance
that is being populated.  It them expects the **Type** template parameter which
is used to define a basic\_istream&lt;**Char**&gt; input stream.  This can be set
to __char__ or __wchar_t__ **Char** type input stream.  This is the default
requirement that one needs to be able to use the data loader template class to
load data into an object instance.

While the above describes the required minimum template parameters.  It doesn't
explain how one goes about initializing and using a data loader template class.
We will start by explaining the other aspects of the data loader template class.
The data loader template class is defined as following:

```cpp
template<
    typename Type,
    typename Char,
    typename Reader = reader<Type,Char>,
    int fields = 1,
    typename IsOpenChar = void,
    typename IsCloseChar = void,
    typename IsSpace = valhalla::checkers::is_space,
    typename IsSpaceInner = IsSpace
>
class dataLoader {
    ...
}
```

As one notices there are several parameters that are part of the dataLoader
template class.  Thus, before describing how one uses this template class.  We
will describe what each parameter means.

| --- | --- |
| __Parameter Name__ | __Description__ |
| Type | The type of object being populated |
| Char | The type of input stream being used, __char__ or __wchar_t__ |
| Reader | The Reader class used to process the data with |
| fields | The number of fields associated with the Type object, defaults to 1 |
| IsOpenChar | Character used to demarcate opening of object data |
| IsCloseChar | Character used to demarcate closing of object data |
| IsSpace | Which spaces to skip before and after opening and closing characters |
| IsSpaceInner | Which spaces to skip within the opening and closing characters |

While the above is fairly clear it doesn't explain the details that are
involved with these template parameters.  Let us then start with the most
obvious statement.  That is that the __Type__ is the object that we intend to
populate.  This can be any class, struct or primitive type like int, long,
std::string, etc.  Thou we know what object we want to populate we now need
to determine the type of stream that we are using.  This is accomplished
using the __Char__ template parameter.  This basically is used to tell the
data loader template class if we are using a __char__ or __wchar_t__ input
stream.  We've thus have explained the most basic data loader template
parameters.  We now turn to the more involved template parameters.

We then start with the how the __Reader__ template parameter is used.  This
parameter has to define a struct or class that implements the following
operator:

```cpp
    virtual std::basic_istream<Char> & operator()(std::basic_istream<Char> & in, Type & type, int field);
```

The above operator will be called by the data loader template class to actually
load the data into the Type instance.  The first and second parameter is self
explanatory but the third parameter is specific to how one whats to load the
data into the Type instance.  For instance, one can define a struct or class
that implements the above operator to populate a different field or it can read
all of the data for all the fields for the Type instance.  Let us then look at
what this might look like.  Let us then take a simple class with two fields:

```cpp
class point {
    int m_x, m_y;
public:
    point() = default;
    point(int x, int y) : m_x(x), m_y(y) {}
    void set_x(int x) { m_x = x; }
    void set_y(int y) { m_y = y; }
};
```

We now look at how we can populate a point instance using the data loader
template class.  Before we can talk about how to load the point instance using
the data loader template class.  We need to explain what and how to use the
remaining template parameters.  Let us start with the field template parameter.

The integer __fields__ template parameter is used to tell the data loader how
many fields are associated with the __Type__ instance.  For instance, the
point class has two fields associated to it, m\_x and m\_y.  The __fields__
template parameter can be set to 2 or 1 depending on how you intend to load
the data into a point instance.  At the moment, we will not describe why and
how setting the __fields__ value to 1 or 2 can be used within the data loader
template class.  Let us then talk about the __IsOpenChar__ and the
__IsCloseChar__ template parameters next.

The __IsOpenChar__ and __IsCloseChar__ template parameters are used to inform
the data loader template class which characters are used to encapsulate the
data that will be loaded into the instance.  These characters can be anything
that one chooses.  For example, the point might use the '{' and '}' characters
as the open and close characters to delineate what is part of a point instance.
For example we have an input stream that contains the following:

```
{ 1 2 }
```

The data loader template class can then use this information to load the value
of 1 and 2 into the point instance.  While this is an example of a use case
that you can use.  There is no requirement that you need to state a given
set of open and close characters.  For instance, a simple integer doesn't
require any encapsulating characters.  The data loader template class offers
a solution to this case.  These are just some examples that can be used.
There are several implementations that one can pick from depending on the
particular use case that one encounters.  Here is a table of the different
implementations that can be used to set the __IsOpenChar__ and __IsCloseChar__
template parameters:

| Name | Description |
| --- | --- |
| is\_character\_noop&lt;Char&gt; | This is used when there is no encapsulating character |
| is\_character&lt;Char,Char...Chars&gt; | This is used to define one or more character that is used to encapulate a data object |
| is\_no\_character&lt;Char&gt; | This is used in the case that we are loading a primitive type and we don't want to consume the character.  This is useful only for the __IsCloseChar__ template parameter  |

While the first two options are clear enough the requirement of the third isn't
as obvious.  The last option was required to solve a specific type of issue
that I was not able to resolve at the moment.  It is possible that that case
will have a solution in the future but not at this time.  While the above options
should cover most if not all of the different cases.  You can implement your own
by creating a struct or class that implements the following operation:

```cpp
template<typename Char>
struct characters {
    bool operator()(Char chr);
};
```

Basically, the operator method should return true if the passed character chr is
the expected character else false.

Let us then talk about the remaining __IsSpace__ and __IsSpaceInner__ template
parameters next.

The __IsSpace__ and __IsSpaceInner__ template parameters are used to skip
spaces that need to be skipped before reading the data to store into the
data instance.  The __IsSpace__ is used to skip space-like characters prior
to the instance data to be read.  While the __IsSpaceInner__ is used to
skip spaces that seperate the fields values within the open and close
characters.  There are several predefined space-like operators avaliable:

| Name | Description |
| --- | --- |
| is\_space\_noop&lt;Char&gt; | This is used when no spaces need to be skipped for Char stream type, char or wchar\_t |
| is\_space | This is a wrapper around the standard isspace method |
| is\_wspace | This is a wrapper around the standard iswspace method |
| is\_space\_or&lt;char...Chars&gt; | This extends the is\_space by including one or more user defined white space characters |
| is\_wspace\_or&lt;wchat_t...Chars&gt; | This extends the is\_wspace by including one or more user defined white space characters |

While the above options should cover most if not all of the different cases.
You can implement your own by creating a struct or class that implements the
following operation:

```cpp
template<typename IntType>
struct space {
    bool operator()(IntType chr);
};
```

Where the IntType is either **int** or **wint\_t** depending if you are using
a **char** or **wchar\_t** input stream.

Now that we've described the different template parameters for the data loader
template class.  We can now look at how we can use the above information to read
the data into a point instance using the data loader template class.

This example will populate the point instance using a single instance of the
data loader template class.  We need to first create a point reader that will
be passed to the data loader template class that will read the data and
populate the point instance.

```cpp
struct point_reader {
    int m_x;
    std::istream & operator()(std::istream & in, point & p, int field) {
        switch (field) {
            case 1: // m_x
                in >> m_x;
                break;
            case 2: // m_y
                int y;
                in >> y;
                p = point(m_x, y);
                break;
            default:
                throw std::runtime_error("Invalid field passed");
        }
    }
};
```

The above reader implementation will be used by the data loader template class
to load the data into the point instance that is passed by reference.  Let us
now create an instance of a data load template class using the above reader to
load data into an instance of a point class.

```cpp
#include <data_loader.h>

using namespace valhalla::loader;
using namespace valhalla::checkers;

std::istream& foo(std::istream& in, point & pt) {
    dataLoader<
        point,
        char,
        point_reader,
        2,
        is_character<char, '{'>,
        is_character<char, '}'>,
        is_space
    > pointLoader(pt);

    return in >> pointLoader;
}
```

The above will then populate the passed pt point to the dataLoader instance
with the data that is processed within the input stream.  The above is one
example of how one can use the data loader template class to populate
instances.  The examples sub-directory contains example on how you can use
the data loader template class within different situations.
