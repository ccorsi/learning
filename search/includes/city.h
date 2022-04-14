#ifndef __CITY_H__
#define __CITY_H__

#include <string>
#include <ostream>

/**
 * @brief This is a simple city class that just references the name of the city.  
 * It contains the required methods that could be used by containers, streams and anyother classes.
 * 
 *
 */
class city {
    // the name of the city
    std::string m_name;
public:
    // =============
    // Constructors
    // =============

    // Default constructors

    // default constructor that could be used within a container
    city() = default;
    // default copy constructor that could be used within a container
    city(const city& other) { m_name = other.m_name; }
    // TODO: for some reason adding a default move ctor causes compiler errors that complain about the operator=!
    // default move constructor that could be used within a container
    // city(city&&) = default;

    // User defined constructors

    // user defined constructor for a passed string reference
    city(std::string& name) : m_name(name) {}
    // user defined constructor for a passed char array
    city(const char* name) : m_name(name) {}

    // ===========================
    // User defined class methods
    // ===========================

    // used to return a reference of this city name
    const std::string& name() const { return m_name; }

    // =========================================================================
    // Implementation of different operators that will be used within the tests.
    // =========================================================================

    // useful in cases in which objects process instances using this operator
    std::string& operator()() { return m_name; }
    // used to output to a stream information about this city
    std::ostream& operator<<(std::ostream& os) { os << m_name; return os; }

    // used to determine if two instances of city are the same
    bool operator==(const city& other) { return other.m_name == this->m_name; }
    // used to sort the city instances within containers that required this operator to be defined.
    bool operator<(const city& other) const { return this->m_name < other.m_name; }
    // used to sort the city instances within containers that require this operator to be defined.
    bool operator>(const city& other) const { return this->m_name > other.m_name; }
    // used to determine if two instances of city are not the same
    bool operator!=(const city& other) { return this->m_name != other.m_name; }
};

std::ostream& operator<<(std::ostream& os, city& c) {
    os << c();
    return os;
}

// FYI: this is not required any longer since the instance definition of this operator requires that
//      you add the const after the definition of the signature to signify that this method call be
//      called in cases that you expect a constant instance to be returned.
// bool operator<(const city& lhs, const city& rhs) { return lhs.name() < rhs.name(); }

// The following definition is used for newer versions of the compiler
/*
constexpr bool operator<(const city& lhs, const city& rhs) {
    return lhs.name() < rhs.name();
}
*/

/*
bool operator()(const city& lhs, const city& rhs) const {
    return lhs.name() < rhs.name();
}

constexpr bool operator()(const city& lhs, const city& rhs) const {
    return lhs.name() < rhs.name();
}
*/

#endif
