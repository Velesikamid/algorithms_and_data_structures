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

void reverse_array(std::vector<int>& v) {
    size_t left = 0;
    size_t right = v.size() - 1;

    while (left < right) {
        std::swap(v[left], v[right]);
        ++left;
        --right;
    }
}

double find_average(std::vector<size_t>& v) {
    size_t sum = 0;
    for (size_t num : v) sum += num;

    return static_cast<double>(sum) / v.size();
}

int main() {
    std::vector<size_t> sizes = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 25000, 50000, 100000};
    for (const auto& size : sizes) {
        std::vector<int> random_array = generate_random_array(size);
        std::vector<int> sorted_array = random_array;
        std::vector<int> reversed_array = random_array;

        heap_sort(sorted_array);
        reverse_array(reversed_array);

        std::cout << "Array size: " << size <<"\n";

        std::vector<size_t> av_comparison_bubble;
        std::vector<size_t> av_copy_bubble;
        std::vector<size_t> av_comparison_comb;
        std::vector<size_t> av_copy_comb;
        std::vector<size_t> av_comparison_heap;
        std::vector<size_t> av_copy_heap;

        for (size_t i = 0; i < 100; ++i) {
            std::vector<int> random_array = generate_random_array(size);
            auto random_copy = random_array;
            stats stat = bubble_sort(random_copy);
            av_comparison_bubble.push_back(stat.comparison_count);
            av_copy_bubble.push_back(stat.copy_count);

            random_copy = random_array;
            stat = comb_sort(random_copy);
            av_comparison_comb.push_back(stat.comparison_count);
            av_copy_comb.push_back(stat.copy_count);

            random_copy = random_array;
            stat = heap_sort(random_copy);
            av_comparison_heap.push_back(stat.comparison_count);
            av_copy_heap.push_back(stat.copy_count);
        }

        std::cout << "Bubble Sort:\n";
        std::cout << "\tAverage:\n";
        std::cout << "The number of comparisons: " << find_average(av_comparison_bubble) << "\n";
        std::cout << "The number of copies: " << find_average(av_copy_bubble) << "\n";
        auto random_copy = sorted_array;
        stats stat = bubble_sort(random_copy);
        std::cout << "\tThe best:\n" << stat;
        random_copy = reversed_array;
        stat = bubble_sort(random_copy);
        std::cout << "\tThe worst:\n" << stat << "\n";

        std::cout << "Comb Sort:\n";
        std::cout << "\tAverage:\n";
        std::cout << "The number of comparisons: " << find_average(av_comparison_comb) << "\n";
        std::cout << "The number of copies: " << find_average(av_copy_comb) << "\n";
        random_copy = sorted_array;
        stat = comb_sort(random_copy);
        std::cout << "\tThe best:\n" << stat;
        random_copy = reversed_array;
        stat = comb_sort(random_copy);
        std::cout << "\tThe worst:\n" << stat << "\n";

        std::cout << "------------------------------------\n";
    }

    return 0;
}