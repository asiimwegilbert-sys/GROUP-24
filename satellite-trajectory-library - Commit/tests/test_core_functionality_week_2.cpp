#include "satellite_trajectory/vector.hpp"

#include <cmath>
#include <iostream>

int main() {
    using sat::num::Vector;
    const Vector velocity{3.0, 4.0};
    if (velocity.size() != 2 || velocity[0] != 3.0 ||
        std::abs(velocity.norm() - 5.0) > 1e-12) {
        std::cerr << "Week 2 vector core functionality failed.\n";
        return 1;
    }
    std::cout << "Week 2 vector core functionality passed.\n";
    return 0;
}
