---
layout: resume
title: General Class Loaders
subtitle: Input Stream Loaders
page-width: lg
css: /assets/css/valhalla.css
---

# Introduction

This section is an outgrowth of my work on using
<a href="http://google.github.io/googletest/" target="_blank">GoogleTests</a> while solving problem from
<a href="https://www.techiedelight.com/" target="_blank"><i>Techie Delight &lt;/&gt;</i></a>.  I had
initially created loaders used to load vector type instances,
<a href="https://github.com/ccorsi/learning/blob/17cd3df535d47b3ce0f2c81955a0071f19812163/utils/includes/loader.h#L157" target="_blank">vectorLoader&lt;E,Container&gt;</a>.
This then included a matrix type,
<a href="https://github.com/ccorsi/learning/blob/17cd3df535d47b3ce0f2c81955a0071f19812163/utils/includes/loader.h#L213" target="_blank">maxtrixLoader<E,Container,Matrix></a>,
loader.  This became the beginning of multiple implementations for different container types.

- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/set_loader.h" target="_blank">setLoader<E,Set,Char,IsSpace></a>
- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/pair_loader.h" target="_blank">pairLoader<leftType,rightType,Char,openChar,closeChar,IsSpace></a>
- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/tuple_loader.h" target="_blank">tupleTripletLoader<TypeOne,TypeTwo,TypeThree,Char,OpenChar,CloseChar,IsSpace></a>
- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/tuple_loader.h" target="_blank">tupleLoader<TupleType,Char,OpenChar,CloseChar,IsSpace></a>
- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/primitive_loader.h" target="_blank">primitiveLoader<E,Char,IsSpace></a>
- updated <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/vector_loader.h" target="_blank">vectorLoader<E,Container,Char,IsSpace></a>
- updated <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/matrix_loader.h" target="_blank">matrixLoader<E,Container,Matrix,Char,IsSpace,VectorLoader></a>
- <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/map_loader.h" target="_blank">mapLoader<Key,Value,Map,Char,openChar,closeChar,dividerChar,IsSpace></a>
- general <a href="https://github.com/ccorsi/learning/blob/cpp_data_structs_and_algos/utils/includes/vector_loader.h" target="_blank">dataLoader<Type,Char,Reader,states,IsOpenChar,IsCloseChar,IsSpaceOuter,IsSpaceInner></a>

While the above selections of templated loader classes slowly expanded.  The dataLoader implementation is
the one that can encapsulate all of the prior implementations.  This templated loader class can be
configured to perform any of the prior loader classes.  It has become the bedrock of all combinations of
data loaders used.  We will start by discussing the different loaders besides the dataLoader in the next.
We will then leave the discussion on the dataLoader within its own section.

## An Abundance of Data Loaders

As mentioned above, the creations of the different template loaders started with a need to be able to load
data within different types of sources, from primitive types to complex data types like containers and maps.
The initial requirement was to be able to load data within a vector type container.  This instigated the
creation of the vectorLoader template class.

## Towards A General Data Loader Class

The above implementations of templated loader classes got me thinking that it would be better that we could
use a single loader class to be able to load any type of data classes.  This started me on the road of
creating multiple versions of the templated dataLoader classes.  In all I have devised five different
versions of the dataLoader template class.  Each of these version is contained with a v# namespace to allow
for prior versions to still be used while implementing improved versions throughout the development process.
We will then discuss the different versions and explain the difference between them.  This will hopefully
clarify the reasons why I've implemented these different versions.  After completing the description of the
different dataLoader implementations.  The different typenames associated with the dataLoader will be
expanded on to clarify any discrepencies that might of occurred in the prior dataLoader explanations. Let us
then begin by talking about the firsts version of the dataLoader.

### Data Loader Version One

The first version of the templated dataLoader class was instigated by the fact that is seemed like a waste to
be creating different templated loader classes.  These templated classes started to contain similar base
implementations with some tweaks to load each different type of instance.  This got me thinking that I could
take those similarities and produce a base templated loading class that can be used to load different type of
instances.  This lead to the first version of the dataLoader.

```cpp
template<
    typename Type,
    typename Reader,
    typename Char,
    typename IsOpenChar,
    typename IsCloseChar,
    typename IsSpace = valhalla::utils::checkers::is_space
>
class dataLoader {
    ...
};
```

The <em>Type</em> is the type of instance that is being loaded.  This can be anything that one is trying to
load like primitive types or complex types.  The <em>Char</em> is the type of input characters that will be
used to read the data for the Type instance.  This can be any type that the std::basic_istream implementation
can read, usually char and wchar_t.  While the Type and Char definitions are fairly obvious the next set of
template typenames of the dataLoader are not that simple.  These will require more clarifications and will be
tackled individually.  We will leave the definition of the Reader typename to last since this is most detailed
one of the lot.

The <em>IsOpenChar</em> and <em>IsCloseChar</em> typenames are used to look for opening and closing characters
that might delineate data like for a container like a vector.  It might delineate the data within the '{' and
'}' opening and closing characters.  These two types do require that they implement the
<em>bool operator()(std::basic_istream&lt;Char&gt;&amp;)</em> operator.  This will be called before and after
loading each entry in the vector container instance.

The IsSpace typename is used to skip space like characters that could hinder the loading of the data for the
instance being loaded.

The Reader is a type that is used to load the data into a Type instance.  It is then required to be able
to actual do the real work in loading the data into a Type instance.  This typename is the only real work
required by the developer to be able to use the dataLoader.  The other typenames provide their own
implementations that should cover most if not all other situations.  While the Reader typename will
understand how to read the data into the Type instance.  The main feature of the Reader typename is that
it needs to be able to implement the
<em>std::basic_istream&lt;Char&gt;&amp; operator()(std::basic_istream&lt;Char&gt;&amp;, Type &amp;)</em>
operator and the <em>ctor(Type&amp;)</em> constructor.  This are the expected constructor and operator
that the dataLoader will be using to call the Reader typename such that it will load the data into the
Type instance that was passed to the Reader constructor.

### Data Loader Version Two

The second version of the dataLoader included the ability to state how many fields are associated with
the given Type.  The dataLoader template class thus has the following signature:

```cpp
template<
    typename Type,
    typename Char = char,
    typename Reader = dataReader<Type,Char>,
    typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsSpace = valhalla::utils::checkers::is_space
>
class dataLoader {
    ...
};
```

This feature becomes useful for data Types like the following example:

```cpp
class person {
    std::string m_fname,m_lname;
public:
    ...
};
```

The above class requires two fields to be loaded.  The m_fname and m_lname fields need to be populated.
The updates to the dataLoader implementation allows one to be able to inform the dataLoader class that
we are not done loading data into the Type instance.  The dataLoader will then continue to call the
Reader instance until all of the fields have been loaded.  This change doesn't add any additional
parameters to the dataLoader template class. The difference is with the associated Reader parameter type.
The first version of the Reader class required that it implemented the
<em>std::basic_istream&lt;Char&gt; &amp; operator()(std::basic_istream&lt;Char&gt;&amp;)</em> operator.
Version two requires that the Reader parameter type extends the <em>dataReader&lt;Type,Char,states&gt;</em>
template class.  The dataReader template class requires that you implement the
<em>std::basic_istream&lt;Char&gt;&amp; load(std::basic_istream&lt;Char&gt;&amp;)</em> protected method.
The state parameter is used to define how many fields the Type instance has to be populated.  The
<em>get_data</em> method returns a reference to the Type instance.  The <em>state</em> method can be used
to determine which field is being read next.  This removes the need for you to keep track of which field
is being populated.  Let us then assume that we created a PersonReader that extends the dataReader
template class.  Here is a possible implementation.

```cpp
class person : public dataReader<person,char,2> {
protected:
    std::istream& load(std::istream& in) {
        switch(state()) {
            case 0: // load m_fname field
                ...
                break;
            case 1: // load m_lname field
                ...
                break;
            default: // invalid field
                throw std::runtime_error("Invalid field");
        }

        return in;
    }
    ...
};
```

The load method thus will read the input data and populate the different person fields.  The form in how
this is done is left to the developer.  While the dataReader and dataLoader template classes perform the
grunt work of clearing the way to easily read the different fields of the person instance.

### Data Loader Version Three

The third version of the dataLoader was inspired by the fact that implementing the load method was too
much of an overhead.  Thus removing the requirement of implementing the load method to just implementation
the Type <em>operator()(std::basic_istream&lt;Char&gt;&amp;,Type&amp;,int)</em> operator.  This remove the
extra overhead of extending the dataReader template class and just required an extension of the Type
classes.  Which makes more sense with what we are trying to implement.  Thus the dataLoader template class
is still defined as:

```cpp
template<
    typename Type,
    typename Char = char,
    typename Reader = dataReader<Type,Char>,
    typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsSpace = valhalla::utils::checkers::is_space
>
class dataLoader {
    ...
};
```

Taking the person class from above we could then just implement the following input operator.

```cpp
class person {
    std::string m_fname, m_lname;
public:
    friend std::istream& operator>>(std::istream& in, person & data, int state) {
        switch(state) {
            case 0: // load m_fname data
                ...
                break;
            case 1: // load m_lname data
                ...
                break;
            default: // invalid field entry
                throw std::runtime_error("Invalid person field");
        }
        return in;
    }
    ...
};
```

As is seen in the above sample implementation.  The developer doesn't need to extend the dataReader
template class but just implement the required operator to be able to load the fields into the person instance.

The signatures to the dataLoader and dataReader doesn't change compared to version two.  The only difference
was that the developer implement the above operator instead of extending the dataReader template class.

### Data Loader Version Four

Verson four of the dataLoader template class implemented some cleanup type changes that didn't involve much
effort on the developer compared to using version three of the dataLoader template class implementation.
The only change between the two is that the states parameter type was added to the dataLoader template
class. Thus the dataLoader template class now needs to use the following signature.

```cpp
template<
    typename Type,
    typename Char,
    typename Reader = reader<Type,Char>,
    int states = 1,
    typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsSpace = valhalla::utils::checkers::is_space
>
class dataLoader {
    ...
};
```

When comparing to version three you will notice that the states int parameter was now included as part of
the list of parameter types for the dataLoader template class.  This removes the need to pass the Reader
parameter as a dataReader type.  Instead the dataReader will be passed the states parameter by the
dataLoader template class instead.  This adds an extra indirection but it removes some of the work on the
developer when initializing the dataLoader template instance.

### Data Loader Version Five

Version five of the dataLoader that has had the benefit of the experience of using the prior four versions
of the dataLoader template class implementations.  This version resolves a subtle issue with the IsSpace
parameter type.  The issue is that the Type surrounding space skipping process might be different than the
inner Type space skipping process.  This was then resolved by seperating the IsSpace parameter type into a
IsSpaceOuter and IsSpaceInner parameter types.  Thus the dataLoader template class signature has been
transformed to.

```cpp
template<
    typename Type,
    typename Char,
    typename Reader = reader<Type,Char>,
    int states = 1,
    typename IsOpenChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsCloseChar = valhalla::utils::checkers::is_character_noop<Char>,
    typename IsSpaceOuter = valhalla::utils::checkers::is_space,
    typename IsSpaceInner = IsSpaceOuter
>
class dataLoader {
    ...
};
```

As seen above the seperation of the IsSpace parameter type into the IsSpaceOuter and IsSpaceInner parameter
types is the only real difference between the prior implementation.  The dataLoader will then use the
IsSpaceOuter before and after loading the data for the Type instance.  While the IsSpaceInner is called
whenever data has been processed for the instance Type.

### Data Loader Version Six

We've reached the latest version of the dataLoader that has had the benefits of the experience of using the
prior five versions of the dataLoader template class.  This version has evolved within the implementation and
the signature of the dataLoader template class hasn't changed.  The internal change that this version contains
is the fact that it will generate different code depending if the __Type__ template parameter defines the
&lt;&lt; operator like the primitive types.  The generated code doesn't require any overhead and that overhead
is compiled out.  Thus, the dataLoader template class signature hasn't changed and it still is defined as:

```cpp
template<
    typename Type,
    typename Char,
    typename Reader = reader<Type,Char>,
    int states = 1,
    typename IsOpenChar = void,
    typename IsCloseChar = void,
    typename IsSpace = valhalla::utils::checkers::is_space,
    typename IsSpaceInner = IsSpace
>
class dataLoader {
    ...
};
```

The change is that now you can simplify the definition of the loading of types that implement the &lt;&lt;
operator as:

```cpp
void fcn(...) {
    ...
    int value;

    dataLoader< int, char > loader(value);
    in >> loader;
    ...
}
```

The above is much simplier to define and use than the prior version of the dataLoader template class for
types that implement the &lt;&lt; operator.  The main point is that just that the above definition will
generate more efficient code than the prior version of the dataLoader template class.  While for complex
types the generated code is similar to the prior version of the dataLoader template class.

Now that we've completed the explanation of the different dataLoader implementations.  We will then
describe in more detail the different parameter types that are being used by the dataLoader and the inner
dataReader template implementations.

## Supporting Data Loader Types

The different implementations of the dataLoader template classes expect parameter types used to determine
beginning/ending characters and space skipping operators.  These were only glossed over in the prior
sections and here we will be expanding on what each of these implementations offer.  While showing one
how these are used to provide a required feature.

### Character Checking Operators

We then start by describing the character checking operators.  These are the IsOpenChar and IsCloseChar
parameter types used throughout the dataLoader template class.  There are several version of these operators
that one can use with the dataLoader template class.  Each will have unique features that are applicable to
developers.  These implementations should be able to cover most if not all possible situations that a
developer would encounter.  We are going to describe each in turn and how they should be used in context to
the dataLoader template class.  Here are a list of the different available character checking operators

- is_character_noop&lt;Char&gt;
- is_character&lt;Char,Char...Chars&gt;
- is_no_character&lt;Char&gt;

The above list is fairly short but it should cover most cases that a developer would require when checking
for opening and closing characters.  We will start by describing the <em>is_character_noop</em> operator.

The is_character_noop operator is used when the data that you are reading isn't wrapped by a opening
and closing character.  This could be the case when you are just reading a primitive value type from
the input stream.  These usually won't be wrapped within opening and closing characters.  Thus the
need for this type of character check operator.  The main requirement for its use is that you need
to state what type of input type it will be processing.  By default, this can be a <em>char</em> or a
<em>wchar_t</em> type.  It is recommended that this is only used for the <em>IsOpenChar</em>
definition.  It isn't recommended using this for the IsCloseChar definition especially for version
five of the dataLoader template implementation.  This will become clear when describing the use of
the <em>is_no_character</em> operator next.

The <em>is_no_character</em> operator was created specifically for use with the <em>IsCloseChar</em>
definition.  The reason is specific to version five of the dataLoader template implementation.  There
is a use case that the older implementations were not able to process correctly.  This is the case in
which we are loading an empty container like a vector instance.  The prior implementations were not
able to manage this conditions without the developer including code within the define reading operator.
The need to offload that requirement from the developer to the dataLoader implementation made sense.
Initially, we started to use the <em>is_character</em> operator but that was causing the dataLoader to
fail whenever their was data associated with the Type.  Thus the addition of the is_no_character
implementation.  This implementation will skip the first character encountered in the stream
when checking for the closing character if the character was not the expected character.  After
that it will perform similarly to the is_charactor operator which will be described next.

The last character check operator we will be looking at is the <em>is_character</em> operator.  This
character checker operator should be used to check for pre and post character checks.  For instance,
we are trying to load data within a vector container.  The data is between the '[' opening and ']'
closing characters like the following.

```
[ 1 2 3 4 ... ]
```

The opening and closing characters will be checked when using the is_character operator with the dataLoader
definition.  The above is_character definitions would be the following when using a char input stream.

```cpp
    is_character<char,'['> IsOpenChar;
    is_character<char,']'> IsCloseChar;
```

While the above character check is fairly simple.  The operator was designed to be able to check for
than a single character check.  For instance, we might be looking for a string of characters instead
of a single character like the following.

```cpp
    is_character<char, 'b', 'e', 'g', 'i', 'n'> IsOpenChars;
```

The above will check if the input stream contains the "begin" string
### Space Skipping Operators

We are now going to take a look at the different space skipping operators that can be used to process
input data.  The following operators can be used to skip space like input characters.

- is_space_noop&lt;Char&gt;
- is_space
- is_wspace
- is_space_or<char...Chars>
- is_wspace_or<wchar_t...Chars>

The <em>is_space</em> and <em>is_wspace</em> wraps the <em>std::isspace</em> and <em>std::iswspace</em>
standard method calls.  These will then just skip all standard white space characters that are
encountered during the reading of input data.  The difference between the two is that the is_space
expects a char input stream while the is_wspace expects a wchar_t input stream.  These two operators
couldn't be combined because of the fact that the isspace and iswspace expect an int and wint_t as well
as a char and wchar_t type.  It was then less complicated to define two seperate operators instead of
combining them together into one.  Clearly this operator can be used when skipping standard space
characters while reading input data.  If you need to skip non-standard white spaces then you would need
to use the next space skipping operators.

This is where the <em>is_space_or</em> and <em>is_wspace_or</em> operators are used.  These two
operators will check for standard white space characters and the ones that you pass to the operators.
For instance, we might need to also consider ',' as a white space separator then we could define them
as follows.

```cpp
    is_space_or<','> IsSpaceOuter;
    is_wspace_or<','> IsSpaceInner;
```

The above will skip all standard white space characters and the comma character.  The above definition
can be expanded to include more than one character that could be skipped.  For instance,

```cpp
    is_space_or<',', '|'> IsSpaceOuter;
```

The above will skip ',' and '\|' space characters as well as the standard white space characters.

## Examples

The following section will include different examples of how to best use the final version of the
dataLoader template class.  The intention is to provide template type starter code that one can
integrate into their project.

We will then start with the simplest examples and slowly move into more complicated implementations of
the dataLoader.  These should more that allow one to easily start to use the dataLoader to load data
within any type of instances.

Before jumping into the different examples that will be using the dataLoader template class to populate
different types of instances.  It should be taken for granted that the following include file and
namespace are being used.

```cpp
#include "loaders.h"

using namespace valhalla::utils::loaders::loader::v5;
using namespace valhalla::utills::checkers;
```

Now that that has been done we can now commence with the different examples that use the dataLoader
template class.

### Loading Into A Primitive Type

We will start with the simipliest dataLoader implementation that only loads a primitive type like an
integer.  Let us assume that we have an input file that contains an integer.

```
101
```

This file will then be opened and the integer value will be loaded into an int instance using a dataLoader
template definition.  The dataLoader template definition used will be the following.

```cpp
    int value;

    // Define the loader instance and associate with the value
    dataLoader<
        int,  // the type that we are assigning the value to
        char, // the input stream character trait
        reader<int,char>, // the reader operator that will populate the referenced value
        1, // the number of individual fields that the reader will populate
        is_character_noop<char>, // the expected pre-character before populating value
        is_no_character<char>, // the expected post-character after populating value
        is_space, // the different white space characters to skip around the value
        is_space // the different white space characters to skip during populating of value
    > loader(value);

    // Load the data from the input stream into the value using the loader instance
    in >> loader;
```

The above assumes that the input file was opened and is accessible using the passed istream instance.  The
defined loader instance will then load the data from the file into the value reference. Upon completing the
istream call.  The value will be set to 101.

While the above is fairly detailed, it does provide many features that one doesn't always realize is useful.
These additional features will become apparent as we delve into more complex data types that can require a
more elaborate set of loading instructions.  In the meantime, let us look at the different parameters that
are passed to the definition of the dataLoader template class.

The first parameter is the type of instance that is being populated, in this case we are populating an int.
While the second parameter tells us what type of input stream will be used to read the data that will be use
to populate the int value.  In this case, we are expecting to read a char based input stream.  We could just
as easily be loading from a file that requires a wchar_t input stream.

The third parameter is the Reader operator that will actual populate the int type.  Whenever this is called,
the dataLoader template class will have done all of the grunt work such that the Reader can easily load the
data from the input stream and assign it to the int type. There is a defined reader template class that one
can use to load types but this is only useful if the loading types define the
<em>std::basic_istream&lt;Char&gt;&amp; operator&gt;&gt;(std::basic_istream&lt;Char&gt;&amp;)</em> operator.
The use of the reader template class can be used throughout but it is better used with simple types like
primitive types or classes that contain a single field.

Let us take a look at a simple example of a class that contains a single long field.  We will define a
immutable Long class.

```cpp
class Long {
    long m_value;
public:
    Long() = default;
    Long(long value) : m_value(value) {}
    ...

    friend std::istream& operator>>(std::istream& in, Long & value) {
        in >> value.m_value;
        return in;
    }
};
```

The above class contains the following requirements to be able to use the default reader template class.
The populating class requires a default constructor and an implementation of the input operator &gt;&gt;.
These two requirements allows one to be able to use the reader template class.  Now that we have a the
required input class defined.  Let us create a simple input file that will contain the data to create an
instance of Long.

```
{ 101 }
```

Note that we've created a simple input file that looks similar to how to assign a Long instance within a
source like the following.

```cpp
void foo(...) {
    Long value = { 101 };
}
```

Since the above source code definition is familiar to C/C++ developers then being able to use a similar
syntax makes things more consistent.  We can then define the dataLoader as follows:

```cpp
   Long value;

    // Define the loader instance and associate with the value
    dataLoader<
        Long,  // the type that we are assigning the value to
        char, // the input stream character trait
        reader<Long,char>, // the reader operator that will populate the referenced value
        1, // the number of individual fields that the reader will populate
        is_character<char,'{'>, // the expected pre-character before populating value
        is_character<char, '}'>, // the expected post-character after populating value
        is_space, // the different white space characters to skip around the value
        is_space // the different white space characters to skip during populating of value
    > loader(value);

    // Load the data from the input stream into the value using the loader instance
    in >> loader;
```

The above definition will then be able to correct parse the above input file.  It will check that the
instance is surrounded by the '{' and '}' characters and call the reader inbetween these two characters.
The reader will then call use the input operator of the Long class to actually read the value into the
m_value field.  Upon completing the input call the Long instance will be populated properly.

We have then seen two examples of populating a primitive type and single class type using the default
reader template class.  We will now continue with looking at how we can implement our own reader class
to populate an instance.

### Loading Into A Simple Object Class

We are now going to take a look at populating a simple class using the dataLoader template class.
The prior section offers options on how to use the dataLoader with primitive and simple class types
using the default reader template class.  We are now going to provide other examples of how to load a
simple instance class.

While the default reader template class can be used to load any instance that one would like to load.
It isn't recommended besides for primitive types and simple class definitions.  It is recommended that
more complex classes use a different technique.  To be able to implement a reader type class.  The
developer would need to create a class that provides the following operator definition.

```
std::basic_istream<Char>& operator()(std::basic_istream<Char> & in, Type & value, int state)
```

The operator will be used by the dataReader template class that is used by the dataLoader template class
to populate the Type instance using the input stream.  Note that the method signature is compatible with
the input operator with the addition of the state parameter.  The state parameter will inform the called
operator which field is being processed.  In our case this is always going to be passed the value of 0.
Let us now look at an implementation of a user_reader class/struct for the Long class.

```cpp
struct user_reader {
    std::basic_istream<Char>& operator()(std::basic_istream<Char> & in, Long & value, int state) {
        switch(state) {
            case 0:
                {
                    long data;
                    in >> data;
                    value = Long(data);
                }
                break;
            default:
                throw std::runtime_error("Invalid state option");
        }

        return in;
    }
};
```

The above user_reader struct can then be used instead of the reader template class to load data into the
Long instance.   If we use the prior section Long data file we can then define the following dataLoader
template class definition.

```cpp
   Long value;

    // Define the loader instance and associate with the value
    dataLoader<
        Long,  // the type that we are assigning the value to
        char, // the input stream character trait
        user_reader, // the reader operator that will populate the referenced value
        1, // the number of individual fields that the reader will populate
        is_character<char,'{'>, // the expected pre-character before populating value
        is_character<char, '}'>, // the expected post-character after populating value
        is_space, // the different white space characters to skip around the value
        is_space // the different white space characters to skip during populating of value
    > loader(value);

    // Load the data from the input stream into the value using the loader instance
    in >> loader;
```

After the call of the dataLoader template class input operator.  The value will be populated with the value
of 101.  This is a similar implementation to the prior section but it removes the need for the Long class
to define the input operator.  This thus allows the developer the option to implement the input operator
that is more appropiate to their own project.  The above example offers a peek into what one can create
which can be used to load more complex instances.  We will then look at these move complex implementations
in the next sections.

### Loading A Complex Object

This section we will look at how one can go about loading a more complex data object using the dataLoader
template class.  This can still be done using the reader template class but it will require that the input
operator will need to correctly manage the parsing of the data between fields.  This takes away the
advantage of the dataLoader template class.  We will then look at how to take advantage of the dataLoader
template class by implementing our own reader class.  Let us first define a point class that will be
populated by a point_reader struct.

```cpp
class point {
    int m_x, m_y;
public:
    point() = default;
    point(int x, int y) :  m_x(x), m_y(y) {}
    ...
};
```

Now that we are class that we will be populating let us then create a simple input file like the following.

```
{ 11, 31 }
```

We are now ready to create the user defined reader that will populate a point instance.  Her is a version
of this point reader.

```cpp
struct point_reader {
    int x;
    std::istream& operator()(std::istream& in, point& value, int state) {
        switch(state) {
            case 0: // read x value
                {
                    in >> x;
                }
                break;
            case 1: // read y value and populate point
                {
                    int y;
                    in >> y;
                    value = point(x, y);
                }
                break;
            default:
                throw std::runtime_error("Invalid state input");
        }

        return in;
    }
}
```

Now that we have a user defined point reader.  We can now define the dataLoader template instance that will be
used to load the data from the input stream into a point instance.  Let us then look at the dataLoader definition.

```cpp
void load(std::istream & in) {
    point value;

    dataLoader<
        point,
        char,
        point_reader,
        2,
        is_character<char,'{'>,
        is_character<char, '}'>,
        is_space,
        is_space_or<','>
    > loader(value);

    in >> loader;
}
```

Let us now look at how the above dataLoader template definition in detail.  From the prior sections we understand what
the first three parameters mean.  We now look at why the third parameter was set to 2.  This is because the point
instance contains two fields that will be populated.  The dataLoader will then call the point_reader twice during the
loading of the data for the x and y values of the point class.  The point_reader operator will be called twice in a
row with the same point instance.  The first time the state value will be set to 0 and the second call the state value
will be set to 1.  This will allow the point_reader to correctly load and apply the correct data to be passed to the
point instance.  When the input operator call completed for the defined dataLoader template above.  The point instance
will contain the x value of 11 and the y value of 31.

We see how the data will be processed using the point_reader struct but we still haven't explained how the other parameters
are used.  The first <em>is_character&lt;char,'{'&gt;</em> parameter is used to check if the first character is an '{'
character.  The second parameter <em>is_character&lt;char,'}'&gt;</em> is used to check if the '}' character is the last
character that encloses the input data.  While the prior two parameters are used to determine if the input data is correctly
formatted.  It doesn't provide the ability to skip space like characters.  The <em>is_space</em> and
<em>is_space_or&lt;','&gt;</em> parameter definitions are used to skip space like characters.  The first definition is used
before and after the '{' and '}' characters.  While the second is_space_or definition is used to skip space like characters
and the ',' characters within the '{' and '}' characters.  The last four definitions will insure that whenever the
point_struct is called that the input data is ready to be read.

While the above example shows one how to be able to populate a complex data type using an input stream and a dataLoader template
definition.  It does show one how one can go about populating a more complex instance like a vector container.  This is
something that can we done using a combination of a reader and vector specific dataLoader template definition.  We will show how
this is done in the next section.

### Loading Entries In A Vector Container

This example will show how we can load entries within a vector using the dataLoader template class.  We will see one that will
be populated with primitive types and another example that will be populated with a more complex data type like above.  Let us
then start by creating a simple input file that will contain an array of integers that will be loaded in a integer vector.

```
{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }
```

The above input file will be used to produce an int vector that contains the values 1 through 10.  We are not ready to create
the required vector_reader struct.  Here is what is looks like.

```cpp
struct vector_reader {
    std::istream& operator()(std::istream& in, std::vector<int>& vec, int state) {
        switch(state) {
            case 0:
            {
                int value;
                in >> value;
                vec.push_back(value);
            }
                break;
            default:
                throw std::runtime_error("Invalid state");
        }

        return in;
    }
}
```

The above vector_reader will read the next entry in the integer vector and append it to the passed vector instance.  Note that
it will only load the next entry to be added to the vector instance and not all of the entries for the vector instance.  The
dataLoader template class will manage the determination if there are any remaining entries that need to be loaded or not.  The
offloads the task of determining this from the reader operator making the creation of the reader operator less complicating.

Since we've now have an instance of the vector_reader we now create the dataLoader template instance that will be used to
populate the vector instance.

```cpp
void load(std::istream& in) {
    std::vector<int> values;

    dataLoader<
        int,
        char,
        vector_reader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space,
        is_space_or<','>
    > loader(values);

    in >> loaders;
}
```

The above dataLoader definition will populate the vector instance with the integer values from 1 to 10.  Remembering that it
will check that the values are surrounded by the '{' and '}' characters.  While purging the standard white spaces before and
after the surrounding characters while also purging the ',' character within the braces.

Let us now look at vector that will load point instances instead of a primitive type like integers.  Taking the definition of
the point class from above.  We can initially create the input file that we will be using to populate the point vector instance.

```
{ { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 }, { 9, 10 } }
```

Now that we have the input file that we will be using to populate the point vector.  We can now create the following vector_reader.

```cpp
struct vector_reader {
    std::istream& operator()(std::istream& in, vector<point> & vec, int state) {
        switch(state) {
            case 0:
            {
                point value;

                dataLoader<
                    point,
                    char,
                    point_reader,
                    2,
                    is_character<char,'{'>,
                    is_character<char, '}'>,
                    is_space,
                    is_space_or<','>
                > loader(value);

                in >> loader;

                vec.push_back(value);
            }
            break;

            default:
                throw std::runtime_error("Invalid state value");
        }

        return in;
    }
}
```

Looking at the above definition, we notice that we are creating a inner dataLoader template definition to load a single point
instance.  Upon loading the point instance we then just append it to the passed point vector instance.  The shows one how simple
it is to just populate different types of instances using the dataLoader template definition.

The above examples should be more than enough for a developer to populate any type of instance using the dataLoader template
definition.  We will then offer one more example that will populate a map instance.

### Loading Entries Within A Map

As mentioned above, the prior examples should more than be enough examples that will make it easy for a developer to populate any
type of instance using the dataLoader template definition.  Let us then look at an example that just expands somewhat on what we've
seen.  We will then be populating a Map instance.  Let us start by creating a simple input file.

```
{ { 1 : 2 }, { 3 : 4 }, { 5 : 6 }, { 7 : 8 }, { 9 : 10 } }
```

The above input file is similar to the input file that was used to populate a vector with point instances.  While the above could of
been defined similar to point vector.  It was decided to use a python like dictionary definition syntax just to offer some format
variety for the input file.  The input will populate a map that uses integer key/value pairs.   Let us now create the reader for the
above input file.

```cpp
struct map_reader {
    std::istream& operator()(std::istream& in, std::map<int,int>& dict, int state ) {
        switch(state) {
            case 0:
            {
                std::map<int,int>::value_type value;

                dataLoader<
                    std::map<int,int>::value_type,
                    char,
                    value_type_reader,
                    2, // This is because we will populate two fields of the value_type
                    is_character<char,'{'>,
                    is_character<char,'}'>,
                    is_space,
                    is_space_or<':'>
                > loader(value);

                in >> loader;

                dict.insert(value);
            }
                break;
            default:
                throw std::runtime_error("Invalid state input");
        }

        return in;
    }
};
```

The above map_reader uses the value_type map definition as the value that is passed to the defined dataLoader template definition.
This operator uses a value_type_reader operator that is defined as.

```cpp
struct value_type_reader {
    std::istream& operator()(std::istream& in, std::map<int,int>::value_type& value, int state) {
        switch(state) {
            case 0:
                in >> value.first;
                break;
            case 1:
                in >> value.second;
                break;
            default:
                throw std::runtime_error("Invalid state value");
        }

        return in;
    }
}
```

Now that we've defined the map_reader and value_type_reader.  We can now create the dataLoader template definition that will process the above input file.

```cpp
void load(std::istream& in) {
    std::map<int,int> dict;

    dataLoader<
        std::map<int,int>,
        char,
        map_reader,
        1,
        is_character<char,'{'>,
        is_character<char,'}'>,
        is_space,
        is_space_or<','>
    > loader(dict);

    in >> loader;
}
```

The above dataLoader template definition when executed will populate the passed dict value with the entries that were stored within the above input file.
As can be seen, this definition allows the developer to focus on the reading of the particular value data and not have to be concerned with parsing the
input stream.  This is all done by the dataLoader template class.

Thus we conclude the different examples that shows one how the dataLoader template class was used to load different types of instances.  Again, the
objective of the dataLoader template class was to extract the need for a developer to worry about parsing the data but be able to focus on processing
the expected data.

# Conclusion

We've seen the evolution of the five versions of the dataLoader implementation above which included the reasons from moving from one version to another.
The above might not be the final version of these dataLoader template class implementations.  They will continue to evolve and currently they are being
copied over into its own branch so that others besides myself can import them into their projects.  They are not relegated to being used in a testing
environment but can also be embedded within a product.

While the above has provided some input into how the dataLoader template class has evolved.  What it doesn't mention is that this will be moved into its
own repository/branch such that others can take advantage of these implementations within their own projects.

Hopefully the above description can be of use to others and thanks tagging along.
