Vector operator+(const Vector& a, const Vector& b) {
  if (a.size() != b.size()) throw std::logic_error("Size mismatch");
  Vector result(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) result[i] = a[i] + b[i];
  return result;
}

Vector operator-(const Vector& a, const Vector& b) {
  if (a.size() != b.size()) throw std::logic_error("Size mismatch");
  Vector result(a.size());
  for (std::size_t i = 0; i < a.size(); ++i) result[i] = a[i] - b[i];
  return result;
}

Vector operator*(double scalar, const Vector& v) {
  Vector result(v.size());
  for (std::size_t i = 0; i < v.size(); ++i) result[i] = scalar * v[i];
  return result;
}

double dot(const Vector& a, const Vector& b) {
  if (a.size() != b.size()) throw std::logic_error("Size mismatch");
  double sum = 0;
  for (std::size_t i = 0; i < a.size(); ++i) sum += a[i] * b[i];
  return sum;
}
