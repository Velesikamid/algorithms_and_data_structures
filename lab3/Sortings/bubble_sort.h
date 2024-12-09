#pragma once

#include <vector>

#include "../Stats/stats.h"

stats bubble_sort(std::vector<int>& v) {
    size_t comparison_count = 0, copy_count = 0;
    size_t n = v.size();

    for (size_t i = 0; i < n; ++i) {
        bool is_sorted = true;
        for (size_t j = 0; j < n - i - 1; ++j) {
            ++comparison_count;
            if (v[j] > v[j + 1]) {
                is_sorted = false;
                std::swap(v[j], v[j + 1]);
                copy_count += 3;
            }
        }
        if (is_sorted) break;
    }

    return stats(comparison_count, copy_count);
}