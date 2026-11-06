# Week 4 Progress Report

> Team summary compiled from the Week 4 individual reports and the repository review dated 2 November. Reported completion is not treated as independently verified unless noted.

## Completed

| Member | Module | Reported work and verification status |
|---|---|---|
| Gilbert | Integration and CMake | No separate individual Week 4 report was identified; integration evidence is summarized in the team report. |
| Delvin | Vector | Reported vector addition, subtraction, scalar multiplication and dot product with sample checks. Repository review found the operators in a test file without `main`, while `src/vector.cpp` still contained TODO behavior. |
| Ibrahim | Matrix | Reported `Matrix * Vector` and 10 tests. His report says local build/testing was pending because his computer was unavailable; the repository review found integration/build issues. |
| Derrick | Linear solvers | Reported iterative refinement and a `RefinementSolver`; those solver classes were not found in the repository code reviewed. |
| Stacy | Decompositions | Two individual Week 4 reports are present. One reports focused tests passed; the other describes stabilization and requests final integrated validation. Their verification status differs and needs reconciliation. |
| Praise | Iterative solvers | Reported Jacobi, Gauss-Seidel and power iteration as finalized and tested. The 2 November repository review did not find Gauss-Seidel and power iteration in the available source/branches. |
| Deogratius | Interpolation | Reported updating `interpolation.hpp`; the implementation was described as incomplete and on an unmerged branch. |
| Jeremiah | Integration | Reported `ClassicalRK4Solver`, `GaussLegendreSolver` and `RombergSolver`; PR #52 is recorded as merged. |
| Erick | Trajectory, least squares and eigenvalues | Reported a two-body model and RK2/RK4 propagation; the report/repository review still listed least squares and eigenvalues as TODO. |

## In Progress

- Validate the current integrated release candidate and resolve discrepancies between reported completion and repository state.
- Complete missing implementations and connect tests/examples to the CMake build.
- Confirm decomposition tests and final integrated build results.

## Challenges / Blockers

- The 2 November review found the project did not build from `main`; issues included test filenames with spaces, duplicate Matrix sources, and module-style solver files in a C++17 build.
- The review also found required methods still marked TODO, including Gaussian elimination, determinant, inverse, Gauss-Seidel, power iteration, interpolation, least squares and eigenvalues.
- Individual reports do not consistently include exact test commands/results, and some reported features were not found in the reviewed source.

## Next Week

- Integrate and verify the missing implementations in the C++17 library.
- Reconcile individual report claims with branch, build and test evidence.
- Complete the README, final report, presentation and submission checks.

## Reports Received

Week 4 individual reports are present for Delvin, Ibrahim, Derrick, Stacy (two reports), Praise, Deogratius, Jeremiah and Erick. Gilbert's separate individual Week 4 report was not identified.

## AI Use

- Individual AI-use statements should be taken from the respective member reports. This summary does not infer additional usage.
