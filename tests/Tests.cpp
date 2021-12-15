//
// Created by majoor@INTRANET.EPFL.CH on 13.12.21.
//

#include <cmath>
#include "../googletest/googletest/googletest/include/gtest/gtest.h"
#include "../googletest/googletest/googletest/include/gtest/gtest-death-test.h"
#include "../test_googletest.h"
#include "../TxtReader.cpp"
#include "../MidpointFormula.h"
#include "../DataStruct.h"
#include "../AbstractIntegrationMethod.h"

TEST(sqrt, integer) { EXPECT_EQ(2, std::sqrt(4)); }

TEST(reader, first_test) { ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_D.txt").OutputData(), "Assertion `D>0' failed");}

TEST(integration, first_test) {
    Eigen::MatrixX2d boundsX(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(2,2); //X rows, 2 columns and ints
    Eigen::MatrixXcd coefficients(2,3); //X rows, 2 columns and ints
    boundsX(0,0) = 1;
    boundsX(0,1) = 2;
    boundsX(1,0) = 6;
    boundsX(1,1) = 7;
    boundsY(0,0) = 5;
    boundsY(0,1) = 6;
    boundsY(1,0) = 8;
    boundsY(1,1) = 9.5;
    noSteps(0,0) = 10;
    noSteps(0,1) = 10;
    noSteps(1,0) = 10;
    noSteps(1,1) = 10;
    coefficients(0,0) = std::complex<double>(1,1);
    coefficients(0,1) = std::complex<double>(15,-5);
    coefficients(0,2) = std::complex<double>(-2,11);
    coefficients(1,0) = std::complex<double>(5,-6);
    coefficients(1,1) = std::complex<double>(10,1);
    coefficients(1,2) = std::complex<double>(0,0);
    Data data = {.boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficients, .D=2, .m=2};
    EXPECT_EQ(data.D, 2);
    EXPECT_EQ(data.m, 2);

}

TEST(integration, second_test){
    Eigen::MatrixX2d boundsX(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2d boundsY(2,2); //X rows, 2 columns and doubles
    Eigen::MatrixX2i noSteps(2,2); //X rows, 2 columns and ints
    Eigen::MatrixXcd coefficients(2,3); //X rows, 2 columns and ints
    boundsX(0,0) = 1;
    boundsX(0,1) = 2;
    boundsX(1,0) = 6;
    boundsX(1,1) = 7;
    boundsY(0,0) = 5;
    boundsY(0,1) = 6;
    boundsY(1,0) = 8;
    boundsY(1,1) = 9.5;
    noSteps(0,0) = 10;
    noSteps(0,1) = 10;
    noSteps(1,0) = 10;
    noSteps(1,1) = 10;
    coefficients(0,0) = std::complex<double>(1,1);
    coefficients(0,1) = std::complex<double>(15,-5);
    coefficients(0,2) = std::complex<double>(-2,11);
    coefficients(1,0) = std::complex<double>(5,-6);
    coefficients(1,1) = std::complex<double>(10,1);
    coefficients(1,2) = std::complex<double>(0,0);
    Data data = {.boundsX = boundsX, .boundsY = boundsY, .noSteps = noSteps, .coefficients=coefficients, .D=2, .m=2};
    Eigen::MatrixX2i testSteps(2,2);
    testSteps(0,0) = 10;
    testSteps(0,1) = 10;
    testSteps(1,0) = 10;
    testSteps(1,1) = 10;
    EXPECT_EQ(data.noSteps, testSteps);
}