#include <iostream>

#include "LinkedList/linked_list.h"

int main() {
    LinkedList<int> list1;
    list1.push_tail(10);
    list1.push_tail(20);
    list1.push_tail(5);
    std::cout << "list1: ";
    list1.print();
    std::cout << std::endl;

    LinkedList<float> list2(5, 1.1f, 12.5f);
    std::cout << "list2: ";
    list2.print();
    std::cout << std::endl;

    LinkedList<int> list3(3, -5, 10);
    std::cout << "list3: ";
    list3.print();
    std::cout << std::endl;

    list1.push_tail(list3);
    std::cout << "list1: ";
    list1.print();
    std::cout << std::endl;
}