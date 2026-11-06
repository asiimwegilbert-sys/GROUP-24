#include <iostream>
#include "satellite_trajectory/satellite_trajectory.hpp"

int main() {
    using namespace sat::num;

    const Matrix matrix{{2.0, 1.0}, {1.0, 3.0}};
    const Vector values{5.0, 6.0};
    const Vector product = matrix * values;
    const Vector sum = values + product;

    std::cout << "Matrix-vector product: [";
    for (std::size_t i = 0; i < product.size(); ++i) {
        std::cout << (i == 0 ? " " : ", ") << product[i];
    }
    std::cout << " ]\n";
    std::cout << "Input plus product: [";
    for (std::size_t i = 0; i < sum.size(); ++i) {
        std::cout << (i == 0 ? " " : ", ") << sum[i];
    }
    std::cout << " ]\n";
    std::cout << "Dot product: " << dot(values, product) << '\n';
}
