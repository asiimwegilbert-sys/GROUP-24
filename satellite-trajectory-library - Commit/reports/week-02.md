# Week 2 Progress Report

> DRAFT for the team lead (Gilbert) to review and edit. Member summaries come from the individual reports in
> `Team Reports/Team Reports Week 2/` (plus Delvin's `report 2.md` and Ibrahim's Week 2 draft in the Week 1 folder).

## Completed
| Member | Module | Completed this week |
|---|---|---|
| Gilbert (lead) | Integration, CMake | No individual report received yet |
| Delvin | Vector | Core members: `size()`, bounds-checked `operator[]`, `norm()`; tested size, safe access with exceptions, and norms of velocity vectors |
| Ibrahim | Matrix | Row and column sizes, zero-based access, transpose, `+`, `-`, `*` and scalar `*`; dimension and index checks; data kept private as row-major `std::vector<double>` |
| Derrick | Linear solvers | Classes `GaussianSolver` (elimination with partial pivoting) and `BackSubstitutionSolver`; private `options_`, public `SolverOptions` with `pivot_tolerance`; C++23 |
| Stacy | Decompositions | No Week 2 report received yet |
| Praise | Iterative solvers | Reported Gauss-Seidel implemented; `IterationOptions` and `IterationResult` structs with public members; size and zero-diagonal checks; stops at the tolerance |
| Deogratius | Interpolation | `tests/test_interpolation.cpp` (2 tests: known cubic, bad input throws); 2 of 2 passed against a temporary reference implementation |
| Jeremiah | Integration (RK) | Input-check helper `validate_simulation_inputs` (empty state, non-positive `dt`); compiles with zero warnings |
| Erick | Least squares, eigenvalues, trajectory | Reviewed the Matrix and Gaussian elimination work; prepared least-squares test cases with known answers for the solution and the polynomial fit |

## In Progress
- Least-squares solution and polynomial fit implementations (Erick).
- Running Deogratius's tests against the real `interpolation.hpp/.cpp` once merged.
- Aligning the integration checks with the main project wrapper (Jeremiah).
- Eigenvalue dependencies under review (Erick).

## Challenges/Blockers
- The Week 2 Gaussian elimination uses its own C++20 module types, not `sat::num::Matrix` and `Vector`, so the main library cannot call it. The canonical `gaussian_elimination()` in `src/linear_solvers.cpp` is still a TODO (Erick). Least squares is waiting on it.
- Deogratius's tests assume the names `lagrangeInterpolate`, `newtonDividedDifferences`, `newtonEvaluate` and `polynomialFit`. The group has to agree the interpolation API.
- Gauss-Seidel is reported implemented, but it does not yet appear in the integrated `src/iterative_solvers.cpp` (still a TODO there), so it needs merging.
- The interpolation tests were waiting for the CMake setup before they could be built with the project.

## Next Week
- Integrate Gaussian elimination with `sat::num` types.
- Least-squares solution and polynomial fitting, then run the prepared tests (Erick).
- Run the interpolation tests through the project build (Deogratius).

## AI Use
- **Tool:** Claude (Anthropic)
- **Purpose:** Summarising the members' individual Week 2 reports into this team report.
- **What was changed:** 
- Members' own AI use is declared in their individual reports (for example, Erick used ChatGPT).

## Reports received
Delvin, Ibrahim, Derrick, Praise, Deogratius, Jeremiah, Erick. 
Not yet received: Stacy.
