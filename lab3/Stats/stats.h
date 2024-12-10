#pragma once

#include <iostream>

struct stats {
    size_t comparison_count = 0;
    size_t copy_count = 0;
};

std::ostream& operator<<(std::ostream& stream, const stats& stat) {
    stream << "The number of comparisons: " << stat.comparison_count << "\n";
    stream << "The number of copies: " << stat.copy_count << "\n";

    return stream;
}