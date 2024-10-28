#include <complex>
#include <iostream>

#include "Matrix/matrix.h"

int main() {
    Matrix<int> m1(2, 2, 1);
    std::cout << m1;
    std::cout << m1.rows() << " " << m1.cols() << " " << m1.size() << "\n\n";

    Matrix<float> m2(3, 2, (float)-13.5, (float)9.7);
    std::cout << m2;
    std::cout << m2.rows() << " " << m2.cols() << " " << m2.size() << "\n\n";

    Matrix<int> m3(m1);
    std::cout << m3;
    std::cout << m3.rows() << " " << m3.cols() << " " << m3.size() << "\n\n";

    Matrix<float> m4 = m2;
    std::cout << m4;
    std::cout << m4.rows() << " " << m4.cols() << " " << m4.size() << "\n\n";

    Matrix<double> m5(4, 5, (double)-2.4, (double)25.6);
    std::cout << m5;
    std::cout << m5(3, 4) << "\n";
    std::cout << m5.rows() << " " << m5.cols() << " " << m5.size() << "\n\n";

    Matrix<std::complex<float>> m6(4, 5, std::complex<float>(-2.4f, 5.4f), std::complex<float>(25.6f, -4.7f));
    std::cout << m6;
    std::cout << m6(2, 0) << "\n";
    std::cout << m6.rows() << " " << m6.cols() << " " << m6.size() << "\n\n";
    
    return 0;
}