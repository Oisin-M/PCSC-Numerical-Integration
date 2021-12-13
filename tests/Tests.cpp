//
// Created by majoor@INTRANET.EPFL.CH on 13.12.21.
//

#include <cmath>
#include "../googletest/googletest/googletest/include/gtest/gtest.h"
#include "../test_googletest.h"

TEST(sqrt, integer) { EXPECT_EQ(2, std::sqrt(4)); }

TEST(google_test, x_positive_y_positive) { EXPECT_EQ(5, test_function(2,1));}