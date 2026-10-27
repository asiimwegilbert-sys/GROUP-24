# Week 1 Progress Report

> DRAFT for the team lead (Gilbert) to review and edit. The member summaries below are taken from the
> individual reports in `Team Reports/Team Reports Week 1/` and the team's existing Week 1 notes.

## Completed
- Created the initial library scaffold.
- Assigning tasks to group members and taking initial investigations about the project.
- Chose the satellite trajectory project by group poll, after comparing the proposals (see the detailed Week 1 report).
- Each member wrote a design or progress report for their assigned module:

| Member | Module | Completed this week | Branch / PR |
|---|---|---|---|
| Gilbert (lead) | Integration, CMake | Scaffold, task assignment, CMake file, plan and workflow drafted | - |
| Delvin | Vector | Report on the `sat::num::Vector` class: three constructors, `size`, `operator[]`, `norm`, private `values_` | - |
| Ibrahim | Matrix | Matrix API proposal; row-major `std::vector<double>` storage; zero-based indexing; dimension rules for `+`, `-`, `*`; list of invalid inputs and draft validation cases | - |
| Derrick | Linear solvers | First version of the module (C++23 named module): back substitution, forward substitution, size checks, small-diagonal check, simple test program | `feature/derrick-linear-solvers`; `feat: add basic linear solver functions` |
| Stacy | Decompositions | Design note: LU with partial pivoting, Cholesky, Modified Gram-Schmidt, Householder QR; API, error handling, test plan | `feature/stacy-decompositions` |
| Praise | Iterative solvers | Header and source split; result type (solution, iterations, convergence, residual); Jacobi method implemented with size and zero-diagonal checks; iteration limit and tolerance | - |
| Deogratius | Interpolation | No Week 1 report received yet | - |
| Jeremiah | Integration (RK) | Designed `integration.hpp`: RK2, RK4, Gaussian quadrature and Romberg signatures; folders and namespace set up | - |
| Erick | Least squares, eigenvalues, trajectory | Reviewed module interfaces and dependencies; implemented the orbital period `T = 2π√(a³/μ)` with input validation; 3 tests in `tests/test_trajectory.cpp`; MinGW build set up; all 8 registered tests passed | `feature/erick-least-squares-trajectory`; PR #8; `feat: implement orbital period calculation` |

## In Progress
- Agreeing on interfaces and numerical conventions.
- Design assumptions, establishing vectors.
- Gauss-Seidel and power iteration (planned in Praise's design).
- Implementation of Cholesky, QR and Gram-Schmidt from Stacy's design.
- Mathematical loops inside `integration.cpp` (Jeremiah).

## Challenges/Blockers
- We were assigned the group late so we didnt have the time to build the foundation part from scratch so we opted for the AI to help us with the layout.
- We had initially done the work for group 9, but later had to switch which disorgainsed the group, hence we didnt do part of the work we had expected to do and complete by the end of week 1.
- When making the CMake file, I had to consult and also we where not sure how to exactly make it.
- The RK2/RK4 interface takes a single `double` state, but satellite propagation needs a state with position and velocity vectors. The group has to agree how to handle this before propagation is finalized (Erick).
- The local build needed CMake and MinGW set up before the tests could run (Erick).

## Next Week
- Implement and test vector and matrix foundations.
- Direct solvers.
- Agree the least-squares approach (QR) and the RK state interface with the module owners (Erick).
- Start the numerical loops in `integration.cpp` (Jeremiah).
- Open pull requests and assign reviewers for the Week 1 branches.

## AI Use
- **Tool:** Manus AI
- **Purpose:** Creating the frame, structure and blueprint, and also to organise the workflow of our project.
- **Reason:** To provide a structure for the group to review and complete, since we didnt know some of the work required, like the src, and also how to present the frame of the project. It made the layout just like it was needed.
- **What was changed:** We included our CMake file, report status, team assignments, and also edited the workflow to allign with our needs and proposals.
- **Tool:** Claude (Anthropic)
- **Purpose:** Filling the gaps in this team report by summarising the members' individual reports.
- **What was changed:** 
- Members' own AI use is declared in their individual reports (for example, Erick used ChatGPT).

## Implementation and Integration Status (end of Week 1)
| **Area** | **Status** | **Notes** |
|---|---|---|
| Vector and Matrix foundations | In progress | Vector and Matrix API designs written |
| Gaussian elimination, determinant, inverse | In progress | Back and forward substitution started (Derrick) |
| LU, Cholesky, QR, Gram-Schmidt | Design done | Design note and API written; no code yet (Stacy) |
| Jacobi, Gauss-Seidel, power iteration | In progress | Jacobi implemented; the other two planned (Praise) |
| Interpolation methods | Not started | No Week 1 report received |
| RK2, RK4, Gaussian quadrature, Romberg | In progress | Header signatures designed (Jeremiah) |
| Least-squares methods | Not started | Dependencies identified (Erick) |
| Eigenvalue computation | Not started | Expected to depend on QR (Erick) |
| Satellite trajectory propagation | In progress | Orbital period done; propagation not started (Erick) |
| Examples and data | Not started | |
| README and documentation | Not started | |
| Full build and test suite | In progress | Erick's local build ran 8 registered tests, all passing |
