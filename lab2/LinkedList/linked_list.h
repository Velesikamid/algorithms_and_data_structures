#pragma once 
 
#include <iostream> 
#include <random> 
#include <stdexcept> 
#include <type_traits> 
 
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
    int _size; 
 
    void clear(); 
 
public: 
    LinkedList(); 
    LinkedList(const LinkedList& other); 
    LinkedList(int count, const T& min_value, const T& max_value); 
 
    ~LinkedList(); 
     
    LinkedList& operator=(const LinkedList& other); 
 
    void push_tail(const T& value); 
    void push_tail(const LinkedList& other); 
    void push_head(const T& value); 
    void push_head(const LinkedList& other); 
 
    T pop_head(); 
    T pop_tail(); 
 
    void delete_node(const T& value); 
 
    T& operator[](int index); 
    const T& operator[](int index) const; 
 
    int get_size() const; 
 
    template<class U> 
    friend std::ostream& operator<<(std::ostream& stream, const LinkedList<U>& list); 
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
LinkedList<T>::LinkedList(int count, const T& min_value, const T& max_value) : LinkedList() { 
    if (min_value > max_value) { 
        throw std::invalid_argument("min_value cannot be greater than max_value"); 
    } 
 
    std::random_device rd; 
    std::mt19937 gen(rd()); 
    if constexpr (std::is_integral<T>::value) { 
        std::uniform_int_distribution<T> dist(min_value, max_value); 
        for (int i = 0; i < count; ++i) { 
            push_tail(dist(gen)); 
        } 
    } else if constexpr (std::is_floating_point<T>::value) { 
        std::uniform_real_distribution<T> dist(min_value, max_value); 
        for (int i = 0; i < count; ++i) { 
            push_tail(dist(gen)); 
        } 
    } else { 
        throw std::invalid_argument("Unsupported type for random generation!"); 
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
T& LinkedList<T>::operator[](int index) { 
    if (index >= _size) { 
        throw std::out_of_range("Index out of range!"); 
    } 
 
    Node<T>* current = _head; 
    for (int i = 0; i < index; ++i) { 
        current = current->_next; 
    } 
    return current->_data; 
} 
 
template<class T> 
const T& LinkedList<T>::operator[](int index) const { 
    if (index >= _size) { 
        throw std::out_of_range("Index out of range!"); 
    } 
 
    Node<T>* current = _head; 
    for (int i = 0; i < index; ++i) { 
        current = current->_next; 
    } 
    return current->_data; 
} 
 
template<class T> 
int LinkedList<T>::get_size() const { 
    return _size; 
} 
 
template<class T> 
std::ostream& operator<<(std::ostream& stream, const LinkedList<T>& list) { 
    Node<T>* current = list._head; 
    stream << "["; 
    while (current) { 
        stream << current->_data; 
        current = current->_next; 
        if (current) stream << ", "; 
    } 
    stream << "]"; 
 
    return stream; 
} 
 
LinkedList<int> add_numbers(const LinkedList<int>& list1, const LinkedList<int>& list2) { 
    if (list1.get_size() == 0 || list2.get_size() == 0) { 
        throw std::invalid_argument("One of the lists is empty!"); 
    } 
 
    LinkedList<int> result; 
    int i = list1.get_size() - 1; 
    int j = list2.get_size() - 1; 
    int carry = 0; 
     
    while (i >= 0 && j >= 0) { 
        int digit1 = list1[i--], digit2 = list2[j--]; 
        int sum = carry + digit1 + digit2; 
        carry = sum / 10; 
        result.push_head(sum % 10); 
    } 
 
    if (i < 0 && j >= 0) { 
        while(j >= 0) { 
            int digit = list2[j--]; 
            int sum = carry + digit; 
            carry = sum / 10; 
            result.push_head(sum % 10); 
        } 
    } 
     
    if (i >= 0 && j < 0) { 
        while(i >= 0) { 
            int digit = list1[i--]; 
            int sum = carry + digit; 
            carry = sum / 10; 
            result.push_head(sum % 10); 
        } 
    } 
     
    if (i < 0 && j < 0 && carry != 0) result.push_head(carry); 
 
    return result; 
} 
 
LinkedList<int> multiply_numbers(const LinkedList<int>& list1, const LinkedList<int>& list2) { 
    if (list1.get_size() == 0 || list2.get_size() == 0) { 
        throw std::invalid_argument("One of the lists is empty!"); 
    } 
 
    LinkedList<int> result; 
    int carry = 0;
    int second_number = 0; 
    for (int j = list2.get_size() - 1; j >= 0; --j) { 
        int place = 1; 
        for (int i = 0; i < list2.get_size() - 1 - j; ++i) { 
            place *= 10; 
        } 
        second_number += list2[j] * place; 
    } 
 
    for (int i = list1.get_size() - 1; i >= 0; --i) { 
        int digit = carry + list1[i] * second_number; 
        carry = digit / 10; 
        result.push_head(digit % 10); 
    } 
 
    result.push_head(carry); 
 
    return result; 
} 
 
void print_number(const LinkedList<int>& list) { 
    for (int i = 0; i < list.get_size(); ++i) { 
        std::cout << list[i]; 
    } 
}