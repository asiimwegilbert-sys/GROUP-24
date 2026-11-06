#include "satellite_trajectory/vector.hpp"

#include <cmath>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

namespace {

int failures = 0;

void check(bool condition, const std::string& name) {
    if (condition) {
        std::cout << "PASS: " << name << '\n';
    } else {
        std::cerr << "FAIL: " << name << '\n';
        ++failures;
    }
}

bool throws_invalid_argument(const std::function<void()>& action) {
    try {
        action();
    } catch (const std::invalid_argument&) {
        return true;
    } catch (...) {
        return false;
    }
    return false;
}

} // namespace

int main() {
    using sat::num::Vector;
    using sat::num::dot;

    const Vector lhs{1.0, 2.0, 3.0};
    const Vector rhs{4.0, 5.0, 6.0};
    const Vector added = lhs + rhs;
    const Vector subtracted = rhs - lhs;
    const Vector scaled_left = 2.0 * lhs;

    check(added[0] == 5.0 && added[1] == 7.0 && added[2] == 9.0,
          "vector addition");
    check(subtracted[0] == 3.0 && subtracted[1] == 3.0 && subtracted[2] == 3.0,
          "vector subtraction");
    check(scaled_left[0] == 2.0 && scaled_left[1] == 4.0 && scaled_left[2] == 6.0,
          "scalar multiplication");
    check(dot(lhs, rhs) == 32.0, "dot product");
    check(std::abs(lhs.norm() - std::sqrt(14.0)) < 1e-12, "Euclidean norm");
    check(throws_invalid_argument([&] { (void)(lhs + Vector{1.0}); }),
          "addition rejects mismatched dimensions");
    check(throws_invalid_argument([&] { (void)(lhs - Vector{1.0}); }),
          "subtraction rejects mismatched dimensions");
    check(throws_invalid_argument([&] { (void)dot(lhs, Vector{1.0}); }),
          "dot product rejects mismatched dimensions");

    if (failures == 0) {
        std::cout << "\nAll vector operation tests passed.\n";
        return 0;
    }
    std::cerr << failures << " vector operation test(s) failed.\n";
    return 1;
}
