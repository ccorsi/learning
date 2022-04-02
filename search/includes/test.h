#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <string>

class test {
private:
    std::string m_name;
    class test_info {
    private:
        std::string& name;
    public:
        test_info(std::string n) : name(n) { std::cout << "Executing test: " << name << std::endl; }
        ~test_info() { std::cout << "Completed executing test: " << name << std::endl; }
    };

protected:
    virtual bool _run() = 0;

public:
    virtual bool operator()() = 0;
    bool run() {
        test_info info(m_name);
        return this->operator()();
    };
};

#endif
