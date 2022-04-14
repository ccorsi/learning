/**
 * @file oprtests.cpp
 * @author Claudio Corsi (clcorsi@yahoo.com)
 * @brief These are going to be a set of different tests that will just provide a means to
 *  learn and practice to implement the different types of operators that can be implemented
 *  within a class/struct object in C++.
 *
 * @version 0.1
 * @date 2022-04-14
 *
 * @copyright Copyright (c) 2022 Claudio Corsi
 *
 * @license MIT License https://raw.githubusercontent.com/ccorsi/learning/main/LICENSE
 */

// standard include libraries
#include <string>

// third party include libraries
#include "gtest/gtest.h"

// inter-project include libraries
#include "macros.h"

// project includes

using namespace std;

/**
 * @brief This is the class that will be used to implement the different set of operators
 *  that can be implemented.
 *
 */
class operator_object {
    string m_name;

public:
    // constructors
    operator_object(const string& name) : m_name(name) {}
    operator_object(string& name) : m_name(name) {}

    // ====================================================================================
    // user defined class operators
    // ====================================================================================

    // ====================================================================================
    // boolean operators
    // ====================================================================================
    inline bool operator==(const operator_object& other) { return m_name == other.m_name; }

    inline bool operator<(const operator_object& other) { return m_name < other.m_name; }

    inline bool operator>(const operator_object& other) { return m_name > other.m_name; }

    // ====================================================================================
    // assignment operators
    // ====================================================================================

    operator_object& operator=(const operator_object& other) {
        if (this != &other) {
            m_name = other.m_name;
        }

        return *this;
    }

    operator_object& operator=(const string& name) {
        m_name = name;
        return *this;
    }

    // ====================================================================================
    // access operators
    // ====================================================================================

    inline const string& operator()() const { return m_name; }

    inline operator_object& operator()() { return *this; }

    inline operator_object& operator()(const string& name) {
        m_name = name;
        return *this;
    }

    // ====================================================================================
    // stream operators
    // ====================================================================================

    inline istream& operator>>(istream& is) {
        is >> m_name;
        return is;
    }

    inline ostream& operator<<(ostream& os) {
        os << "operator_object [ m_name = " << m_name << " ]";
        return os;
    }

    // ====================================================================================
    // other operators
    // ====================================================================================

    inline void operator+(string& append)     { m_name += append; }
    inline void operator+(const char* append) { m_name += append; }
    inline void operator+(const char append)  { m_name += append; }
};

TEST(OperatorTestSuite, EqualOperatorTest) {
    operator_object lhs("Joe"), rhs("Joe");

    ASSERT_TRUE(lhs == rhs);

}

TEST(OperatorTestSuite, NotEqualOperatorTest) {
    operator_object lhs("Joe"), rhs("Ben");

    ASSERT_FALSE(lhs == rhs);

}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}