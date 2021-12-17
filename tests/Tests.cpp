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

// Initialize the readers we use for solving with the different methods
TxtReader reader_constant = TxtReader("../tests/int_constant.txt");
Data data_constant = reader_constant.OutputData();

TxtReader reader_rank3 = TxtReader("../tests/int_rank3.txt");
Data data_rank3 = reader_rank3.OutputData();

TxtReader reader_rank6 = TxtReader("../tests/int_rank6.txt");
Data data_rank6 = reader_rank6.OutputData();

TxtReader reader_rank9 = TxtReader("../tests/int_rank9.txt");
Data data_rank9 = reader_rank9.OutputData();


TEST(reader, death_tests) {
    std::cout << std::endl << "---------- READER TESTS ----------" << std::endl << std::endl;
    ASSERT_DEATH (auto data = TxtReader("../tests/non_existing_file.txt").OutputData(), "Failed to open");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_D.txt").OutputData(), "Assertion `D>0' failed");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_m.txt").OutputData(), "Assertion `m>0' failed");
    ASSERT_DEATH (auto data = TxtReader("../tests/readfile_fail_l.txt").OutputData(), "Assertion `l>0' failed");
}

TEST(IntegrationMidpoint, constant){

    auto mid_out = MidpointFormula(data_constant, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(2,4);
    expected(1) = std::complex<double>(-2,8);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));
}

TEST(IntegrationTrapezoidal, constant){

    auto trap_out = TrapezoidalRule(data_constant, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(2,4);
    expected(1) = std::complex<double>(-2,8);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(trap_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(trap_out(1)));
}

TEST(IntegrationSimpson, constant){

    auto simp_out = SimpsonsRule(data_constant, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(2,4);
    expected(1) = std::complex<double>(-2,8);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));
}

TEST(IntegrationMidpoint, rank3){

    auto mid_out = MidpointFormula(data_rank3, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(60,-32);
    expected(1) = std::complex<double>(28,-50);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(mid_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(mid_out(1)));
}

TEST(IntegrationTrapezoidal, rank3){

    auto trap_out = TrapezoidalRule(data_rank3, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(60,-32);
    expected(1) = std::complex<double>(28,-50);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(trap_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(trap_out(1)));
}

TEST(IntegrationSimpson, rank3){

    auto simp_out = SimpsonsRule(data_rank3, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(60,-32);
    expected(1) = std::complex<double>(28,-50);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));
}

TEST(IntegrationMidpoint, rank6){

    auto mid_out = MidpointFormula(data_rank6, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(7.75,7.75);
    expected(1) = std::complex<double>(7.75,7.75);

    // The method is approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(mid_out(0))+0.1 && std::real(expected(0)) >= std::real(mid_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(mid_out(0))+0.1 && std::imag(expected(0)) >= std::imag(mid_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(mid_out(1))+0.1 && std::real(expected(1)) >= std::real(mid_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(mid_out(1))+0.1 && std::imag(expected(1)) >= std::imag(mid_out(1))-0.1);
}

TEST(IntegrationTrapezoidal, rank6){

    auto trap_out = TrapezoidalRule(data_rank6, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(7.75,7.75);
    expected(1) = std::complex<double>(7.75,7.75);

    // The method is approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);
    EXPECT_TRUE(std::real(expected(1)) <= std::real(trap_out(1))+0.1 && std::real(expected(1)) >= std::real(trap_out(1))-0.1);
    EXPECT_TRUE(std::imag(expected(1)) <= std::imag(trap_out(1))+0.1 && std::imag(expected(1)) >= std::imag(trap_out(1))-0.1);
}

TEST(IntegrationSimpson, rank6){

    auto simp_out = SimpsonsRule(data_rank6, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (2);
    expected(0) = std::complex<double>(7.75,7.75);
    expected(1) = std::complex<double>(7.75,7.75);

    // The method is exact
    EXPECT_FLOAT_EQ(std::norm(expected(0)), std::norm(simp_out(0)));
    EXPECT_FLOAT_EQ(std::norm(expected(1)), std::norm(simp_out(1)));
}

TEST(IntegrationMidpoint, rank9){

    auto mid_out = MidpointFormula(data_rank9, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (1);
    double real = 977.0/60.0;
    double imag = -464.0/60.0;
    expected(0) = std::complex<double>(real,imag);

    // The method is approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(mid_out(0))+0.1 && std::real(expected(0)) >= std::real(mid_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(mid_out(0))+0.1 && std::imag(expected(0)) >= std::imag(mid_out(0))-0.1);
}

TEST(IntegrationTrapezoidal, rank9){

    auto trap_out = TrapezoidalRule(data_rank9, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (1);
    double real = 977.0/60.0;
    double imag = -464.0/60.0;
    expected(0) = std::complex<double>(real,imag);

    // The method is approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(trap_out(0))+0.1 && std::real(expected(0)) >= std::real(trap_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(trap_out(0))+0.1 && std::imag(expected(0)) >= std::imag(trap_out(0))-0.1);
}

TEST(IntegrationSimpson, rank9){

    auto simp_out = SimpsonsRule(data_rank9, &func).Solve();

    // Expected result
    Eigen::VectorXcd expected (1);
    double real = 977.0/60.0;
    double imag = -464.0/60.0;
    expected(0) = std::complex<double>(real,imag);

    // The method is approximate
    EXPECT_TRUE(std::real(expected(0)) <= std::real(simp_out(0))+0.1 && std::real(expected(0)) >= std::real(simp_out(0))-0.1);
    EXPECT_TRUE(std::imag(expected(0)) <= std::imag(simp_out(0))+0.1 && std::imag(expected(0)) >= std::imag(simp_out(0))-0.1);

}
