# Week 1 Progress Report – Erick

**Assigned Module:** Least Squares, Eigenvalue Computation, and Satellite Trajectory

# Completed

* created the feature branch `feature/erick-least-squares-trajectory`.
* Reviewed the project structure, assigned modules, and their dependencies.
* Implemented orbital period calculation in `src/trajectory_solver.cpp` using (T = 2π√(a³/μ)), including input validation.
* Added tests in `tests/test_trajectory.cpp` covering:
  - Normal orbital period calculation.
  - Invalid negative semi-major axis.
  - Invalid zero gravitational parameter.
* Configured CMake with MinGW, successfully built the project, and passed all 8 registered tests.
* Committed the changes 

# In Progress

* Reviewing least-squares and polynomial fitting implementation.
* Exploring eigenvalue computation methods.
* Coordinating dependencies with the QR decomposition, linear solver, and numerical integration modules.

# Challenges / Blockers

* Least-squares and eigenvalue implementations depend on QR decomposition and linear solver components still under development.
* The existing RK2/RK4 functions support scalar values, while satellite trajectory propagation requires vector-based states.
* Initial CMake and MinGW configuration required troubleshooting.

# Next Week

* Coordinate with team members to finalize module interfaces.
* Begin least-squares implementation once dependencies are ready.
* Confirm the approach for eigenvalue computation and satellite trajectory integration.
* Continue writing tests and review another team member's pull request.

# AI Use

**AI** ChatGPT

Used to understand project requirements, Git/GitHub workflows, module dependencies, numerical methods, CMake/MinGW setup, and test design.

All AI suggestions were reviewed and verified before implementation.
