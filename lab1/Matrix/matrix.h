#pragma once

#include <algorithm>
#include <complex>
#include <iomanip>
#include <iostream>
#include <random>
#include <stdexcept>

#include "../MyVector/my_vector.h"

template <class T>
class Matrix
{
private:
    size_t _rows, _cols;
    MyVector<T> _data;
    static constexpr double EPSILON = 1e-10;

public:
    static double epsilon()
    {
        return EPSILON;
    }

    size_t rows() const
    {
        return _rows;
    }

    size_t cols() const
    {
        return _cols;
    }

    size_t size() const
    {
        return rows() * cols();
    }

    const MyVector<T> &data() const
    {
        return _data;
    }

    Matrix(size_t rows, size_t cols, const T &initial_value = T())
        : _rows(rows), _cols(cols), _data(size(), initial_value) {}

    Matrix(size_t rows, size_t cols, const T &min_value, const T &max_value)
        : _rows(rows), _cols(cols), _data(size())
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<T> dis(min_value, max_value);

        for (size_t i = 0; i < size(); ++i)
        {
            _data.push_back(dis(gen));
        }
    }

    Matrix(const Matrix &other) : _rows(other._rows), _cols(other._cols), _data(other._data) {}

    Matrix &operator=(const Matrix &other)
    {
        if (this == &other)
        {
            return *this;
        }

        (*this)(other);
        return *this;
    }

    T &operator()(size_t row, size_t col)
    {
        if (row >= _rows || col >= _cols)
        {
            throw std::out_of_range("Index out of range!");
        }

        return _data[row * _cols + col];
    }

    const T &operator()(size_t row, size_t col) const
    {
        if (row >= _rows || col >= _cols)
        {
            throw std::out_of_range("Index out of range!");
        }

        return _data[row * _cols + col];
    }

    Matrix operator+(const Matrix &other) const
    {
        if (_rows != other._rows || _cols != other._cols)
        {
            throw std::invalid_argument("Matrix dimensions must match for addition!");
        }

        Matrix result(_rows, _cols);
        for (size_t i = 0; i < size(); ++i)
        {
            result._data[i] = _data[i] + other._data[i];
        }

        return result;
    }

    Matrix operator-(const Matrix& other) const
    {
        if (_rows != other._rows || _cols != other._cols)
        {
            throw std::invalid_argument("Matrix dimensions must match for subtraction!");
        }

        Matrix result(_rows, _cols);
        for (size_t i = 0; i < size(); ++i)
        {
            result._data[i] = _data[i] - other._data[i];
        }
        
        return result;
    }

    Matrix operator*(const Matrix& other) const
    {
        if (_cols != other._rows)
        {
            throw std::invalid_argument("Invalid matrix dimensions for multiplication!");
        }

        Matrix result(_rows, other._cols);
        for (size_t i = 0; i < _rows; ++i)
        {
            for (size_t j = 0; j < other._cols; ++j)
            {
                result(i, j) = T();
                for (size_t k = 0; k < _cols; ++k)
                {
                    result(i, j) += (*this)(i, k) * other(k, j);
                }
            }
        }
        return result;
    }

    Matrix operator*(const T& scalar) const
    {
        Matrix result(_rows, _cols);
        for (size_t i = 0; i < size(); ++i)
        {
            result._data[i] = _data[i] * scalar;
        }

        return result;
    }

    friend Matrix operator*(const T& scalar, const Matrix& matrix)
    {
        return matrix * scalar;
    }

    Matrix operator/(const T& scalar) const
    {
        Matrix result(_rows, _cols);
        for (size_t i = 0; i < size(); ++i)
        {
            result._data[i] = _data[i] / scalar;
        }

        return result;
    }

    T trace() const
    {
        if (_rows != _cols)
        {
            throw std::invalid_argument("Trace is defined only for square matrices!");
        }

        T result = T();
        for (size_t i = 0; i < _rows; ++i)
        {
            result += (*this)(i, i);
        }

        return result;
    }

    bool operator==(const Matrix& other) const
    {
        if (_rows != other._rows || _cols != other._cols)
        {
            return false;
        }
        
        for (size_t i = 0; i < size(); ++i)
        {
            if (std::abs(_data[i] - other._data[i]) > EPSILON)
            {
                return false;
            }
        }
        return true;
    }

    bool operator!=(const Matrix& other) const
    {
        return !(*this == other);
    }

    friend std::ostream &operator<<(std::ostream &stream, const Matrix &matrix)
    {
        for (size_t i = 0; i < matrix._rows; ++i)
        {
            stream << "||";
            for (size_t j = 0; j < matrix._cols; ++j)
            {
                stream << std::setw(20) << std::setprecision(4) << matrix(i, j);
                if (j == matrix._cols - 1)
                    stream << "||\n";
            }
        }
        return stream;
    }
};

template<>
Matrix<std::complex<float>>::Matrix(size_t rows, size_t cols, const std::complex<float> &min_value, const std::complex<float> &max_value)
    : _rows(rows), _cols(cols), _data(size())
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_real(min_value.real(), max_value.real());
    std::uniform_real_distribution<> dis_imag(min_value.imag(), max_value.imag());

    for (size_t i = 0; i < size(); ++i)
    {
        _data.push_back(std::complex<float>((float)dis_real(gen), (float)dis_imag(gen)));
    }
}
    
template<>
Matrix<std::complex<double>>::Matrix(size_t rows, size_t cols, const std::complex<double> &min_value, const std::complex<double> &max_value)
    : _rows(rows), _cols(cols), _data(size())
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis_real(min_value.real(), max_value.real());
    std::uniform_real_distribution<> dis_imag(min_value.imag(), max_value.imag());

    for (size_t i = 0; i < size(); ++i)
    {
        _data.push_back(std::complex<double>(dis_real(gen), dis_imag(gen)));
    }
}

template<class T>
void gauss(Matrix<T>& matrix)
{
    if (matrix.rows() != matrix.cols())
    {
        throw std::invalid_argument("Only square matrices are reduced to a triangular form!");
    }

    size_t n = matrix.rows();
    for (size_t i = n; i > 0; --i)
    {
        size_t row = i - 1;

        if (std::abs(matrix(row, row)) < Matrix<T>::epsilon())
        {
            bool swapped = false;
            for (size_t j = row - 1; j < n; --j)
            {
                if (std::abs(matrix(j, row)) > Matrix<T>::epsilon())
                {
                    for (size_t k = 0; k < n; ++k)
                    {
                        std::swap(matrix(row, k), matrix(j, k));
                    }
                    swapped = true;
                    break;
                }
            }
            if (!swapped)
            {
                throw std::runtime_error("Matrix is singular and cannot be reduced!");
            }
        }

        for (size_t j = 0; j < row; ++j)
        {
            T multiplier = matrix(j, row) / matrix(row, row);
            for (size_t k = 0; k < n; ++k)
            {
                matrix(j, k) -= multiplier * matrix(row, k);
            }

        }
    }
}
