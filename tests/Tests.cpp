//
// Created by majoor@INTRANET.EPFL.CH on 13.12.21.
//

#include <cmath>
#include "../googletest/googletest/googletest/include/gtest/gtest.h"
#include "../TxtReader.cpp"
#include "../MidpointFormula.h"
#include "../TrapezoidalRule.h"
#include "../SimpsonsRule.h"


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

TEST(reader, death_tests) {
    std::cout << std::endl << "---------- READER TESTS ----------" << std::endl << std::endl;
    ASSERT_DEATH (auto data = TxtReader("../tests/non_existing_file.txt").OutputData(), "Failed to open");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_D.txt").OutputData(), "Assertion `D>0' failed");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_m.txt").OutputData(), "Assertion `m>0' failed");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_l.txt").OutputData(), "Assertion `l>0' failed");
}


TEST(integrate, constant){

    // Open file and solve for each method
    std::cout << "---------- INTEGRATION TESTS ----------" << std::endl << std::endl;
    std::string filename = "../tests/int_constant.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(2,4);
    expected(1) = std::complex<double>(-2,8);

    // All 3 methods are exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(trap_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(trap_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));
}


TEST(integrate, rank3) {

    // Open file and solve for each method
    std::string filename = "../tests/int_rank3.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(60,-32);
    expected(1) = std::complex<double>(28,-50);

    // Simpson and midpoint are exact, trapezoidal is approximate
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));

    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(trap_out(1))+0.1 && std::real(expected(1)) >= std::real(trap_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(trap_out(1))+0.1 && std::imag(expected(1)) >= std::imag(trap_out(1))-0.1);
}


TEST(integrate, rank6) {

    // Open file and solve for each method
    std::string filename = "../tests/int_rank6.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(7.75,7.75);
    expected(1) = std::complex<double>(7.75,7.75);

    // Simpson is exact, midpoint and trapezoidal are approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(mid_out(0))+0.1 && std::real(expected(0)) >= std::real(mid_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(mid_out(0))+0.1 && std::imag(expected(0)) >= std::imag(mid_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(mid_out(1))+0.1 && std::real(expected(1)) >= std::real(mid_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(mid_out(1))+0.1 && std::imag(expected(1)) >= std::imag(mid_out(1))-0.1);

    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));

    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(trap_out(1))+0.1 && std::real(expected(1)) >= std::real(trap_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(trap_out(1))+0.1 && std::imag(expected(1)) >= std::imag(trap_out(1))-0.1);
}


TEST(integrate, rank9) {

    // Open file and solve for each method
    std::string filename = "../tests/int_rank9.txt";
    TxtReader reader = TxtReader(filename);
    Data data = reader.OutputData();
    auto mid_out = MidpointFormula(data, &func).Solve();
    auto trap_out = TrapezoidalRule(data, &func).Solve();
    auto simp_out = SimpsonsRule(data, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (1);
    double real = 977.0/60.0;
    double imag = -464.0/60.0;
    expected(0) = std::complex<double>(real,imag);

    // All 3 methods are approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(mid_out(0))+0.1 && std::real(expected(0)) >= std::real(mid_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(mid_out(0))+0.1 && std::imag(expected(0)) >= std::imag(mid_out(0))-0.1);

    EXPECT_TRUE(std::real(expected(0)) <= std::real(simp_out(0))+0.1 && std::real(expected(0)) >= std::real(simp_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(simp_out(0))+0.1 && std::imag(expected(0)) >= std::imag(simp_out(0))-0.1);

    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);

    std::cout << std::endl << "---------- END OF TESTS ----------" << std::endl << std::endl;
}