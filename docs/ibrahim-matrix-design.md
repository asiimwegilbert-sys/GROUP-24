# Ibrahim — Matrix Module Design Note
## 1. Purpose
The Matrix module provides the foundational matrix data structure for the
Satellite Trajectory Numerical Computing Library.
The Matrix API should provide a clear and reusable interface that can later
support linear algebra operations, Gaussian elimination, decompositions,
iterative solvers, and satellite trajectory calculations.
The design uses standard C++17 and does not depend on external mathematics
libraries.
## 2. Proposed Matrix API
The Matrix class will provide:
- Matrix construction using row and column dimensions.
- Construction from nested initializer lists for convenient testing.
- Access to the number of rows and columns.
- Element access using `(row, column)`.
- Matrix addition.
- Matrix subtraction.
- Matrix multiplication.
- Scalar multiplication.
- Matrix transpose.
- Square-matrix checking.
- Approximate comparison for floating-point tests.
Proposed interface:
  ***cpp
class Matrix {
public:
 Matrix(std::size_t rows, std::size_t cols,
 double initial_value = 0.0);

    Matrix(std::initializer_list<std::initializer_list<double>> values);

 std::size_t rows() const noexcept;
    std::size_t cols() const noexcept;

   double& operator()(std::size_t row, std::size_t col);
    double operator()(std::size_t row, std::size_t col) const;

  Matrix transpose() const;

   Matrix operator+(const Matrix& other) const;
    Matrix operator-(const Matrix& other) const;
    Matrix operator*(const Matrix& other) const;
    Matrix operator*(double scalar) const;

  bool is_square() const noexcept;

   bool is_approx(const Matrix& other,
                   double tolerance = 1e-9) const noexcept;
};
