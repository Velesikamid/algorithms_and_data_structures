#include <complex>
#include <iostream>

#include "Matrix/matrix.h"

int main() {
    Matrix<int> m1(2, 2, 1);
    std::cout << m1;
    std::cout << m1.rows() << " " << m1.cols() << " " << m1.size() << "\n";
    m1(0, 0) = 5;
    std::cout << m1 << "\n";

    Matrix<float> m2(3, 2, (float)-13.5, (float)9.7);
    std::cout << m2;
    std::cout << m2.rows() << " " << m2.cols() << " " << m2.size() << "\n";
    m2(2, 1) = 3.5;
    std::cout << m2 << "\n";

    Matrix<int> m3(m1);
    std::cout << m3;
    std::cout << m3.rows() << " " << m3.cols() << " " << m3.size() << "\n";
    m3(0, 0) = 10;
    std::cout << m3 << "\n" << m1 << "\n";

    Matrix<float> m4 = m2;
    std::cout << m4;
    std::cout << m4.rows() << " " << m4.cols() << " " << m4.size() << "\n";
    m4(2, 1) = -1.0;
    std::cout << m4 << "\n" << m2 << "\n";

    Matrix<double> m5(4, 5, (double)-2.4, (double)25.6);
    std::cout << m5;
    std::cout << m5(3, 4) << "\n";
    std::cout << m5.rows() << " " << m5.cols() << " " << m5.size() << "\n";
    m5(0, 0) = 12.25;
    std::cout << m5 << "\n";

    Matrix<std::complex<float>> m6(2, 2, std::complex<float>(-2.4f, -5.4f), std::complex<float>(25.6f, 4.7f));
    std::cout << m6;
    std::cout << m6(0, 0) << "\n";
    std::cout << m6.rows() << " " << m6.cols() << " " << m6.size() << "\n";
    m6(0, 0) = std::complex<float>(1.5f, 2.5f);
    std::cout << m6 << "\n";

    Matrix<int> m7 = m1 + m3;
    std::cout << m7;
    std::cout << m7.rows() << " " << m7.cols() << " " << m7.size() << "\n\n";

    Matrix<float> m8 = m2 - m4;
    std::cout << m8;
    std::cout << m8.rows() << " " << m8.cols() << " " << m8.size() << "\n\n";

    Matrix<std::complex<float>> m9(2, 1, std::complex<float>(-2.4f, -5.4f), std::complex<float>(25.6f, 4.7f));
    std::cout << m9 << "\n";
    
    Matrix<std::complex<float>> m10 = m6 * m9;
    std::cout << m10 << "\n";

    std::cout << m5 << "\n";
    Matrix<double> m11 = m5 * 2;
    std::cout << m11 << "\n";

    std::cout << m5 << "\n";
    Matrix<double> m12 = 0.5 * m5;
    std::cout << m12 << "\n";

    std::cout << m6 << "\n";
    Matrix<std::complex<float>> m13 = m6 / 2;
    std::cout << m13 << "\n";

    Matrix<int> m14(2, 2);
    m14(0, 0) = 1;
    m14(0, 1) = 2;
    m14(1, 0) = 3;
    m14(1, 1) = 4;
    std::cout << m14;
    std::cout << m14.trace() << "\n\n";

    std::cout << m1 << "\n" << m3;
    std::cout << (m1 == m3) << "\n";
    std::cout << (m1 != m3) << "\n\n";

    std::cout << m4;
    std::cout << (m4 == m4) << "\n";
    std::cout << (m4 != m4) << "\n\n";

    gauss(m14);
    std::cout << m14;
    
    return 0;
}