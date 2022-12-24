#include <iostream>

#include "resources.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace std;

namespace valhalla {
    namespace util
    {
        TEST(MEMORY_TESTS, SIMPLE_MEMORY_TEST) {
            memory m;
            // bool exhausted = m(1);
            // cout << "Memory has reached 50% is " << exhausted << endl;

            for( int percentage = 1 ; percentage < 101 ; percentage += 10) {
                bool result = m(percentage);
                cout << "Total memory reached " << percentage << "% is " << ( result ? "yes" : "no" ) << endl;
            }

            memory::mem_size_type total = m(memory::mem_type::TOTAL);
            memory::mem_size_type system = m(memory::mem_type::SYSTEM);
            memory::mem_size_type process = m(memory::mem_type::PROCESS);

            cout << "Total memory is " << total << endl;
            cout << "System memory is " << system << endl;
            cout << "Process memory is " << process << endl;
        }        
    } // namespace util
    
} // namespace valhalla

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
 