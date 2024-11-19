#pragma once

#include <iostream>
#include <random>
#include <stdexcept>

template <class T>
struct Node {
    T _data;
    Node* _prev;
    Node* _next;

    Node(const T& value, Node* prev = nullptr, Node* next = nullptr) : _data(value), _prev(prev), _next(next) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* _head;
    Node<T>* _tail;
    size_t _size;

    void clear();

public:
    LinkedList();
    LinkedList(const LinkedList& other);
    explicit LinkedList(size_t size, const T& min_value, const T& max_value);

    ~LinkedList();
    
    LinkedList& operator=(const LinkedList& other);

    void push_tail(const T& value);
    void push_tail(const LinkedList& other);
    void push_head(const T& value);
    void push_head(const LinkedList& other);

    T pop_head();
    T pop_tail();

    void delete_node(const T& value);

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void print() const;
};

template<class T>
void LinkedList<T>::clear() {
    while (_head) {
        pop_head();
    }
}

template<class T>
LinkedList<T>::LinkedList() : _head(nullptr), _tail(nullptr), _size(0) {}

template<class T>
LinkedList<T>::LinkedList(const LinkedList& other) : LinkedList() {
    Node<T>* current = other._head;
    while (current) {
        push_tail(current->_data);
        current = current->_next;
    }
}

template<class T>
LinkedList<T>::LinkedList(size_t size, const T& min_value, const T& max_value) : LinkedList() {
    if (min_value > max_value) {
        throw std::invalid_argument("Min_value cannot be greater than max_value!");
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<T> dist(min_value, max_value);

    for (size_t i = 0; i < size; ++i) {
        push_tail(dist(gen));
    }
}

template<class T>
LinkedList<T>::~LinkedList() {
    clear();
}

template<class T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        Node<T>* current = other._head;
        while(current) {
            push_tail(current->_data);
            current = current->_next;
        }
    }

    return *this;
}

template<class T>
void LinkedList<T>::push_tail(const T& value) {
    Node<T>* new_node = new Node<T>(value, _tail, nullptr);
    if (!_tail) {
        _head = _tail = new_node;
    } else {
        _tail->_next = new_node;
        _tail = new_node;
    }
    ++_size;
}

template<class T>
void LinkedList<T>::push_tail(const LinkedList& other) {
    Node<T>* current = other._head;
    while (current) {
        push_tail(current->_data);
        current = current->_next;
    }
}

template<class T>
void LinkedList<T>::push_head(const T& value) {
    Node<T>* new_node = new Node<T>(value, nullptr, _head);
    if (!_head) {
        _head = _tail = new_node;
    } else {
        _head->_prev = new_node;
        _head = new_node;
    }
    ++_size;
}

template<class T>
void LinkedList<T>::push_head(const LinkedList& other) {
    Node<T>* current = other._tail;
    while(current) {
        push_head(current->_data);
        current = current->_prev;
    }
}

template<class T>
T LinkedList<T>::pop_head() {
    if (!_head) {
        throw std::underflow_error("List is empty!");
    }

    Node<T>* temp = _head;
    T data = temp->_data;
    _head = _head->_next;
    if (_head) {
        _head->_prev = nullptr;
    } else {
        _tail = nullptr;
    }
    delete temp;
    --_size;

    return data;
}

template<class T>
T LinkedList<T>::pop_tail() {
    if (!_tail) {
        throw std::underflow_error("List is empty!");
    }

    Node<T>* temp = _tail;
    T data = temp->_data;
    _tail = _tail->_prev;
    if (_tail) {
        _tail->_next = nullptr;
    } else {
        _head = nullptr;
    }
    delete temp;
    --_size;

    return data;
}

template<class T>
void LinkedList<T>::delete_node(const T& value) {
    Node<T>* current = _head;
    while (current) {
        Node<T>* next = current->_next;
        if (current->_data == value) {
            if (current->_prev) {
                current->_prev->_next = current->_next;
            } else {
                _head = current->_next;
            }
            if (current->_next) {
                current->_next->_prev = current->_prev;
            } else {
                _tail = current->_prev;
            }
            delete current;
            --_size;
        }
        current = next;
    }
}

template<class T>
T& LinkedList<T>::operator[](size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range!");
    }

    Node<T>* current = _head;
    for (size_t i = 0; i < index; ++i) {
        current = current->_next;
    }
    return current->_data;
}

template<class T>
const T& LinkedList<T>::operator[](size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range!");
    }

    Node<T>* current = _head;
    for (size_t i = 0; i < index; ++i) {
        current = current->_next;
    }
    return current->_data;
}

template<class T>
void LinkedList<T>::print() const {
    Node<T>* current = _head;
    while (current) {
        std::cout << current->_data << " ";
        current = current->_next;
    }
    std::cout << std::endl;
}