#pragma once

#include <iostream>
#include <stdexcept>

template <class T>
class MyVector
{
private:
    size_t _size;
    size_t _capacity;
    T *_data;

    void resize(size_t new_capacity)
    {
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

public:
    MyVector() : _size(0), _capacity(0), _data(nullptr) {}
    MyVector(size_t capacity) : _size(0), _capacity(capacity), _data(new T[capacity]) {}
    MyVector(size_t capacity, const T& initial_value) : _size(capacity), _capacity(capacity), _data(new T[capacity]) {
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = initial_value;
        }
    }
    MyVector(const MyVector &other) : _size(other._size), _capacity(other._capacity), _data(new T[_capacity])
    {
        for (size_t i = 0; i < _size; ++i)
        {
            _data[i] = other._data[i];
        }
    }

    MyVector &operator=(const MyVector &other)
    {
        if (this == &other)
        {
            return *this;
        }

        delete[] _data;

        _size = other._size;
        _capacity = other._size;
        _data = new T[_capacity];
        for (size_t i = 0; i < _size; ++i)
        {
            _data[i] = other._data[i];
        }

        return *this;
    }

    ~MyVector()
    {
        delete[] _data;
    }

    size_t size() const
    {
        return _size;
    }
    size_t capacity() const
    {
        return _capacity;
    }

    bool empty() const
    {
        return _size == 0;
    }

    T &operator[](size_t index)
    {
        if (index >= _size)
        {
            throw std::out_of_range("Index out of range!");
        }
        return _data[index];
    }
    const T &operator[](size_t index) const
    {
        if (index >= _size)
        {
            throw std::out_of_range("Index out of range!");
        }
        return _data[index];
    }

    void push_back(const T &value)
    {
        if (_size == _capacity)
        {
            resize(_capacity == 0 ? 1 : _capacity * 2);
        }
        _data[_size++] = value;
    }

    void pop_back()
    {
        if (empty())
        {
            throw std::underflow_error("Vector is empty!");
        }
        --_size;
    }

    void clear()
    {
        _size = 0;
    }

    void shrink_to_fit()
    {
        resize(_size);
    }
};

template <class T>
std::ostream &operator<<(std::ostream &stream, const MyVector<T> &v)
{
    stream << "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        stream << v[i];
        if (i < v.size() - 1)
        {
            stream << ", ";
        }
    }
    stream << "]";
    return stream;
}