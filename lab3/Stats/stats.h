#pragma once

#include <iostream>

struct stats {
    size_t _comparison_count;
    size_t _copy_count;

    stats(size_t comparison_count = 0, size_t copy_count = 0) :
        _comparison_count(comparison_count),
        _copy_count(copy_count)
    {}
};

std::ostream& operator<<(std::ostream& stream, const stats& stat) {
    stream << "The number of comparisons: " << stat._comparison_count << "\n";
    stream << "The number of copies: " << stat._copy_count << "\n";

    return stream;
}