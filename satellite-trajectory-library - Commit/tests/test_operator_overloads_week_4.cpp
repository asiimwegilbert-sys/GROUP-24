#include "satellite_trajectory/vector.hpp"

#include <iostream>
#include <stdexcept>

int main() {
    using sat::num::Vector;
    using sat::num::dot;

    const Vector a{1.0, 2.0, 3.0};
    const Vector b{4.0, 5.0, 6.0};
    const Vector sum = a + b;
    const Vector difference = b - a;
    const Vector scaled = 2.0 * a;

    if (sum[0] != 5.0 || sum[1] != 7.0 || sum[2] != 9.0 ||
        difference[0] != 3.0 || difference[1] != 3.0 || difference[2] != 3.0 ||
        scaled[0] != 2.0 || scaled[1] != 4.0 || scaled[2] != 6.0 ||
        dot(a, b) != 32.0) {
        std::cerr << "Vector operator overload results are incorrect.\n";
        return 1;
    }

    bool rejected_mismatch = false;
    try {
        (void)(a + Vector{1.0});
    } catch (const std::invalid_argument&) {
        rejected_mismatch = true;
    }
    if (!rejected_mismatch) {
        std::cerr << "Vector addition did not reject mismatched dimensions.\n";
        return 1;
    }

    std::cout << "Vector operator overload tests passed.\n";
    return 0;
}
