#pragma once

#include <vector>

#include "../Stats/stats.h"

void heapify(std::vector<int>& v, size_t size, size_t idx, size_t& comparison_count, size_t& copy_count) {
    size_t largest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    ++comparison_count;
    if (left < size && v[left] > v[largest]) largest = left;
    ++comparison_count;
    if (right < size && v[right] > v[largest]) largest = right;
    ++comparison_count;
    if (largest != idx) {
        std::swap(v[idx], v[largest]);
        copy_count += 3;
        heapify(v, size, largest, comparison_count, copy_count);
    }
}

stats heap_sort(std::vector<int>& v) {
    size_t comparison_count = 0, copy_count = 0;
    int size = v.size();

    for (int i = size / 2 - 1; i-- > 0;) heapify(v, size, i, comparison_count, copy_count);

    for (size_t i = size - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        copy_count += 3;
        heapify(v, i, 0, comparison_count, copy_count);
    }
}