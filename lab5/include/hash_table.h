#pragma once

#include <iostream>
#include <random>
#include <string>

template <class K, class T>
class HashTable {
private:
    struct Node {
        K _key;
        T _value;
        Node* _next;

        Node(K key, T value) : _key(key), _value(value), _next(nullptr) {}
    };

    struct Bucket {
        Node* _head;
        size_t _size;

        Bucket() : _head(nullptr), _size(0) {}

        ~Bucket() {
            Node* current = _head;
            while (current) {
                Node* next = current->_next;
                delete current;
                current = next;
            }
        }

        void push_back(K key, T value) {
            Node* newNode = new Node(key, value);
            if (!_head) _head = newNode;
            else {
                Node* current = _head;
                while (current->_next) current = current->_next;
                current->_next = newNode;
            }
            ++_size;
        }

        bool erase(K key) {
            if (!_head) return false;

            if (_head->_key == key) {
                Node* toDelete = _head;
                _head = _head->_next;
                delete toDelete;
                --_size;
                return true;
            }

            Node* current = _head;
            while (current->_next) {
                if (current->_next->_key == key) {
                    Node* toDelete = current->_next;
                    current->_next = toDelete->_next;
                    delete toDelete;
                    --_size;
                    return true;
                }
                current = current->_next;
            }
            return false;
        }
    };

    Bucket* _table;
    size_t _tableSize;
    size_t _totalSize;

    size_t hash_function(K key) const {
        const size_t a = 2654435761;
        const size_t w = 32;
        const size_t m = _tableSize;
        const size_t shift = w - log2(m);

        size_t hash = static_cast<size_t>(key) * a;
        return (hash >> shift) % m;
    }

    size_t log2(size_t n) const {
        size_t result = 0;
        while (n >>= 1) ++result;
        return result;
    }

    char to_upper(char c) const {
        if (c >= 'a' && c <= 'z') {
            return c - 'a' + 'A';
        }
        return c;
    }

    size_t roman_to_decimal_hash(const std::string& roman) const {
        size_t decimal = 0;
        size_t prev_value = 0;

        for (int i = roman.size() - 1; i >= 0; --i) {
            char current_char = to_upper(roman[i]);
            size_t current_value = 0;
            switch (current_char) {
                case 'I':
                    current_value = 1;
                    break;
                case 'V':
                    current_value = 5;
                    break;
                case 'X':
                    current_value = 10;
                    break;
                case 'L':
                    current_value = 50;
                    break;
                case 'C':
                    current_value = 100;
                    break;
                case 'D':
                    current_value = 500;
                    break;
                case 'M':
                    current_value = 1000;
                    break;
            }
            
            if (current_value < prev_value) {
                decimal -= current_value;
            } else {
                decimal += current_value;
                prev_value = current_value;
            }
        }
        return decimal;
    }

public:
    HashTable(size_t size = 10) : _tableSize(size), _totalSize(0) {
        _table = new Bucket[size];
    }

    HashTable(size_t size, size_t count) : _tableSize(size), _totalSize(0) {
        _table = new Bucket[size];

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> key_dist(1, 1000);
        std::uniform_int_distribution<T> val_dist(1, 1000);

        for (size_t i = 0; i < count; ++i) {
            insert(key_dist(gen), val_dist(gen));
        }
    }

    HashTable(const HashTable& other) : _tableSize(other._tableSize), _totalSize(other._totalSize) {
        _table = new Bucket[_tableSize];
        for (size_t i = 0; i < _tableSize; ++i) {
            Node* current = other._table[i]._head;
            while (current) {
                _table[i].push_back(current->_key, current->_value);
                current = current->_next;
            }
        }
    }

    ~HashTable() {
        delete[] _table;
    }

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            delete[] _table;

            _tableSize = other._tableSize;
            _totalSize = other._totalSize;
            _table = new Bucket[_tableSize];

            for (size_t i = 0; i < _tableSize; ++i) {
                Node* current = other._table[i]._head;
                while (current) {
                    _table[i].push_back(current->_key, current->_value);
                    current = current->_next;
                }
            }
        }
        return *this;
    }

    void print() const {
        for (size_t i = 0; i < _tableSize; ++i) {
            std::cout << "Bucket " << i << ": ";
            Node* current = _table[i]._head;
            while (current) {
                std::cout << "[" << current->_key << ":" << current->_value << "]";
                current = current->_next;
            }
            std::cout << std::endl;
        }
    }

    bool insert(K key, const T& value) {
        size_t index = hash_function(key);
        Node* current = _table[index]._head;
        while (current) {
            if (current->_key == key) return false;
            current = current->_next;
        }
        _table[index].push_back(key, value);
        ++_totalSize;
        return true;
    }

    void insert_or_assign(K key, T& value) {
        size_t index = hash_function(key);
        Node* current = _table[index]._head;
        while (current) {
            if (current->_key == key) {
                current->_value = value;
                return;
            }
            current = current->_next;
        }
        _table[index].push_back(key, value);
        ++_totalSize;
    }

    bool contains(const T& value) const {
        for (size_t i = 0; i < _tableSize; ++i) {
            Node* current = _table[i]._head;
            while (current) {
                if (current->_value == value) return true;
                current = current->_next;
            }
        }
        return false;
    }

    T* search(K key) {
        size_t index = hash_function(key);
        Node* current = _table[index]._head;
        while (current) {
            if (current->_key == key) return &current->_value;
            current = current->_next;
        }
        return nullptr;
    }

    bool erase(K key) {
        size_t index = hash_function(key);
        if (_table[index].erase(key)) {
            --_totalSize;
            return true;
        }
        return false;
    }

    int count(K key) const {
        size_t index = hash_function(key);
        return _table[index]._size;
    }

    size_t roman_to_decimal(const std::string& roman) const {
        return roman_to_decimal_hash(roman);
    }
};

void string_to_upper(std::string& str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') {
            c = c - 'a' + 'A';
        }
    }
}

void roman_to_decimal() {
    HashTable<std::string, size_t> ht(10);

    std::string roman;
    std::cout << "Enter a roman numeral (I, V, X, L, C, D, M): ";
    std::cin >> roman;

    string_to_upper(roman);

    size_t decimal = ht.roman_to_decimal(roman);
    std::cout << roman << " in decimal is: " << decimal << std::endl;
}