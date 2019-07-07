#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include <iostream>
#include "mat.h"
#include "matOperations.h"

using namespace std;
using ::testing::Return;
using ::testing::_; // Matcher for parameters


TEST(matTest, Fill) {



    EXPECT_CALL(A, t())
        .Times(2)


    ASSERT_TRUE(A.compare(B));
}

/** \brief Main test entrance point.
 * \param[in] argc
 * \param[in] argv
 */
int main(int argc, char** argv) {
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
