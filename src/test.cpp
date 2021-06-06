#include <iostream>

//#define MATRIX_DEBUGGING
//#define VECTOR_DEBUGGING

#include "Matrix.h"
#include "Vector.h"

#include "Eigen/Dense"
#include "Eigen/Core"

using namespace Eigen;

void test_1() {
    atlatec::Matrix<int> P(3, 3);
    P(0, 0) = 1;
    P(0, 1) = 2;
    P(0, 2) = 3;
    P(1, 0) = 1;
    P(1, 1) = 2;
    P(1, 2) = 3;
    P(2, 0) = 1;
    P(2, 1) = 2;
    P(2, 2) = 3;

    atlatec::Vector<int> x(3);
    x(0) = 1;
    x(1) = 1;
    x(2) = 1;

    atlatec::Matrix<int> F(3, 3);
    F(0, 0) = 1;
    F(0, 1) = 0;
    F(0, 2) = 1;
    F(1, 0) = 0;
    F(1, 1) = 1;
    F(1, 2) = 0;
    F(2, 0) = 0;
    F(2, 1) = 0;
    F(2, 2) = 1;

    atlatec::Matrix<int> Q(3, 3);
    Q(0, 0) = 1;
    Q(0, 1) = 0;
    Q(0, 2) = 1;
    Q(1, 0) = 0;
    Q(1, 1) = 1;
    Q(1, 2) = 0;
    Q(2, 0) = 0;
    Q(2, 1) = 0;
    Q(2, 2) = 1;

    x = F * x;
    P = F * P + Q;

    x.show();
    P.show();
}

void test_eigen_1() {
    MatrixXd P = MatrixXd(3, 3);
    P << 1, 2, 3,
        1, 2, 3,
        1, 2, 3;
    VectorXd x = VectorXd(3);
    x << 1, 1, 1;

    MatrixXd F = MatrixXd(3, 3);
    F << 1, 0, 1,
        0, 1, 0,
        0, 0, 1;
    MatrixXd Q = MatrixXd(3, 3);
    Q << 1, 0, 1,
        0, 1, 0,
        0, 0, 1;

    x = F * x;
    P = F * P + Q;

    IOFormat OctaveFmt(StreamPrecision, 0, ", ", ";\n", "", "", "[", "]");
    std::cout << x.format(OctaveFmt) << std::endl;
    std::cout << P.format(OctaveFmt);

}

int main()
{
    // here just comparing result of our matrix/vector calculations with result of Eigen calculations
    // Basically, we can see that our developed matrix/vector operations work correctly

    try {
        std::cout << "**************************" << std::endl;
        std::cout << "*** Matrix and vector  ***" << std::endl;
        std::cout << "**************************" << std::endl;
        test_1();

        std::cout << "**************************" << std::endl;
        std::cout << "*** Eigen calculations ***" << std::endl;
        std::cout << "**************************" << std::endl;
        test_eigen_1();
    }
    catch (std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << std::endl;
    }

}
