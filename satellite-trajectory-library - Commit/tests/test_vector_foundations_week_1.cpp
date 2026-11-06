#include "satellite_trajectory/vector.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    using sat::num::Vector;

    const Vector empty;
    const Vector zeros(3);
    const Vector filled(2, 2.5);
    const Vector values{1.0, -2.0, 3.0};
    const Vector& const_values = values;

    if (empty.size() != 0 || zeros.size() != 3 || zeros[1] != 0.0 ||
        filled[0] != 2.5 || values.size() != 3 || const_values[1] != -2.0) {
        std::cerr << "Vector foundation construction or access failed.\n";
        return 1;
    }

    bool checked_bounds = false;
    try {
        (void)const_values[3];
    } catch (const std::out_of_range&) {
        checked_bounds = true;
    }
    if (!checked_bounds) {
        std::cerr << "Vector indexing did not reject an out-of-range index.\n";
        return 1;
    }

    std::cout << "Vector foundation tests passed.\n";
    return 0;
}
