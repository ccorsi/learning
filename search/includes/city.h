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
    // default constructor that could be used within a container
    city() {}
    // default copy constructor that could be used within a container
    city(const city& other) : m_name(other.m_name) {}
    // user defined constructor for a passed string reference
    city(std::string& name) : m_name(name) {}
    // user defined constructor for a passed char array
    city(const char* name) : m_name(name) {}
    // useful in cases in which objects process instances using this operator
    std::string& operator()() { return m_name; }
    // used to output to a stream information about this city
    std::ostream& operator<<(std::ostream& os) { os << m_name; return os; }
    // used to return a reference of this city name
    const std::string& name() const { return m_name; }
    // used to determine if two instances of city are the same
    bool operator==(const city& other) { return other.m_name == this->m_name; }
    // For some reason this does not work as expected.....still need to investigate why....
    bool operator<(const city& other) { return this->m_name < other.m_name; }
    // used to determine if two instances of city are not the same
    bool operator!=(const city& other) { return this->m_name != other.m_name; }
};

std::ostream& operator<<(std::ostream& os, city& c) {
    os << c();
    return os;
}

bool operator<(const city& lhs, const city& rhs) { return lhs.name() < rhs.name(); }

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
