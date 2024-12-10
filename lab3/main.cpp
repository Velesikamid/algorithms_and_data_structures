#include <iostream>
#include <random>
#include <vector>

#include "Sortings/bubble_sort.h"
#include "Sortings/comb_sort.h"
#include "Sortings/heap_sort.h"

std::vector<int> generate_random_array(size_t size, int min = 0, int max = 10000) {
    std::vector<int> v(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(min, max);

    for (size_t i = 0; i < size; ++i) {
         v[i] = dis(gen);
    }

    return v;
}

int main() {
    std::vector<size_t> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000};
    for (const auto& size : sizes) {
        std::vector<int> random_array = generate_random_array(size);
        std::vector<int> sorted_array = random_array;
        std::vector<int> reversed_array = random_array;

        std::sort(sorted_array.begin(), sorted_array.end());
        std::sort(reversed_array.rbegin(), reversed_array.rend());

        std::cout << "Array size: " << size <<"\n";

        auto random_copy = random_array;
        stats stat = bubble_sort(random_copy);
        std::cout << "Bubble Sort - Random:\n" << stat << "\n";

        random_copy = random_array;
        stat = comb_sort(random_copy);
        std::cout << "Comb Sort - Random:\n" << stat << "\n";

        random_copy = random_array;
        stat = heap_sort(random_copy);
        std::cout << "Heap Sort - Random:\n" << stat;

        std::cout << "------------------------------------\n";
    }

    return 0;
}