#pragma once

#include <complex>
#include <format>
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

public:
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

    Matrix(size_t rows, size_t cols, const T &initial_value)
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