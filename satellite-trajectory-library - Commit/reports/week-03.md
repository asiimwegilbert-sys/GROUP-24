# Week 3 Progress Report

> The team lead's report after review and edit. Member summaries come from the individual reports in
> `Team Reports/Team Reports Week 3/`. 
> Next Week items also follow `TEAM_ASSIGNMENTS_AND_WEEKLY_PLAN.md`.

## Completed
| Member | Module | Completed this week (object-oriented work and implementation) |
|---|---|---|
| Gilbert (lead) | Integration, CMake | Did the merging and reviewing |
| Delvin | Vector | Declared operator overloads for vector `+`, `-`, scalar `*` and `dot`; placeholder bodies throw `std::logic_error`; pseudocode drafted |
| Ibrahim | Matrix | Implemented the `Matrix` class (three constructors, `rows`, `columns`, checked access, `transpose`, `identity`) and the operators `+`, `-`, matrix `*` and scalar `*`; `std::invalid_argument` and `std::out_of_range` errors; `tests/test_matrix.cpp` with 41 checks |
| Derrick | Linear solvers | Residual validation (`calculateResidual`, `residualNorm`, `isSolutionAccurate`); abstract base class `LinearSolver` with pure virtual `solve`; `GaussianSolver` and `BackSubstitutionSolver` derived from it; polymorphism tested through `std::unique_ptr<LinearSolver>` |
| Stacy | Decompositions | Reported the design and validation requirements for LU, Cholesky, Householder QR, and modified Gram-Schmidt; numerical correctness and full-project compatibility remained unverified in her report |
| Praise | Iterative solvers | Week 3 report describes power iteration and `IterationOptions`/`IterationResult`; the report claims code was added, but the reviewed repository did not confirm an implementation |
| Deogratius | Interpolation | Updated the interpolation tests to use `TestResult` and `InterpolationTester` classes in `test_interpolation3.cpp`; no project-integrated test result was reported |
| Jeremiah | Integration (RK) | Three-level inheritance: `BaseSolver` (input validation) -> `NumericalIntegrator` (virtual `compute_step`) -> `MidpointSolver` (overrides it for RK2); runtime polymorphism shown through a base-class pointer |
| Erick | Least squares, eigenvalues, trajectory | Defined the satellite state as 3D position and velocity; added propagation input checks (state sizes, positive time step, steps and gravitational parameter) with tests; kept and verified the orbital period function |

## In Progress
- `Matrix * Vector` waits on the Vector class so the two APIs match (Ibrahim).
- Two-body orbital dynamics and circular-orbit tests (Erick).
- Iterative refinement as another solver implementation (Derrick, Week 4).
- Adding RK4, Romberg and Gaussian quadrature to the inheritance tree (Jeremiah, Week 4).

## Challenges/Blockers
- `integration.hpp` and `integration.cpp` are not yet aligned, and RK4 for vector states is incomplete, so `propagate_rk2()` and `propagate_rk4()` cannot be finished (Erick).
- Derrick's tests need the team's C++23 named-module setup, which differs from the C++17 CMake build; his report does not claim the tests were compiled or run.
- The vector operators are still placeholders, so anything that adds or scales vectors cannot work yet.

## Solved.
- The team lead was told to edit the CMake file so as to be able to handle C++17 and above

## Next Week
- Implement the vector operators and `Matrix * Vector`.
- Finish RK2/RK4 for vector states, then the two-body model and satellite propagation (Erick, Jeremiah).
- Interpolation, Gaussian quadrature, Romberg, polynomial fitting and eigenvalues, per the Week 4 plan.

## AI Use
- **Tool:** Claude (Anthropic)
- **Purpose:** Was used to show how to create and implement the CMake files.
- Members' own AI use is declared in their individual reports (for example, Erick used ChatGPT).

## Reports received
Individual reports are present for Delvin, Ibrahim, Derrick, Stacy, Praise, Deogratius, Jeremiah, and Erick. Gilbert's separate individual report/integration note is not identified. Praise's report describes power iteration, but its implementation was not verified in the reviewed repository; this summary distinguishes the report's claim from merged, tested code.
