#pragma once

#include <vector>

#include "../Stats/stats.h"

stats bubble_sort(std::vector<int>& v) {
    stats stat;
    size_t n = v.size();
    bool swapped = true;

    for (size_t i = 0; i < n - 1 && swapped; ++i) {
        swapped = false;
        for (size_t j = 0; j < n - i - 1; ++j) {
            ++stat.comparison_count;
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
                stat.copy_count += 3;
                swapped = true;
            }
        }
    }

    return stat;
}