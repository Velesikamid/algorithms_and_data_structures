#pragma once

#include <vector>

#include "../Stats/stats.h"

stats comb_sort(std::vector<int>& v, size_t step) {
    size_t comparison_count = 0, copy_count = 0;
    size_t n = v.size();
    bool is_sorted = false;

    while(step > 1 || is_sorted) {
        if (step > 1) step = step * 4 / 5;
        is_sorted = false;
        size_t i = 0;
        while (i + step < n) {
            ++comparison_count;
            if (v[i] > v[i + step]) {
                is_sorted = true;
                std::swap(v[i], v[i + step]);
                copy_count += 3;
            }
            i += step;
        }
    }

    return stats(comparison_count, copy_count);
}