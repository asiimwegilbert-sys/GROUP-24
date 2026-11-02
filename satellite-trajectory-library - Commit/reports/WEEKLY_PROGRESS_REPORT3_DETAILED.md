# Week 3 Progress Report

**Submission:** First submission
**Project:** Satellite Trajectory Numerical Computing Library
**Submitted work:** Reports and structure of the project.

> DRAFT for the team lead (Gilbert) to review. The member sections are taken from the individual reports in
> `Team Reports/`. Where a report says nothing, this document says so instead of guessing.

## 1. Weekly Summary

Week 3 added the object-oriented concepts (classes, access specifiers, inheritance, polymorphism) to the project. Jeremiah built a three-level inheritance chain for the integration module, Derrick added an abstract solver base class with two derived solvers and residual checks, Ibrahim implemented the Matrix class with 41 tests, and Delvin declared the vector operators with placeholder bodies. Erick defined the satellite state and added propagation input checks.
The main blockers are that `integration.hpp` and `integration.cpp` are not aligned, RK4 for vector states is incomplete, the vector operators are placeholders, and Derrick's tests need the C++23 module setup.
No Week 3 report was received from Gilbert, Stacy, Praise or Deogratius.

## 2. Team Status Overview

| Member | Assigned module | Completed this week | In progress | Blocker | Commit/PR link |
|---|---|---|---|---|---|
| Gilbert (team lead) | Integration/CMake | No individual report or integration note received | Integration of the commits and review | - | - |
| Delvin | Vector | Operator overloads declared (`+`, `-`, scalar `*`, `dot`); placeholder bodies | Implementation | - | - |
| Ibrahim | Matrix | Matrix class implemented; `+`, `-`, `*`, scalar `*`; `test_matrix.cpp` (41 checks) | `Matrix * Vector` | Waits on the Vector class | - |
| Derrick | Linear solvers | Residual validation; `LinearSolver` base with two derived solvers; polymorphism tests | Iterative refinement (Week 4) | Needs C++23 module setup | suggested `feature/derrick-residual-validation` |
| Stacy | Decompositions | No individual report received | - | - | - |
| Praise | Iterative solvers | No individual report received | - | - | - |
| Deogratius | Interpolation | No individual report received (`test_interpolation3.cpp` is in the repo root) | - | - | - |
| Jeremiah | Integration/RK methods | `BaseSolver` -> `NumericalIntegrator` -> `MidpointSolver`; polymorphism | RK4, Romberg and quadrature (Week 4) | - | - |
| Erick | Least squares, eigenvalues, satellite trajectory | Satellite state and propagation input checks; tests updated | Two-body dynamics; trajectory tests | RK header and source not aligned | - |

## 3. Individual Member Reports
The following are the member reports for their assigned modules, summarised from the individual report files.

### Gilbert (team lead):

No individual report or integration note received. The Week 3 plan asks the lead for a short integration note on merged modules and remaining conflicts.

### Delvin:

**Assigned responsibility:** Vectors (operator overloads)
**Branch:** -
**Commits:** -
**Reviewer(s):** To be confirmed

#### Completed

- Declared operator overloads for vector addition, subtraction, scalar multiplication and dot product.
- Added placeholder implementations that throw `std::logic_error`; outlined the mathematical definitions and drafted pseudocode for addition and dot product.
- Reflection: declaring operators early keeps the design clear and lets teammates plan how vectors interact in trajectory code.

#### In Progress

- Implementations are pending.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Ibrahim:

**Assigned responsibility:** Matrix
**Branch:** -
**Commits:** -
**Reviewer(s):** To be confirmed

#### Completed

- Implemented the `Matrix` class declared in `matrix.hpp`: default, sized and nested initializer-list constructors; `rows()`, `columns()`; checked element access with `operator()`; `transpose()`; `identity(size)`.
- Implemented `+`, `-`, matrix `*` matrix and `double * Matrix`.
- Error handling: `std::invalid_argument` for zero-size matrices, rows of different lengths and mismatched sizes; `std::out_of_range` for invalid indices.
- Wrote `tests/test_matrix.cpp` (41 checks: normal cases, edge cases such as 1x1 and row/column vectors, and invalid inputs). File names checked against the group CMakeLists.

#### In Progress

- `Matrix * Vector` is declared in the header; the implementation waits until the Vector class is merged so the two APIs match.

#### Challenges / Blockers

- Waiting on the Vector class.

#### Next Week

- Implement `Matrix * Vector`.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Derrick:

**Assigned responsibility:** Linear solvers
**Branch:** Suggested: `feature/derrick-residual-validation` (not confirmed created)
**Commits:** Suggested: `feat: add residual validation and solver polymorphism`
**Reviewer(s):** To be confirmed

#### Completed

- Residual validation: `calculateResidual` (r = b − A·x), `residualNorm`, `isSolutionAccurate`.
- Inheritance: abstract base class `LinearSolver` with a pure virtual `solve`; `GaussianSolver` and `BackSubstitutionSolver` derive from it and override `solve`.
- Polymorphism: tests store derived objects in `std::unique_ptr<LinearSolver>` and call `solve` through the base pointer.
- Tests cover known answers, polymorphic calls, residual checks and an inaccurate solution. The report does not claim they were compiled or run.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Tests must be compiled with the team's C++23 named-module setup.

#### Next Week

- Week 4: iterative refinement as another solver implementation.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Stacy:

No individual report received.

### Praise:

No individual report received.

### Deogratius:

No individual report received. A file `test_interpolation3.cpp` (classes `TestResult` and `InterpolationTester`) is in the repository root and may be his Week 3 work.

### Jeremiah:

**Assigned responsibility:** Numerical integration
**Branch:** -
**Commits:** -
**Reviewer(s):** To be confirmed

#### Completed

- Structured the integration module with multilevel inheritance: `BaseSolver` (grandparent; input validation) -> `NumericalIntegrator` (parent; holds the virtual step function) -> `MidpointSolver` (child; overrides the step for RK2).
- Demonstrated runtime polymorphism with a base-class pointer (`NumericalIntegrator*`) pointing at a concrete child object.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Add RK4, Romberg and Gaussian quadrature into the inheritance tree in Week 4.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Erick:

**Assigned responsibility:** Least squares, eigenvalues and satellite trajectory
**Branch:** -
**Commits:** -
**Reviewer(s):** To be confirmed

#### Completed

- Reviewed the updated RK2/RK4 work, which is being extended from scalar to vector states, and identified the remaining mismatch between `integration.hpp` and `integration.cpp`.
- Defined the satellite state as 3D position and velocity.
- Added validation for propagation inputs (position/velocity size, positive time step, non-zero steps, positive gravitational parameter) and updated the trajectory tests.
- Kept and verified the orbital period calculation.

#### In Progress

- Two-body orbital dynamics; circular-orbit tests; waiting for the RK2/RK4 vector-state interface to be finalized.

#### Challenges / Blockers

- The RK header and source files are not yet fully aligned.
- RK4 vector-state propagation is incomplete, so `propagate_rk2()` and `propagate_rk4()` cannot be finalized.

#### Next Week

- Finalize integration with the RK2/RK4 vector interface; implement the two-body gravity model; complete propagation with RK2 and RK4; run accuracy and circular-orbit tests.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Review the RK interface, identify integration issues, design trajectory validation and prepare trajectory test cases
- **Reason it was used:** To support understanding of the numerical integration requirements and organize the trajectory implementation
- **What the team verified or changed:** -

## 4. Decisions Made This Week

| Decision | Reason | Affected modules/members |
|---|---|---|
| Operator overloads declared first, with placeholder bodies | Fix the design early so teammates can plan around it | Delvin; vector users |
| Multilevel inheritance for the integration module (`BaseSolver` -> `NumericalIntegrator` -> `MidpointSolver`) | Meet the week's object-oriented targets and share validation | Jeremiah, Erick |
| Abstract `LinearSolver` base class with `GaussianSolver` and `BackSubstitutionSolver` | Call solvers polymorphically | Derrick |
| Satellite state is 3D position and velocity | Needed for propagation | Erick, Jeremiah |

## 5. Issues and Blockers Requiring Team Action

| Issue | Owner | Impact | Action before next Monday (proposed) |
|---|---|---|---|
| `integration.hpp` and `integration.cpp` do not match; RK4 for vector states is incomplete | Jeremiah, Erick | Satellite propagation cannot be finished | Agree one RK interface and align header and source |
| Derrick's tests need the C++23 named-module setup, but the project builds as C++17 | Derrick, Gilbert | Solver tests cannot run with the project | Port to the main `sat::num` types and C++17 |
| Vector operators are placeholders; `Matrix * Vector` waits on them | Delvin, Ibrahim | Vector and matrix arithmetic unusable | Implement the operators, then `Matrix * Vector` |
| No Week 3 report from Gilbert, Stacy, Praise, Deogratius; integration note missing | Gilbert, Stacy, Praise, Deogratius | Incomplete submission | Submit before the deadline |

## 6. Next Week's Shared Goals

1. Implement the vector operators and `Matrix * Vector`.
2. Finish the RK2/RK4 vector-state interface, then two-body propagation.
3. Complete interpolation, quadrature, Romberg, polynomial fitting and eigenvalues (Week 4 plan).
4. Collect the missing Week 3 reports and write the integration note.

## 7. Conclusion

Week 3 introduced inheritance and polymorphism in the integration and linear-solver modules and produced a tested Matrix class. The remaining work is mostly integration: aligning the RK interface, implementing the vector operators and moving the solver classes onto the main library types. Four members have not yet submitted Week 3 reports.
