#pragma once

#include <vector>
#include <list>
#include <string>
#include <random>
#include <iostream>

template <class K, class T>
class HashTable {
private:
    struct Node {
        K _key;
        T _value;

        Node(K key, T value) : _key(key), _value(value) {}
    };

    std::vector<std::list<Node>> _table;
    size_t _size;

    size_t hash_function(K key) const {
        const size_t a = 2654435761;
        const size_t w = 32;
        const size_t m = _table.size();
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
    HashTable(size_t size = 10) : _table(size), _size(0) {}

    HashTable(size_t size, size_t count) : _table(size), _size(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> key_dist(1, 1000);
        std::uniform_int_distribution<T> val_dist(1, 1000);

        for (size_t i = 0; i < count; ++i) {
            insert(key_dist(gen), val_dist(gen));
        }
    }

    HashTable(const HashTable& other) : _table(other._table), _size(other._size) {}

    ~HashTable() = default;

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            _table = other._table;
            _size = other._size;
        }
        return *this;
    }

    void print() const {
        for (size_t i = 0; i < _table.size(); ++i) {
            std::cout << "Bucket " << i << ": ";
            for (const auto& node : _table[i]) {
                std::cout << "[" << node._key << ":" << node._value << "] ";
            }
            std::cout << std::endl;
        }
    }

    bool insert(K key, const T& value) {
        size_t index = hash_function(key);
        for (auto& node : _table[index]) {
            if (node._key == key) return false;
        }
        _table[index].emplace_back(key, value);
        ++_size;
        return true;
    }

    void insert_or_assign(K key, T& value) {
        size_t index = hash_function(key);
        for (auto& node : _table[index]) {
            if (node._key == key) {
                node._value = value;
                return;
            }
        }
        _table[index].emplace_back(key, value);
        ++_size;
    }

    bool contains(const T& value) const {
        for (const auto& bucket : _table) {
            for (const auto& node : bucket) {
                if (node._value == value) {
                    return true;
                }
            }
        }
        return false;
    }

    T* search(K key) {
        size_t index = hash_function(key);
        for (auto& node : _table[index]) {
            if (node._key == key) {
                return &node._value;
            }
        }
        return nullptr;
    }

    bool erase(K key) {
        size_t index = hash_function(key);
        for (auto it = _table[index].begin(); it != _table[index].end(); ++it) {
            if (it->_key == key) {
                _table[index].erase(it);
                --_size;
                return true;
            }
        }
        return false;
    }

    int count(K key) const {
        size_t index = hash_function(key);
        return _table[index].size();
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