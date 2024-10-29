#include <complex>
#include <iostream>

#include "Matrix/matrix.h"

int main() {
    Matrix<int> m1(2, 2, 1);
    std::cout << "Matrix m1 initialized with 2x2 size, all elements set to 1:\n" << m1;
    std::cout << "m1 rows: " << m1.rows() << ", columns: " << m1.cols() << ", size: " << m1.size() << "\n";

    m1(0, 0) = 5;
    std::cout << "m1 after setting m1(0, 0) to 5:\n" << m1 << "\n";

    Matrix<float> m2(3, 2, -13.5f, 9.7f);
    std::cout << "Matrix m2 initialized with random float values between -13.5 and 9.7:\n" << m2;
    std::cout << "m2 rows: " << m2.rows() << ", columns: " << m2.cols() << ", size: " << m2.size() << "\n";

    m2(2, 1) = 3.5f;
    std::cout << "m2 after setting m2(2, 1) to 3.5:\n" << m2 << "\n";

    Matrix<int> m3(m1);
    std::cout << "Matrix m3, copy of m1:\n" << m3;
    m3(0, 0) = 10;
    std::cout << "m3 after setting m3(0, 0) to 10:\n" << m3 << "\nm1 remains unchanged:\n" << m1 << "\n";

    Matrix<float> m4 = m2;
    std::cout << "Matrix m4, copy of m2:\n" << m4;
    m4(2, 1) = -1.0f;
    std::cout << "m4 after setting m4(2, 1) to -1.0:\n" << m4 << "\nm2 remains unchanged:\n" << m2 << "\n";

    Matrix<double> m5(4, 5, -2.4, 25.6);
    std::cout << "Matrix m5 initialized with random double values between -2.4 and 25.6:\n" << m5;
    std::cout << "m5(3, 4): " << m5(3, 4) << "\n";
    std::cout << "m5 rows: " << m5.rows() << ", columns: " << m5.cols() << ", size: " << m5.size() << "\n";

    m5(0, 0) = 12.25;
    std::cout << "m5 after setting m5(0, 0) to 12.25:\n" << m5 << "\n";

    Matrix<std::complex<float>> m6(2, 2, std::complex<float>(-2.4f, -5.4f), std::complex<float>(25.6f, 4.7f));
    std::cout << "Complex matrix m6 initialized with random complex values between (-2.4, -5.4) and (25.6, 4.7):\n" << m6;
    std::cout << "m6(0, 0): " << m6(0, 0) << "\n\n";

    Matrix<int> m7 = m1 + m3;
    std::cout << "Matrix m7 = m1 + m3:\n" << m7;

    Matrix<float> m8 = m2 - m4;
    std::cout << "Matrix m8 = m2 - m4:\n" << m8;

    Matrix<double> m11 = m5 * 2;
    std::cout << "Matrix m11 = m5 * 2 (multiplication by scalar):\n" << m11;

    Matrix<double> m12 = 0.5 * m5;
    std::cout << "Matrix m12 = 0.5 * m5 (scalar multiplication from the left):\n" << m12;

    Matrix<std::complex<float>> m13 = m6 / 2.0f;
    std::cout << "Matrix m13 = m6 / 2:\n" << m13 << "\n";

    Matrix<int> m14(2, 2);
    m14(0, 0) = 1;
    m14(0, 1) = 2;
    m14(1, 0) = 3;
    m14(1, 1) = 4;
    std::cout << "Matrix m14:\n" << m14;
    std::cout << "Trace of m14: " << m14.trace() << "\n\n";

    std::cout << "m1 and m3 equality check:\n" << (m1 == m3) << " (0 means false, 1 means true)\n";
    std::cout << "m1 and m3 inequality check:\n" << (m1 != m3) << " (0 means false, 1 means true)\n\n";

    std::cout << "Matrix m1 before Gaussian elimination:\n" << m1;
    gauss(m1);
    std::cout << "Matrix m1 after Gaussian elimination:\n" << m1 << "\n";

    Matrix<double> m15(3, 3, -12.5, 12.5);
    std::cout << "Matrix m15 before Gaussian elimination:\n" << m15;
    gauss(m15);
    std::cout << "Matrix m15 after Gaussian elimination:\n" << m15 << "\n";

    return 0;
}
