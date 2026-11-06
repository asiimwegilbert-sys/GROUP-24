# Week 4 Progress Report

**Submission:** Fourth submission
**Project:** Satellite Trajectory Numerical Computing Library
**Submitted work:** Reports and project Code.

> Team report from lead Gilbert after review. Member sections come from individual reports where available; Gilbert's section summarizes the lead work recorded in the team report. "Repository check" lines are attributed to the lead's review of Git history and code.

## 1. Weekly Summary

Week 4 was meant to finish interpolation, integration, fitting and eigenvalues. Jeremiah finished RK4, Gaussian quadrature and Romberg as two class families, and Erick connected the RK2/RK4 steps to a two-body satellite propagation. Ibrahim added Matrix * Vector with 10 new tests, Delvin reported the vector operators, Derrick added iterative refinement, and Deogratius updated the interpolation header.
A review of the repository on 2 November found that the project did not build from `main` (test file names with spaces, two matrix files compiled together, module-style solver files in a C++17 build) and that several required methods were still `TODO`: Gaussian elimination, determinant, inverse, Gauss-Seidel, power iteration, the interpolation functions, least squares and eigenvalues. The lead's patch fixes the build and fills these in.
No separate Week 4 individual report from Gilbert is identified. His repository-review and integration work is summarized below from the team report. Individual Week 4 reports are present for Stacy and Praise; their statements and the repository review are also summarized below.

## 2. Team Status Overview

| Member | Assigned module | Completed this week | In progress | Blocker | Commit/PR link |
|---|---|---|---|---|---|
| Gilbert (team lead) | Integration/CMake | No individual report. Git: 94 commits, 36 pull requests merged | Integration and release | Clean-environment build and coverage checklist not found | - |
| Delvin | Vector | Reports vector `+`, `-`, scalar `*`, dot implemented and checked | - | Operators were not yet in `src/vector.cpp` | - |
| Ibrahim | Matrix | `Matrix * Vector` plus 10 tests | Build and `ctest` on his machine | His computer is out of service | - |
| Derrick | Linear solvers | Iterative refinement; `RefinementSolver` derived class | - | Solver classes are not in the repository code | - |
| Stacy | Decompositions | Two Week 4 reports are present. `week-04-Stacy.md` says focused decomposition tests compiled and passed; `Stacy-week-04.md` describes the stabilization checks and asks for final integrated validation | Verify the current release candidate and obtain review | The two reports differ in how they describe completed versus pending verification | PR #46, #53 |
| Praise | Iterative solvers | Week 4 report states Jacobi, Gauss-Seidel, and power iteration were finalized and tested for convergence and invalid inputs | Reconcile the report's completion claim with repository evidence | The 2 Nov repository review did not find Gauss-Seidel and power iteration in the available source/branches | - |
| Deogratius | Interpolation | Updated `interpolation.hpp` with the four functions | - | Implementation only on an unmerged branch, and incomplete | `arindadeogratius-interpolation` |
| Jeremiah | Integration/RK methods | `ClassicalRK4Solver`, `GaussLegendreSolver`, `RombergSolver`; templates | - | - | PR #52 (merged) |
| Erick | Least squares, eigenvalues, satellite trajectory | Two-body model; `propagate_rk2()`, `propagate_rk4()` | Circular-orbit accuracy tests | Least squares and eigenvalues still `TODO` | PR #51 (merged) |

## 3. Individual Member Reports
The following are the member reports for their assigned modules, summarised from the individual report files.

### Gilbert (team lead):

**Assigned responsibility:** Integration, CMake and release coordination
**Source:** Week 4 team report and its repository-review notes; no separate individual Week 4 report was identified.

#### Completed

- Reviewed the `main` branch on 2 November and identified build blockers, including incorrectly named test files, duplicate Matrix sources and module-style solver files in a C++17 build.
- Identified unfinished methods recorded as TODO in the reviewed repository, including Gaussian elimination, determinant, inverse, Gauss-Seidel, power iteration, interpolation, least squares and eigenvalues.
- The team report attributes the integration patch that fixed the build and filled these gaps to the lead. This weekly summary records that attribution; it does not claim that member-owned methods were Gilbert's original implementations.

#### In Progress / Limitations

- The report did not document a clean-machine build or a coverage checklist at that review point.
- Week 5's separate contribution report provides the subsequent merge, CMake, demonstration and visual evidence: `Team Reports/Team Reports Week 5/Gilbert_week_05.md`.

### Delvin:

**Assigned responsibility:** Vectors (operator overloads)
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Implemented vector addition and subtraction, scalar multiplication and the dot product.
- Verified addition and subtraction with sample vectors, scaling with different factors, and the dot product against manual calculations.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### Repository check (lead review of the repository, 3 Nov)

- The finished operators were in `tests/test_operator overloads week 4.cpp`, which has no `main` and cannot run, while `src/vector.cpp` still threw `TODO`.

#### AI Use

- **Tool:** None declared in the individual report.
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Ibrahim:

**Assigned responsibility:** Matrix
**Branch:** `feature/ibrahim-matrix` (merged, PR #40)
**Commits:** `added semi final log cleans` (25 Oct)
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- The Matrix pull request was reviewed and merged into `main`.
- Implemented `Matrix * Vector` in `src/matrix.cpp`: one result element per matrix row; `std::invalid_argument` for an empty matrix or when the vector size differs from the number of columns.
- Added 10 tests to `tests/test_matrix.cpp` for it: 2x3 and 3x2 shapes, identity, agreement with a one-column Matrix, 1x1 and zero-vector edge cases, and invalid inputs.

#### In Progress

- Running the full build and `ctest` on his own machine.

#### Challenges / Blockers

- His computer is out of service, so the Week 3 and Week 4 Matrix code has not been built or run by him locally.
- No teammate has asked for extra Matrix functions yet.

#### Next Week

- Build and test as soon as he has a working machine or a GitHub Codespace, and fix anything that fails.

#### Repository check (lead review of the repository, 3 Nov)

- `main` compiled both `matrix.cpp` and `Matrix3.cpp` into the library (duplicate definitions, and `Matrix3.cpp` is missing a closing brace). His Week 4 file `matrix-4.cpp` compiles cleanly and passes 41 + 51 checks, so it becomes `src/matrix.cpp` in the lead's patch.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Derrick:

**Assigned responsibility:** Linear solvers
**Branch:** `Lubangakene-Derrick-Linear-solvers` (merged, PR #50)
**Commits:** `Update Derrick_Week_3_Linear_Solvers_Report.md` and others (27 Oct)
**Reviewer(s):** To be confirmed

#### Completed

- Integrated the earlier solver functions and added iterative refinement: `solveWithRefinement` gets a first solution, calculates the residual, solves for a correction and adds it until the tolerance or iteration limit is reached.
- `LinearSolver` stays the abstract base; `GaussianSolver` and `BackSubstitutionSolver` inherit from it, and `RefinementSolver` is a new derived class that overrides `solve`.
- Tests create `LinearSolver` pointers for `GaussianSolver` and `RefinementSolver` and call `solve` through the base interface (runtime polymorphism). They compare direct and refined answers, check residuals and reject a negative iteration count.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Iterative refinement may not improve every matrix.

#### Next Week

- Not stated in the individual report.

#### Repository check (lead review of the repository, 3 Nov)

- The solver classes and refinement code are not in the repository's source files: `src/linear_solvers.cpp` had only `TODO` stubs for Gaussian elimination, determinant and inverse. The C++23 module files are not part of the C++17 build. The lead's patch adds Gaussian elimination, determinant and inverse on the library's `Matrix` and `Vector`; Derrick should review them and decide how his classes use them.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Help organize the report and explain iterative refinement with inheritance and polymorphism
- **Reason it was used:** To describe the code and tests clearly
- **What the team verified or changed:** -

### Stacy:

Two Week 4 reports are present: `Team Reports/Team Reports Week 4/week-04-Stacy.md` and `Stacy-week-04.md`.

- `week-04-Stacy.md` describes LU with pivoting, Cholesky, Householder QR, and modified Gram-Schmidt, including validation and tests. It says focused decomposition tests were compiled and passed, while noting that the full-project build was blocked by an unrelated `State` compilation issue in `src/integration.cpp`.
- `Stacy-week-04.md` describes the stabilization and integration checklist, including reconstruction identities, orthogonality, invalid inputs, tolerance checks, and teammate review. It frames final testing on the current release candidate as next work.
- Repository history also records Cholesky and QR work in PR #46 and compile fixes in PR #53. These reports therefore exist; their different descriptions of verification should be reconciled before using either as a definitive test record.

### Praise:

`Team Reports/Team Reports Week 4/Praise_Week_4_iterativereport.md` is present. It states that Jacobi, Gauss-Seidel, and power iteration were finalized, tested for expected convergence and edge cases, and aligned with the shared `IterationOptions` and `IterationResult` structures. It also describes a class-layout diagram uploaded to the documentation folder and refers to a pull request awaiting approval. The report does not include exact test commands or outputs. The 2 November repository review did not find Gauss-Seidel and power iteration in the reviewed source/branches, so the claimed completion was not confirmed by that repository check.

### Deogratius:

**Assigned responsibility:** Interpolation
**Branch:** `arindadeogratius-interpolation`
**Commits:** `Create ArindaWeek4.md`, `Update interpolation.hpp` (26 Oct), `Update interpolation.cpp` (27 Oct)
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Updated `interpolation.hpp` so that it provides `lagrangeInterpolate`, `newtonDividedDifferences`, `newtonEvaluate` and `polynomialFit`, which `test_interpolation.cpp` needs.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### Repository check (lead review of the repository, 3 Nov)

- The implementation (Lagrange, Newton divided differences, Newton evaluation) is only on the unmerged branch, so `main` still has `TODO` stubs.
- That file includes `sat_trajectory/interpolation.hpp` (the folder is `satellite_trajectory`) and ends in the middle of `polynomialFit`, so it does not compile. The lead's patch uses his code with the include fixed and the last function finished the way his comment describes.
- `tests/test_interpolation.cpp` is still a placeholder; the lead's patch replaces it with 9 checks.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Jeremiah:

**Assigned responsibility:** Numerical integration
**Branch:** `feature/jeremiah-integration` (merged, PR #52)
**Commits:** `Refactor rk2_step and rk4_step function signatures` and others (2 Nov)
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- Added `ClassicalRK4Solver` as a second child of `TrajectorySolver` (overrides `compute_step` for fourth-order Runge-Kutta).
- Added a separate `QuadratureIntegrator` base class with `GaussLegendreSolver` and `RombergSolver` derived classes overriding `integrate`.
- Two class families: `BaseSolver` -> `TrajectorySolver` -> `MidpointSolver` / `ClassicalRK4Solver`, and `QuadratureIntegrator` -> `GaussLegendreSolver` / `RombergSolver`.
- The classes are templates (`template <typename T>`); the public functions use `double` instances. `time_step` is `protected` so derived solvers use it and outside code cannot change it.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### Repository check (lead review of the repository, 3 Nov)

- Checked with new tests: RK2 and RK4 steps match the exact values, RK4 reaches e to 1e-9 over 100 steps, Gaussian quadrature is exact for cubics, Romberg gives sin integral = 2 to 1e-8 (11 checks pass).
- Invalid input (empty state, non-positive step) was printed and ignored; the lead's patch makes `rk2_step` and `rk4_step` throw `std::invalid_argument` instead.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Erick:

**Assigned responsibility:** Least squares, eigenvalues and satellite trajectory
**Branch:** `feature/erick-least-squares-trajectory` (merged, PR #51)
**Commits:** `week_4`, `updated trajectory_solver.cpp` (1 Nov), `updated` (2 Nov)
**Reviewer(s):** Gilbert, Delvin, Ibrahim.

#### Completed

- Reviewed the finished vector-based RK2 and RK4 interface and updated the trajectory module to use it.
- State is `[x, y, z, vx, vy, vz]`, with conversion to and from `OrbitalState`.
- Implemented the two-body gravity model a = -mu r / |r|³ and `propagate_rk2()` and `propagate_rk4()`; kept the input validation.
- OOP: inheritance (`MidpointSolver` and `ClassicalRK4Solver` derive from `TrajectorySolver`), runtime polymorphism through `virtual compute_step` and `override`, and encapsulation of `time_step`.

#### In Progress

- Testing RK2 and RK4 on a circular Earth orbit and checking accuracy over a full period.

#### Challenges / Blockers

- The trajectory code needed the RK interface to move from scalar to vector states first.
- Both modules had to agree on a six-component state.

#### Next Week

- Circular-orbit tests; compare RK2 and RK4 accuracy; longer propagation periods; continue eigenvalues and least squares.

#### Repository check (lead review of the repository, 3 Nov)

- With the lead's examples, one orbit at 60 s steps: RK4 radius stays within 0.2 km, RK2 within 22 km (about 98 steps, a little over one orbit).
- `least_squares.cpp` and `eigenvalues.cpp` were still `TODO` on `main`; the lead's patch adds QR-based least squares and a symmetric eigenvalue method for Erick to review.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Review the updated RK interface, structure the satellite propagation implementation, verify the two-body model and identify OOP concepts in the integration design
- **Reason it was used:** To understand the numerical integration architecture and connect the trajectory module to RK2/RK4
- **What the team verified or changed:** -

## 4. Decisions Made This Week

| Decision | Reason | Affected modules/members |
|---|---|---|
| Satellite state is a six-component vector `[x, y, z, vx, vy, vz]` | One common state for RK2, RK4 and the trajectory module | Erick, Jeremiah |
| Two class families in integration: ODE solvers and quadrature solvers; template classes with `double` instances | Share validation and a virtual interface | Jeremiah, Erick |
| `RefinementSolver` added as a third derived class of `LinearSolver` | Reuse the Gaussian solver and the residual checks | Derrick |
| Lead's patch: `matrix-4.cpp` becomes the single `matrix.cpp`; `Matrix3.cpp` and the C++20 module files leave the build | The build needs one definition of each function and one language standard (C++17) | Ibrahim, Derrick, Gilbert |

## 5. Issues and Blockers Requiring Team Action

| Issue | Owner | Impact | Action before next Monday (proposed) |
|---|---|---|---|
| `main` does not configure or build: 4 test files have spaces in their names but CMake expects underscores; `matrix.cpp` and `Matrix3.cpp` are both compiled; `Matrix3.cpp` is missing a brace; module files need C++20 | Gilbert, Ibrahim, Derrick | Nobody can build or run the tests | Apply the lead's patch, pull, and run a clean build |
| Required methods not on `main`: Gaussian elimination, determinant, inverse (Derrick); Gauss-Seidel, power iteration (Praise); interpolation (Deogratius, unmerged and incomplete); least squares, eigenvalues (Erick); vector operators (Delvin) | Each owner | Methods required by the assignment are missing | Owners read the patch versions, correct them, and re-commit under their own names |
| Reports still missing at this review: Gilbert's individual Week 4 report and the Week 5 team report; Stacy and Praise Week 4 reports are present | Gilbert | Missing lead evidence and upcoming team report | Add the lead's evidence and complete the Week 5 report |
| Derrick's classes (`LinearSolver`, `RefinementSolver`) are described in reports but are not in the repository code | Derrick | Reports and code disagree | Add the classes to the C++17 library or correct the reports |
| GitHub account `Tushabepaul` has 3 commits and is not in the team list | Gilbert | Unclear contributor | Confirm whose account it is |
| Praise's Week 3 report has leftover `[cite: 8]` markers and no AI-use declaration | Praise | Report accuracy | Clean up and add the declaration |

## 6. Next Week's Shared Goals

1. Pull the latest `main`, apply the lead's patch, and confirm a clean build and `ctest` on a second machine.
2. Each member reads the patch version of their module, corrects it where needed and commits it under their own name.
3. Write the README, final report and presentation in the group's own words; keep every AI-use declaration accurate.
4. Confirm Gilbert's individual Week 4 evidence and complete the Week 5 report; reconcile the verification claims in Stacy's two Week 4 reports and Praise's report with repository/test evidence.
5. Final package, GitHub check and submission checklist by Thursday 5 November (Gilbert).

## 7. Conclusion

Week 4 delivered RK4, quadrature, Romberg, two-body propagation and Matrix * Vector. The project could not be built from `main`, and several required methods were still `TODO`; the lead's patch fixes the build and adds them, with 9 test programs that now all pass. The remaining work before 5 November is for each owner to review and commit their module, to complete the missing reports, and to write the README and final report.
