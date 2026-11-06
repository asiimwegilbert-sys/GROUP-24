#include "satellite_trajectory/vector.hpp"

#include <cmath>
#include <stdexcept>

namespace sat::num {

Vector::Vector(std::size_t n, double v) : values_(n, v) {}

Vector::Vector(std::initializer_list<double> v) : values_(v) {}

std::size_t Vector::size() const noexcept { return values_.size(); }

double& Vector::operator[](std::size_t i) { return values_.at(i); }

const double& Vector::operator[](std::size_t i) const { return values_.at(i); }

double Vector::norm() const {
    double s = 0.0;
    for (double v : values_) {
        s += v * v;
    }
    return std::sqrt(s);
}

Vector operator+(const Vector& lhs, const Vector& rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vector dimensions must match for addition");
    }

    Vector result(lhs.size());
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i] + rhs[i];
    }
    return result;
}

Vector operator-(const Vector& lhs, const Vector& rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vector dimensions must match for subtraction");
    }

    Vector result(lhs.size());
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        result[i] = lhs[i] - rhs[i];
    }
    return result;
}

Vector operator*(double scalar, const Vector& vector) {
    Vector result(vector.size());
    for (std::size_t i = 0; i < vector.size(); ++i) {
        result[i] = scalar * vector[i];
    }
    return result;
}

Vector operator*(const Vector& vector, double scalar) {
    return scalar * vector;
}

double dot(const Vector& lhs, const Vector& rhs) {
    if (lhs.size() != rhs.size()) {
        throw std::invalid_argument("Vector dimensions must match for dot product");
    }

    double total = 0.0;
    for (std::size_t i = 0; i < lhs.size(); ++i) {
        total += lhs[i] * rhs[i];
    }
    return total;
}

} // namespace sat::num
