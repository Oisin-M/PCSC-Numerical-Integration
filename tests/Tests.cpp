//
// Created by majoor@INTRANET.EPFL.CH on 13.12.21.
//

#include <cmath>
#include "../googletest/googletest/googletest/include/gtest/gtest.h"
#include "../googletest/googletest/googletest/include/gtest/gtest-death-test.h"
#include "../TxtReader.cpp"
#include "../MidpointFormula.h"
#include "../TrapezoidalRule.h"
#include "../SimpsonsRule.h"
#include "../DataStruct.h"
#include "../AbstractIntegrationMethod.h"


Eigen::VectorXcd func(double x, double y, Eigen::MatrixXcd &coeff) {
    int r = coeff.rows();
    int c = coeff.cols();

    Eigen::VectorXd XandY (c);
    XandY(0) = 1;
    for (int i = 0; i < c - 1; i++){
        int power = ceil((i + 0.5) / 2); // gives 1, 1, 2, 2, 3, 3, ...
        if (i % 2 == 0){
            XandY(i + 1) = pow(x, power);
        }
        else {
            XandY(i + 1) = pow(y, power);
        }
    }
    Eigen::VectorXcd output (r);
    output = coeff * XandY;
    return output;
}

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

TEST(midpoint, integrate){
    std::string filename = "../tests/midpt_readfile.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    MidpointFormula midpt = MidpointFormula(data, &func);
    auto midpt_out = midpt.Solve();
    std::cout << data.coefficients << std::endl << std::endl << std::endl;
    std::cout << midpt_out << std::endl;
}

TEST(integrate, constant){
    std::string filename = "../tests/int_constant.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(2,4);
    expected(1) = std::complex<double>(-2,8);

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(trap_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(trap_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));
}

TEST(integrate, rank3) {
    std::string filename = "../tests/int_rank3.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(60,-32);
    expected(1) = std::complex<double>(28,-50);

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));

    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(trap_out(1))+0.1 && std::real(expected(1)) >= std::real(trap_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(trap_out(1))+0.1 && std::imag(expected(1)) >= std::imag(trap_out(1))-0.1);}