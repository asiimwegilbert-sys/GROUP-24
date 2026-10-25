# Week 2 Progress Report

**Submission:** Second submission
**Project:** Satellite Trajectory Numerical Computing Library
**Submitted work:** Reports and structure of the project.

> Report for the team lead (Gilbert) after review. The member sections are taken from the individual reports in
> `Team Reports/`.

## 1. Weekly Summary

This week the group worked on making the library foundation usable. Delvin implemented the core Vector members, and Ibrahim the Matrix operations. Derrick organised Gaussian elimination and back substitution into solver classes. Praise reported the Gauss-Seidel method with option and result structs, Deogratius wrote the first interpolation tests, Jeremiah added input validation for the RK solvers, and Erick prepared least-squares test cases.
The main problems found were that the Week 2 solver uses its own module types and cannot be called from the main library, that the interpolation tests assume function names the library does not have, and that Gaussian elimination in the main library is still a TODO.
No Week 2 report was received from Gilbert or Stacy.

## 2. Team Status Overview

| Member | Assigned module | Completed this week | In progress | Blocker | Commit/PR link |
|---|---|---|---|---|---|
| Gilbert (team lead) | Integration/CMake | No individual report received | Integration of the commits and review | - | - |
| Delvin | Vector | `size()`, bounds-checked `operator[]`, `norm()`; tested | - | - | - |
| Ibrahim | Matrix | Sizes, zero-based access, transpose, `+`, `-`, `*`, scalar `*`; error checks | - | - | commit 5645c3c |
| Derrick | Linear solvers | `GaussianSolver` and `BackSubstitutionSolver` classes with options struct; tests written | - | Needs the C++23 named-module build to run | suggested `feature/derrick-week2-class-based-solvers` |
| Stacy | Decompositions | No individual report received | - | - | - |
| Praise | Iterative solvers | Gauss-Seidel reported implemented; options and result structs | - | Not in the integrated source tree | - |
| Deogratius | Interpolation | `tests/test_interpolation.cpp`, 2 tests, 2/2 passed against a reference implementation | Run against the real implementation | API names; waiting on CMake | - |
| Jeremiah | Integration/RK methods | Input check helper, zero warnings | Align with the main wrapper | - | - |
| Erick | Least squares, eigenvalues, satellite trajectory | Reviewed Matrix and Gaussian elimination work; prepared least-squares test cases | Least-squares implementation; eigenvalue dependencies | Waiting for Gaussian elimination in `sat::num` | - |

## 3. Individual Member Reports
The following are the member reports for their assigned modules, summarised from the individual report files.

### Gilbert (team lead):

General and weekly progress report in details.

### Delvin:

**Assigned responsibility:** Vectors
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Implemented `size()`, `operator[]` with bounds checking, and `norm()` (Euclidean magnitude).
- Tested vector size retrieval, safe element access with exception handling, and norms for velocity vectors in trajectory examples.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### AI Use

- **Tool:** None declared in the individual report.
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Ibrahim:

**Assigned responsibility:** Matrix
**Branch:** -
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/commit/5645c3c4e806ef728d508cc02c3eb79adf5f7063`
**Reviewer(s):** Gilbert.

#### Completed

- Built the Matrix module following the Week 1 interface: row and column sizes, zero-based element access.
- Math operations: transpose, matrix addition, subtraction, multiplication and scalar multiplication.
- Strict error checking for incompatible dimensions and out-of-bounds indices; data kept private in row-major `std::vector<double>` storage.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### AI Use

- **Tool:** None declared in the individual report.
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Derrick:

**Assigned responsibility:** Linear solvers
**Branch:** Suggested: `feature/derrick-week2-class-based-solvers` (not confirmed created)
**Commits:** Suggested: `refactor: organize linear solvers into classes`
**Reviewer(s):** Gilbert.

#### Completed

- Two classes: `GaussianSolver` (elimination with partial pivoting) and `BackSubstitutionSolver` (upper-triangular systems), plus `SolverOptions` holding `pivot_tolerance`.
- Why: each solver's operations and settings are grouped in one place and tests can create a solver object and call `solve`.
- Data: private `options_` in both classes; constructors and `solve()` are public; `pivot_tolerance` is public because `SolverOptions` is a struct. No protected members or inheritance in the Week 2 design.
- Tests written for known answers, a pivoting case and a singular matrix. The report does not claim they were compiled or run. A class layout drawing guide is included.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- The tests need the team's C++23 named-module build configuration.

#### Next Week

- Not stated in the individual report.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Help organize the report and explain the class structure
- **Reason it was used:** To communicate how the solver classes are organized and used
- **What the team verified or changed:** -

### Stacy:

No individual report received.

### Praise:

**Assigned responsibility:** Iterative solvers
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Reported implementing the Gauss-Seidel method, which uses newly calculated values immediately.
- Two structs: `IterationOptions` (tolerance, max iterations) and `IterationResult` (solution, iterations, converged); members are public by design.
- Input validation for sizes, guards against near-zero diagonal values, and stopping when the largest change drops below the tolerance.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Deogratius:

**Assigned responsibility:** Interpolation (tests, test data and edge cases)
**Branch:** -
**Commits:** Build and test output attached to the pull request (link to be added)
**Reviewer(s):** Gilbert.

#### Completed

- Wrote `tests/test_interpolation.cpp` (48 lines, 2 tests, standard headers only): a known cubic `y = 2x³ − 3x² + x − 5` interpolated by Lagrange, Newton and polynomial fit, and bad input (duplicate nodes, mismatched sizes) throwing `std::invalid_argument`.
- Compiled with `-Wall -Wextra` and ran against a temporary reference implementation: 2/2 passed.

#### In Progress

- Run the tests against the real `interpolation.hpp/.cpp` once merged; confirm the test file is picked up by Gilbert's CMake setup.

#### Challenges / Blockers

- The tests assume `lagrangeInterpolate`, `newtonDividedDifferences`, `newtonEvaluate` and `polynomialFit`; the team needs to agree the real names.
- Waiting on the CMake setup so the tests can be built through the project.

#### Next Week

- Run the two tests against the merged implementation and fix any failures.
- More edge cases: exact values at nodes, unsorted nodes, queries near a node, empty input, single point.
- Accuracy tests (sin(x) against the error bound; Runge's function with equispaced versus Chebyshev nodes), Newton-specific tests, and a circular-orbit interpolation example.
- Update the tests to use the group's `Vector` class once available.

#### AI Use

- **Tool:** Claude
- **Purpose:** Research on how to run interpolation tests in C++ and the structure of `test_interpolation.cpp`
- **Reason it was used:** -
- **What the team verified or changed:** -

### Jeremiah:

**Assigned responsibility:** Numerical integration
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert.

#### Completed

- Wrote the helper `validate_simulation_inputs`: it rejects an empty state array and a zero or negative time step before the RK2 and RK4 steps run. Compiles with zero warnings.

#### In Progress

- Start aligning this logic with the main project wrapper next week.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Align the logic with the main project wrapper.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Erick:

**Assigned responsibility:** Least squares, eigenvalues and satellite trajectory
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Updated the repository from `main`; reviewed the Matrix implementation (transpose and matrix multiplication available) and the Week 2 Gaussian elimination and back-substitution work.
- Found that the Week 2 solver uses different Matrix/Vector types from `sat::num`, and that the canonical `gaussian_elimination()` in `src/linear_solvers.cpp` is still a TODO.
- Prepared least-squares test cases with known answers for the solution and the polynomial fit.

#### In Progress

- Preparing `least_squares_solution()` and the polynomial fit; reviewing eigenvalue dependencies.

#### Challenges / Blockers

- Least squares is waiting for `gaussian_elimination()` to be integrated with `sat::num::Matrix` and `Vector`.
- The Week 2 solver uses separate C++20 module types and cannot be called from the main library.

#### Next Week

- Implement least-squares solution and polynomial fitting; run the prepared tests and validate error handling; continue reviewing eigenvalue dependencies.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Review module dependencies, understand the solver integration issue, and help design and verify least-squares test cases
- **Reason it was used:** To support understanding of the numerical methods and prepare the implementation without duplicating another member's work
- **What the team verified or changed:** -

## 4. Decisions Made This Week

| Decision | Reason | Affected modules/members |
|Report and repository editing|Guys used to make a very disorganised work so we later decided on how the report should look like|All|
| None recorded in the individual reports | - | - |

## 5. Issues and Blockers Requiring Team Action

| Issue | Owner | Impact | Action before next Monday (proposed) |
|---|---|---|---|
| Week 2 Gaussian elimination uses its own C++20 module types; `gaussian_elimination()` in `sat::num` is still a TODO | Derrick, Erick | Least squares is blocked | Port elimination to `sat::num::Matrix` and `Vector` |
| Interpolation tests assume names (`lagrangeInterpolate`, `newtonEvaluate`, ...) that differ from the library | Deogratius | Tests cannot build against the library | Agree and use one naming style |
| Gauss-Seidel reported implemented but is a TODO in `src/iterative_solvers.cpp` (copy of 24 Oct) | Praise | Feature missing from the integrated build | Push and merge the implementation |
| Interpolation tests waiting for the CMake setup | Gilbert | Tests are not run with the project | Add the tests to CMake |
| No Week 2 report from and Stacy | Stacy | Incomplete submission | Submit before the deadline |

## 6. Next Week's Shared Goals

1. Integrate Gaussian elimination with the `sat::num` types.
2. Implement least-squares solution and polynomial fitting.
3. Run the interpolation tests against the real implementation through CMake.
4. Align the RK input checks with the main wrapper.

## 7. Conclusion

Week 2 gave the group a usable Vector and Matrix and first versions of the solver, interpolation tests and RK checks. The next step is integration: the solver, the interpolation API and Gauss-Seidel are not yet connected to the main `sat::num` library. Gilbert and Stacy have not submitted individual reports.
