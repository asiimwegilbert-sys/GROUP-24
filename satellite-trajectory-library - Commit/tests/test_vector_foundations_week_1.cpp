namespace sat::num {
class Vector {
public:
  Vector() = default;
  explicit Vector(std::size_t size, double value = 0.0);
  Vector(std::initializer_list<double> values);
private:
  std::vector<double> values_;
};
}
