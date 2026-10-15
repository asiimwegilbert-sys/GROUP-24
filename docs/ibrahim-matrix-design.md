# Ibrahim - Matrix Module Design Note

## 1. What I am working on

My assigned part of the project is the Matrix module. The Matrix class will
be one of the basic parts of the numerical library and will later be used by
the other numerical methods.

For this first stage, I focused on deciding what the Matrix should look like,
how the data will be stored, and what rules should be followed when working
with different matrix sizes.

## 2. Proposed Matrix API

The Matrix class should have the following basic functions:

cpp
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
Matrix operator*(double scalar)
const;                                       
bool is_square() const noexcept;                                                            
bool is_approx(const Matrix& other,                                                                 double tolerance = 1e-9) const noexcept;
};
The main idea is to keep the basic Matrix class simple. More advanced
operations such as solving systems and decompositions can use this class
later.
## 3. Storage layout
I propose storing the matrix values in a one-dimensional
`std::vector<double>`.
I will use row-major order. For example:
text
1  2  3
4  5  6
would be stored as:
text
1, 2, 3, 4, 5, 6
The position of an element can be found using:
text
index = row * number_of_columns + column
The actual storage will stay private so that other parts of the project
access the matrix through the Matrix class.
## 4. Dimension rules
### Addition and subtraction
The two matrices must have the same number of rows and columns.
Example:
text
2 x 2 + 2 x 2  ->  valid
2 x 2 + 2 x 3  ->  invalid
### Multiplication
For matrix multiplication, the number of columns in the first matrix must
be the same as the number of rows in the second matrix.
text
(m x n) * (n x p) = (m x p)
For example:
text
2 x 3  *  3 x 2  =  2 x 2
### Transpose
If the original matrix is `m x n`, its transpose will be `n x m`.
### Square matrix
A matrix is square when its number of rows is equal to its number of
columns.
## 5. Invalid inputs
I propose that invalid operations should not be allowed to continue
silently.
The following cases should be checked:
- Zero rows or columns when creating a matrix.
- Different dimensions for addition or subtraction.
- Incompatible dimensions for multiplication.
- Rows of different lengths when using an initializer list.
- Trying to access an element outside the matrix.
The proposed errors are `std::invalid_argument` for invalid matrix
operations and `std::out_of_range` for invalid element access.
## 6. Assumptions
For now I am assuming:
- C++17 will be used.
- Matrix values will be stored as `double`.
- Indexing will start from zero.
- Row-major storage will be used.
- The Matrix class will be inside the `sat_trajectory` namespace.
- A tolerance will be used when comparing floating-point values.
## 7. Questions for the group
Before the final implementation, I think we should agree on:
1. Whether the proposed function names should be kept.
2. What numerical tolerance the whole project should use.
3. Whether determinant and inverse should be part of Matrix or the
   linear-algebra module.
   4. What common error-handling approach the other modules will use.
   5. Whether all members agree on zero-based indexing. 
   
   ## 8. Validation rules
   
   I will use these cases when testing the Matrix:
      - Normal square matrix.
   - Rectangular matrix.
   - Addition with matching dimensions.
   - Addition with mismatched dimensions.
   - Subtraction with matching dimensions.
   - Valid matrix multiplication.
   - Invalid matrix multiplication.
   - Transpose of a matrix.
   - Invalid element index.
   - Invalid matrix dimensions.
   - Inconsistent initializer-list rows.
   
   ## 9. Next step
      After the group agrees on the API and rules, I will implement
      the Matrix
   class and its tests and then connect it to the team's CMake/build structure.
   
