#include <iostream>
#include <set>
#include <array>

#include "gtest/gtest.h"

using namespace std;

template<typename E>
class wrapper {
    E m_value;
public:
    wrapper(E& value) : m_value(value) {}
    const E& operator()() const { return m_value; }
    bool operator<(const wrapper<E>& other) const { return this->m_value < other.m_value; }
    // why doesn't this operator method work since it is similar to the one defined later?
    ostream& operator<<(ostream& os) const { os << m_value; return os; }
    bool operator==(const wrapper<E>& other) const { return this->m_value == other.m_value; }
};

/*
template<typename E>
bool operator<(const E& lhs, const E& rhs) {
    return lhs() < rhs();
}
*/

template<typename E>
ostream& operator<<(ostream& os, const wrapper<E>& value) {
    os << value();
    return os;
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);

    set<wrapper<int>> values;
    for(int cnt = 1 ; cnt < 11 ; cnt++)
        values.insert(wrapper<int>(cnt));
    cout << "Values contains " << values.size() << " entries." << endl;
    for(int cnt = 1 ; cnt < 21 ; cnt++)
        values.insert(wrapper<int>(cnt));
    cout << "Values contains " << values.size() << " entries." << endl;

    for(auto value = values.begin() ; value != values.end() ; value++) {
        cout << "Value: " << (*value)() << endl;
    }

    while(argc-- > 0) {
        cout << "Argc: " << argc << " == " << argv[argc] << endl;
    }

    int i = 1;
    int j = 2;
    int k = 3;

    array<wrapper<int>, 3> ints = {wrapper<int>(i), wrapper<int>(j), wrapper<int>(k)};

    cout << "Is " << ints[1] << " < " <<  ints[2] << " ==> " << (ints[1] < ints[2]) << endl;
    cout << "Is " << ints[1] << " < " <<  ints[0] << " ==> " << (ints[1] < ints[0]) << endl;
    cout << "Is " << ints[1] << " == " <<  ints[2] << " ==> " << (ints[1] == ints[2]) << endl;
    cout << "Is " << ints[1] << " == " <<  ints[1] << " ==> " << (ints[1] == ints[1]) << endl;

    wrapper<int> a(i), b(j);

    cout << "Is " << a << " less than " <<  b << " ==> " << (a < b) << endl;

    return RUN_ALL_TESTS();
}