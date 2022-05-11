
#include "gtest/gtest.h"

#include "heap.h"

namespace valhalla {
    namespace heaps {
        TEST(Heap_Test_Suite, Heap_Test) {
            heap<int> h;

            h.add(10);

            h.add(6);
            h.add(7);
            h.add(14);
            h.add(1);
            h.add(3);

            ASSERT_TRUE(h.contains(14)) << "The value of 14 was not found in the heap";

            ASSERT_FALSE(h.contains(2)) << "The value of 2 was not supposed to be found in the heap";

            ASSERT_FALSE(h.remove(9)) << "It removed a non-existent entry";

            ASSERT_TRUE(h.remove(6)) << "It didn't remove an existing entry";

            // auto itr = h.begin();

        }
    }
}
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}