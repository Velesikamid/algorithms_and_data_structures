#include <iostream>
#include <random>
#include <vector>

#include "Sortings/bubble_sort.h"
#include "Sortings/comb_sort.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(-100, 100);

    std::vector<int> v1, v2, v3;
    for(size_t i = 0; i < 100; ++i) {
        v1.push_back(dist(gen));
        v2.push_back(dist(gen));
        v3.push_back(dist(gen));
    }
    
    std::cout << "Bubble sort:\n";
    std::cout << "The original array: [";
    for (int n : v1) std::cout << n << " ";
    std::cout << "]\n\n";
    std::cout << bubble_sort(v1);
    std::cout << "The sorted array: [";
    for (int n : v1) std::cout << n << " ";
    std::cout << "]\n\n";

    std::cout << "\nComb sort:\n";
    std::cout << "The original array: [";
    for (int n : v2) std::cout << n << " ";
    std::cout << "]\n\n";
    std::cout << comb_sort(v2, 10);
    std::cout << "The sorted array: [";
    for (int n : v2) std::cout << n << " ";
    std::cout << "]\n\n";

    return 0;
}