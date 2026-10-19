# Week 2 Progress Report – Erick

## Completed
- Updated the repository with the latest changes from `main`.
- Reviewed the updated Matrix implementation and confirmed that transpose, matrix multiplication, and matrix-vector multiplication are now available.
- Reviewed the Week 2 Gaussian elimination and back-substitution work.
- Identified that the Week 2 solver uses different Matrix/Vector types from the main `sat::num` library.
- Confirmed that the canonical `gaussian_elimination()` in `src/linear_solvers.cpp` is still a TODO.
- Prepared least-squares test cases with known expected results for:
  - Least-Squares Solution.
  - Least-Squares Polynomial Fitting.

## In Progress
- Preparing the implementation of `least_squares_solution()`.
- Preparing the polynomial fitting implementation.
- Reviewing dependencies for eigenvalue computation.

## Challenges / Blockers
- Least-squares implementation is waiting for the canonical `gaussian_elimination()` to be integrated with `sat::num::Matrix` and `sat::num::Vector`.
- The existing Week 2 solver uses separate C++20 module types and cannot yet be called directly from the main library.

## Next Week
- Implement least-squares solution once the canonical solver is available.
- Implement least-squares polynomial fitting.
- Run the prepared tests and validate error handling.
- Continue reviewing eigenvalue dependencies.

## AI Use
- **Tool:** ChatGPT
- **Purpose:** Used to review module dependencies, understand the solver integration issue, and help design and verify least-squares test cases.
- **Reason:** To support understanding of the numerical methods and prepare the implementation without duplicating another team member's work.