#pragma once

#include <vector>

#include "../Stats/stats.h"

void heapify(std::vector<int>& v, size_t size, size_t idx, stats& stat) {
    size_t largest = idx;
    size_t left = 2 * idx + 1;
    size_t right = 2 * idx + 2;

    ++stat.comparison_count;
    if (left < size && v[left] > v[largest]) largest = left;
    ++stat.comparison_count;
    if (right < size && v[right] > v[largest]) largest = right;
    ++stat.comparison_count;
    if (largest != idx) {
        std::swap(v[idx], v[largest]);
        stat.copy_count += 3;
        heapify(v, size, largest, stat);
    }
}

stats heap_sort(std::vector<int>& v) {
    stats stat;
    size_t size = v.size();

    for (size_t i = size / 2; i > 0; --i) heapify(v, size, i - 1, stat);

    for (size_t i = size - 1; i > 0; --i) {
        std::swap(v[0], v[i]);
        stat.copy_count += 3;
        heapify(v, i, 0, stat);
    }

    return stat;
}