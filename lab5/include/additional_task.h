#pragma once

#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <optional>

template <class K, class T>
class HashTable {
private:
    enum class NodeState {
        EMPTY,
        OCCUPIED,
        DELETED
    };

    struct Node {
        K _key;
        T _value;
        NodeState _state;

        Node() : _state(NodeState::EMPTY) {}
        Node(K key, T value) : _key(key), _value(value), _state(NodeState::OCCUPIED) {}
    };

    std::vector<Node> _table;
    size_t _size;
    size_t _occupied; // учитывает только занятые ячейки (не DELETED)

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

    // Линейное пробирование
    size_t probe(size_t index, size_t attempt) const {
        return (index + attempt) % _table.size();
    }

    // Найти индекс ключа или подходящее место для вставки
    std::pair<size_t, bool> find_index(K key) const {
        if (_table.empty()) return {0, false};

        size_t index = hash_function(key);
        size_t attempt = 0;
        size_t first_deleted = _table.size(); // запоминаем первую удаленную ячейку

        while (attempt < _table.size()) {
            size_t current = probe(index, attempt);
            
            if (_table[current]._state == NodeState::EMPTY) {
                // Если нашли пустую ячейку, возвращаем или первую удаленную, или текущую
                return {first_deleted != _table.size() ? first_deleted : current, false};
            }
            
            if (_table[current]._state == NodeState::OCCUPIED && _table[current]._key == key) {
                // Нашли ключ
                return {current, true};
            }
            
            if (_table[current]._state == NodeState::DELETED && first_deleted == _table.size()) {
                // Запоминаем первую удаленную ячейку
                first_deleted = current;
            }
            
            attempt++;
        }
        
        // Таблица полная (должно быть редким при хорошем коэффициенте нагрузки)
        return {first_deleted != _table.size() ? first_deleted : _table.size(), false};
    }

public:
    HashTable(size_t size = 10) : _table(size), _size(0), _occupied(0) {}

    HashTable(size_t size, size_t count) : _table(size), _size(0), _occupied(0) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<K> key_dist(1, 1000);
        std::uniform_int_distribution<T> val_dist(1, 1000);

        for (size_t i = 0; i < count; ++i) {
            insert(key_dist(gen), val_dist(gen));
        }
    }

    HashTable(const HashTable& other) : _table(other._table), _size(other._size), _occupied(other._occupied) {}

    ~HashTable() = default;

    HashTable& operator=(const HashTable& other) {
        if (this != &other) {
            _table = other._table;
            _size = other._size;
            _occupied = other._occupied;
        }
        return *this;
    }

    void print() const {
        for (size_t i = 0; i < _table.size(); ++i) {
            std::cout << "Slot " << i << ": ";
            if (_table[i]._state == NodeState::OCCUPIED) {
                std::cout << "[" << _table[i]._key << ":" << _table[i]._value << "]";
            } else if (_table[i]._state == NodeState::DELETED) {
                std::cout << "[DELETED]";
            } else {
                std::cout << "[EMPTY]";
            }
            std::cout << std::endl;
        }
    }

    bool insert(K key, const T& value) {
        if (_occupied >= _table.size() * 0.7) {
            rehash();
        }

        auto [index, found] = find_index(key);
        if (found) return false; // Ключ уже существует

        if (index >= _table.size()) {
            // Таблица полная (маловероятно после rehash)
            rehash();
            return insert(key, value); // Повторная попытка после rehash
        }

        _table[index] = Node(key, value);
        _size++;
        _occupied++;
        return true;
    }

    void insert_or_assign(K key, T& value) {
        if (_occupied >= _table.size() * 0.7) {
            rehash();
        }

        auto [index, found] = find_index(key);
        if (found) {
            _table[index]._value = value;
            return;
        }

        if (index >= _table.size()) {
            // Таблица полная (маловероятно после rehash)
            rehash();
            insert_or_assign(key, value); // Повторная попытка после rehash
            return;
        }

        _table[index] = Node(key, value);
        _size++;
        _occupied++;
    }

    bool contains(const T& value) const {
        for (const auto& node : _table) {
            if (node._state == NodeState::OCCUPIED && node._value == value) {
                return true;
            }
        }
        return false;
    }

    std::optional<T> search(K key) {
        auto [index, found] = find_index(key);
        if (found) {
            return _table[index]._value;
        }
        return std::nullopt;
    }

    bool erase(K key) {
        auto [index, found] = find_index(key);
        if (!found) return false;

        _table[index]._state = NodeState::DELETED;
        _size--;
        return true;
    }

    int count(K key) const {
        auto [index, found] = find_index(key);
        return found ? 1 : 0;
    }

    size_t roman_to_decimal(const std::string& roman) const {
        return roman_to_decimal_hash(roman);
    }

private:
    void rehash() {
        std::vector<Node> old_table = _table;
        _table.clear();
        _table.resize(old_table.empty() ? 10 : old_table.size() * 2);
        _size = 0;
        _occupied = 0;

        for (const auto& node : old_table) {
            if (node._state == NodeState::OCCUPIED) {
                insert(node._key, node._value);
            }
        }
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