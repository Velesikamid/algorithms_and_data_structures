#include "hash_table.h"

int main() {
    HashTable<int, std::string> ht(11);
    ht.insert(1, "one");
    ht.insert(2, "two");
    ht.insert(3, "three");
    ht.insert(4, "four");
    ht.insert(5, "five");
    ht.insert(6, "six");
    ht.insert(7, "seven");
    ht.insert(8, "eight");
    ht.insert(9, "nine");
    ht.insert(10, "ten");
    ht.insert(100, "one hundred");
    ht.print();

    roman_to_decimal();

    return 0;
}