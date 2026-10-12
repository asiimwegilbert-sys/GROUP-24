#pragma once
#include <cstddef>
#include <initializer_list>
#include <vector>
namespace sat::num {
class Vector {
public:
  Vector() = default;
  explicit Vector(std::size_t size, double value = 0.0);
  Vector(std::initializer_list<double> values);
  std::size_t size() const noexcept;
  double& operator[](std::size_t index);
  const double& operator[](std::size_t index) const;
  double norm() const;
private:
  std::vector<double> values_;
};
Vector operator+(const Vector&, const Vector&);
Vector operator-(const Vector&, const Vector&);
Vector operator*(double, const Vector&);
double dot(const Vector&, const Vector&);
}
