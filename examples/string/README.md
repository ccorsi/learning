# String Data Loader Example

The string data loader example provides two examples on how one can use the
dataloader template class to load a string from an input stream.  The
difference between the two examples is the definition of the reader that
is used to load the string from the input stream.  The first reader will
load the string into the passed instance in a single step and is defined
as:

```cpp
struct string_reader {
    std::istream & operator()(std::istream & in, std::string & str, int field) {
        char chr = in.get();
        while (chr != std::string::traits_type::eof() && chr != '"') {
            chr = in.get();
            if (chr == '\\') {
                chr = in.get();
                if (chr == std::string::traits_type::eof()) {
                    return in;
                } // if (chr == std::string::traits_type::eof())
            } // if (chr == '\\')
            str += chr;
        } // while (chr != std::string::traits_type::eof() && chr != '"')
        return in;
    }
};
```

As you can see this reader manages the whole process of loading the string
from the first access after the open character to the closing character.
Note that it doesn't consume the closing character because this will cause
the data loader template class from continuing to try and load more characters
in the passed instance.

The other reader will load a single character at the time and add it to the
passed string.  This reader is defined as:

```cpp
struct string_single_character_reader {
    std::istream & operator()(std::istream & in, std::string & str, int field) {
        char chr = in.get();
        if (chr != std::string::traits_type::eof()) {
            if (chr == '\\') {
                chr = in.get();
                if (chr == std::string::traits_type::eof()) {
                    return in;
                } // if (chr == std::string::traits_type::eof())
            } // if (chr == '\\')
            str += chr;
        } // if (chr != std::string::traits_type::eof())

        return in;
    }
};
```

The above reader will only append the next character to the passed string.
The data loader template class will manage the characters that the reader
will process.  This removes the need to check for the closing character and
leaves this reader with the responsibility of processing escape characters.

The above readers will then use the following dataloader template definition:

```cpp
    std::string value;

    // define the dataLoader for a string...
    dataLoader<
        std::string,
        char,
        string_single_character_reader,
        1,
        is_character<char,'\'','"'>,
        is_character<char,'\'','"'>,
        is_space,
        is_space_noop<char> // This is required when using the string_single_character_reader reader
    > loader(value);
    // ...initialize the string value
    in >> loader;
```

The above data loader definition chould be used by the string_reader and
string_single_character_reader readers.  The only requirement is that the
string_single_character_reader reader requires that you set the InnerSpace
template parameter to is_space_noop.  Without using this operator the
spaces within the string will be skipped and not added to the passed
string.
