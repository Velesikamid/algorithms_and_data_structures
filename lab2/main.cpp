#include <iostream> 
 
#include "LinkedList/linked_list.h" 
 
int main() {
    std::cout << "Checking the default ctor and adding methods:\n";
    LinkedList<int> list1; 
    list1.push_tail(10); 
    list1.push_tail(20); 
    list1.push_head(5); 
    std::cout << "list1: " << list1 << "\n\n"; 

    std::cout << "Checking random ctor:\n";
    LinkedList<float> list2(5, 1.1f, 12.5f); 
    std::cout << "list2: " << list2 << "\n";
    LinkedList<double> list3(7, -2.3, 5.7);
    std::cout << "list3: " << list3 << "\n";
    LinkedList<int> list4(3, -5, 10); 
    std::cout << "list4: " << list4 << "\n\n";

    std::cout << "Checking the copy ctor and deleting methods:\n";
    LinkedList<float> list5(list2);
    std::cout << "list2: " << list2 << "\n" << "list5: " << list5 << "\n";
    std::cout << "The deleted element: " << list5.pop_head() << "\n";
    std::cout << "The deleted element: " << list5.pop_tail() << "\n";
    std::cout << "list2: " << list2 << "\n" << "list5: " << list5 << "\n\n";
 
    std::cout << "Checking adding methods with a list:\n";
    std::cout << "list1: " << list1 << "\n" << "list4: " << list4 << "\n";
    list1.push_tail(list4); 
    std::cout << "list1 after push_tail(list4): " << list1 << "\n";
    list1.push_head(list4); 
    std::cout << "list1 after push_head(list4): " << list1 << "\n";
    std::cout << "The deleted element: " << list1.pop_head() << "\n";
    std::cout << "The deleted element: " << list1.pop_tail() << "\n";
    std::cout << "list1: " << list1 << "\n" << "list4: " << list4 << "\n";
    list4.push_head(123);
    std::cout << "The deleted element: " << list4.pop_tail() << "\n";
    std::cout << "list1: " << list1 << "\n" << "list4: " << list4 << "\n\n";
 
    std::cout << "Checking the sum function:\n";
    LinkedList<int> list6(3, 1, 9); 
    LinkedList<int> list7(3, 1, 9); 
    LinkedList<int> list8(5, 1, 9); 
    std::cout << "list6: " << list6 << "\n" << "list7: " << list7 << "\n" << "list8: " << list8 << "\n"; 
    LinkedList<int> list9 = add_numbers(list6, list7); 
    std::cout << "list6 + list7: "; 
    print_number(list9); 
    std::cout << "\n"; 
    list9 = add_numbers(list7, list8); 
    std::cout << "list7 + list8: "; 
    print_number(list9);
    std::cout << "\n"; 
    list9 = add_numbers(list8, list7);
    std::cout << "list8 + list7: "; 
    print_number(list9); 
    std::cout << "\n\n"; 
 
    std::cout << "Checking the multiplication function:\n";
    std::cout << "list6: " << list6 << "\n" << "list7: " << list7 << "\n" << "list8: " << list8 << "\n"; 
    list9 = multiply_numbers(list6, list7); 
    std::cout << "list6 * list7: "; 
    print_number(list9); 
    std::cout << "\n"; 
    list9 = multiply_numbers(list7, list8); 
    std::cout << "list7 * list8: "; 
    print_number(list9); 
    std::cout << "\n"; 
    list9 = multiply_numbers(list8, list7); 
    std::cout << "list8 * list7: "; 
    print_number(list9); 
    std::cout << "\n\n"; 

    std::cout << "Checking the = and the delete_node:\n";
    LinkedList<int> list10 = list1;
    std::cout << "list1: " << list1 << "\n" << "list10: " << list10 << "\n";
    list10.push_tail(5);
    list10[1] = 5;
    std::cout << "list1: " << list1 << "\n" << "list10: " << list10 << "\n";
    list10.delete_node(5);
    std::cout << "list1: " << list1 << "\n" << "list10: " << list10 << "\n";
 
    return 0; 
}
