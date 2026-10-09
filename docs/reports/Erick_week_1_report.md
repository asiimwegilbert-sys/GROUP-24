# Week 1 Progress Report – Erick

## Assigned Module
Least Squares, Eigenvalue Computation, and Satellite Trajectory

## Completed



- Created and published my feature branch:
  `feature/erick-least-squares-trajectory`.
- Reviewed the existing project structure and the interfaces for:
  - Matrix and Vector classes
  - Linear solvers
  - Matrix decompositions
  - Least-squares methods
  - Eigenvalue computation
  - Numerical integration
  - Satellite trajectory propagation
- Identified the main dependencies for my assigned modules:
  - Least-squares solution depends on Matrix operations and the linear solver / QR decomposition modules.
  - Eigenvalue computation is expected to depend on the QR decomposition module.
  - Satellite trajectory propagation depends on the Runge-Kutta integration functionality.
- Identified an interface issue between the current scalar RK2/RK4 integration functions and the satellite trajectory state, which contains vector position and velocity.
- Implemented the orbital period calculation in `src/trajectory_solver.cpp` using:

  T = 2π√(a³/μ)

  where:
  - `a` is the semi-major axis.
  - `μ` is the gravitational parameter.

- Added validation to reject non-positive semi-major axis and gravitational parameter values.
- Added tests in `tests/test_trajectory.cpp` covering:
  - Normal orbital period calculation.
  - Invalid negative semi-major axis.
  - Invalid zero gravitational parameter.
- Configured CMake to build using the MinGW toolchain.
- Successfully built the project and ran the complete test suite.
- All 8 registered tests passed successfully.
- Committed the work with:

  `feat: implement orbital period calculation`

- Opened Pull Request #8 for review:
  `feat: implement orbital period calculation`

## In Progress

- Reviewing the design of the least-squares solution and polynomial fitting functions.
- Coordinating how the least-squares module will use the QR decomposition and/or linear solver modules.
- Reviewing the intended method for computing all eigenvalues.
- Reviewing how the satellite trajectory solver will interface with the RK2/RK4 integration module.

## Challenges / Blockers

- The QR decomposition and linear solver implementations are currently still under development. This limits implementation of the least-squares solution.
- Eigenvalue computation is also dependent on the QR decomposition implementation.
- The current generic RK2/RK4 interface accepts a scalar `double` state, while satellite propagation requires a coupled state containing position and velocity vectors. The team needs to agree on how this interface will be handled before trajectory propagation is finalized.
- Initial local build setup required configuration of CMake and the MinGW build toolchain.

## Next Week

- Follow up with the decomposition and linear solver module owners on the required interfaces.
- Agree on the approach to be used for least-squares solution, particularly the use of QR decomposition.
- Begin implementation of least-squares functionality once the required upstream interfaces are stable.
- Confirm the numerical method and interface for eigenvalue computation.
- Agree with the integration module owner on how RK2/RK4 will support the satellite state.
- Continue adding tests together with each implemented feature.
- Review at least one other team member's pull request.

## AI Use

- **Tool:** ChatGPT
- **Purpose:** Used to clarify the project requirements, review module dependencies, troubleshoot CMake/MinGW setup, and assist in designing tests for the orbital period calculation.
- **Reason:** To support understanding of the project architecture and development workflow, identify integration issues early, and verify the logic of the implementation and testing approach.

All AI-generated suggestions were reviewed and checked before being applied to the project.