# Integer Data Loader Example

The following example shows how one can use the data loader template
class to load primitive types like an integer.  This data loader
template class makes this process fairly easy compared to populating
a complex data type like a struct or a class type.  While those types
will require you implement a reader object that implements the
_std::istream & operator()(std::istream & in, Type & type, int field)_
operator.  Populating a primitive type simplifies this process and
only requires that you define the first twp parameters of the data loader
template class.  For instance, the data loader template class for an
int can be defined as:

```cpp
    int value;

    // define the dataLoader for a int primitive...
    dataLoader<int,char> loader(value);
    // ...initialize the value
    in >> loader;
```

The above data loader definition will use the default definition of
the other parameters to populate the integer value using the input
stream.  The above definition will skip all white space characters
that the _std::isspace_ standard method prior and after populating
the integer value.  The only caveat is that the above compact
definition is only useful whenever you are using the _char_ input
stream.  At the moment, a _wchar\_t_ input stream will require a more
elaborate definition.

Thou this example shows one how to use the data loader template class
to load primitive types.  It is probably easier for one to just by-pass
the use of the dataloader template class and just use the input stream
directly to load the primitive data types.
