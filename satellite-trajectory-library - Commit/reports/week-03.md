# Week 3 Progress Report

> DRAFT for the team lead (Gilbert) to review and edit. Member summaries come from the individual reports in
> `Team Reports/Team Reports Week 3/` (plus Ibrahim's `Week 3 rpt Ibrahim-matrices.md`). Next Week items also
> follow `TEAM_ASSIGNMENTS_AND_WEEKLY_PLAN.md`.

## Completed
| Member | Module | Completed this week (object-oriented work and implementation) |
|---|---|---|
| Gilbert (lead) | Integration, CMake | No individual report or integration note received yet |
| Delvin | Vector | Declared operator overloads for vector `+`, `-`, scalar `*` and `dot`; placeholder bodies throw `std::logic_error`; pseudocode drafted |
| Ibrahim | Matrix | Implemented the `Matrix` class (three constructors, `rows`, `columns`, checked access, `transpose`, `identity`) and the operators `+`, `-`, matrix `*` and scalar `*`; `std::invalid_argument` and `std::out_of_range` errors; `tests/test_matrix.cpp` with 41 checks |
| Derrick | Linear solvers | Residual validation (`calculateResidual`, `residualNorm`, `isSolutionAccurate`); abstract base class `LinearSolver` with pure virtual `solve`; `GaussianSolver` and `BackSubstitutionSolver` derived from it; polymorphism tested through `std::unique_ptr<LinearSolver>` |
| Stacy | Decompositions | No Week 3 report received yet |
| Praise | Iterative solvers | No Week 3 report received yet |
| Deogratius | Interpolation | No Week 3 report received yet. `test_interpolation3.cpp` (classes `TestResult` and `InterpolationTester`) is in the repository root. |
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

## Next Week
- Implement the vector operators and `Matrix * Vector`.
- Finish RK2/RK4 for vector states, then the two-body model and satellite propagation (Erick, Jeremiah).
- Interpolation, Gaussian quadrature, Romberg, polynomial fitting and eigenvalues, per the Week 4 plan.

## AI Use
- **Tool:** Claude (Anthropic)
- **Purpose:** Summarising the members' individual Week 3 reports into this team report.
- **What was changed:** 
- Members' own AI use is declared in their individual reports (for example, Erick used ChatGPT).

## Reports received
Delvin, Ibrahim, Derrick, Jeremiah, Erick. 
Not yet received: Stacy, Praise, Deogratius.
