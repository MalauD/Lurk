#include "gtest/gtest.h"
#define TESTING

#ifdef TESTING
#include "Test/main_test.hpp"
#endif

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}