week 3

What i have gone through
Implemented most importantly the Matrix class I declared in include/satellite_trajectory/matrix.hpp, in src/matrix.cpp: default, sized (with optional fill value) and nested initializer-list constructors, rows(), columns(), checked element access with operator(), transpose() and identity(size).
I as well implemented the operators +, -, matrix * matrix and double * Matrix.
Now for error handling: std::invalid_argument for zero-size matrices, rows of different lengths and mismatched sizes. std::out_of_range for invalid indices.
Another thing wrote the tests/test_matrix.cpp (41 checks) covering normal cases, edge cases (1x1, row and column vectors, zero matrix) and invalid inputs.
Checked that the file names match the group CMakeLists.txt.
In Progress(for progressive edits)
Matrix * Vector (operator*(const Matrix&, const Vector&)): declared in the header, implementation waits until the Vector class is merged so the two APIs match.
