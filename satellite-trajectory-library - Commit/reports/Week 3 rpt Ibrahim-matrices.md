Week 3 Progress Report
For being specific ;
Module: Matrix
Branch: feature/ibrahim-matrix

Completed

This week I committed the working Matrix class (include/sat_trajectory/matrix.hpp, src/matrix.cpp) following the Week 1 design: row-major std::vector<double> storage, zero-based indexing, private data.
Operations went for this week more revised: transpose, addition, subtraction, matrix multiplication and scalar multiplication. Also added identity(n), isSquare() and almostEqual() for the solver modules to use.
Error handling: std::invalid_argument for zero-size matrices, a wrong number of values and mismatched sizes. std::out_of_range for invalid indices.
I revised and wrote let me say drafted tests/test_matrix.cpp (41 checks) covering normal cases, edge cases (1x1, row and column vectors, zero matrix) and invalid inputs.
