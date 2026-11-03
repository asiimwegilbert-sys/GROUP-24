Completed
 The Matrix pull request was reviewed and merged into `main`. [Reviewer name]
 Implemented Matrix * Vector (operator*(const Matrix&, const Vector&)) in src/matrix.cpp, using the Vector interface now in main. The result has one element per matrix row. It throws std::invalid_argument if the matrix is empty or the Vector size does not equal the number of matrix columns.
 Added 10 tests to tests/test_matrix.cpp for it: normal cases (2x3 and 3x2 shapes, identity), agreement with multiplying by a one-column Matrix, edge cases (1x1, zero Vector) and invalid inputs (wrong size, empty Vector, empty Matrix).

In Progress
 Running the full build and ctest on my own machine. My computer is currently out of service, so the Week 3 and Week 4 Matrix code has not yet been built or run by me locally.

Challenges
 My computer is currently down, so I could not run the build and tests myself. But as soon as I have a working machine or a GitHub Codespace, and fix anything that fails.
 No teammate has asked for extra Matrix functions yet, so none were added this week.