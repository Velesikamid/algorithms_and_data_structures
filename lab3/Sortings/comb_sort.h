#pragma once

#include <vector>

#include "../Stats/stats.h"

stats comb_sort(std::vector<int>& v) {
    stats stat;
    size_t gap = v.size();
    bool swapped = true;

    while(gap > 1 || swapped) {
        gap = (gap * 10) / 13;
        if (gap < 1) gap = 1;
        swapped = false;
        
        for (size_t i = 0; i + gap < v.size(); ++i) {
            ++stat.comparison_count;
            if (v[i] > v[i + gap]) {
                std::swap(v[i], v[i + gap]);
                stat.copy_count += 3;
                swapped = true;
            }
        }
    }

    return stat;
}