std::size_t Vector::size() const noexcept { return values_.size(); }

double& Vector::operator[](std::size_t i) { return values_.at(i); }
const double& Vector::operator[](std::size_t i) const { return values_.at(i); }

double Vector::norm() const {
  double sum = 0;
  for (double v : values_) sum += v * v;
  return std::sqrt(sum);
}
