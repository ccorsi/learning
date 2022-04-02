#include <iostream>

#include "gtest/gtest.h"

#include "graph.h"
#include "dfs.h"
#include "city.h"

#include "test.h"

using namespace std;

namespace search {
    namespace uninformed {
        class dfsTest : public ::testing::Test {
            void print(char* message) {
                cout << "Calling dfsTest " << message << endl;
            }

        protected:
            dfsTest() {
                print("dfsTest ctor");
            }

            ~dfsTest() override {
                print("dfsTest dtor");
            }

            void SetUp() override {
                print("SetUp");
            }

            void TearDown() override {
                print("TearDown");
            }

            int value() const { return 13; }

            void runTest() {

            }
        };

        TEST(DepthFirstSearchTestSuite, DepthFirstSearchTest) {
            // This type of test just associates the DepthFirstSearchTest test to the DepthFirstSearchTestSuite test suite
            // I just add whatever tests within this block and it will be associated to the DepthFirstSearchTest test.
            cout << "Hello, World!" << endl;
        }

        TEST_F(dfsTest, DepthFirstSearchTestMe) {
            cout << "Inside the DepthFirstSearchTestMe Test" << endl;
            cout << "Value: " << value() << endl;
        }

        class data {
        private:
            string m_name;
        public:
            data() {}
            data(const data& other) : m_name(other.m_name) {}
            data(string& name) : m_name(name) {}
            ostream& operator<<(ostream& os) {
                os << m_name;
                return os;
            }
        };

        class dfsTestParam :
            public testing::TestWithParam<const data> {

        };

        // TEST_P(dfsTestParam, DepthFirstSearchWithParamsTest) {
        //     const data d = GetParam();

        // }

    };
};

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
} 