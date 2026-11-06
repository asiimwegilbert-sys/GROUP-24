# Week 3 Progress Report

**Submission:** Third submission
**Project:** Satellite Trajectory Numerical Computing Library
**Submitted work:** Reports and structure of the project.

> Report from the team lead, Gilbert after review. The member sections come from the individual reports in
> `Team Reports/`; "Repository check" lines come from the lead's review of the Git history and the code.

## 1. Weekly Summary

Week 3 added the object-oriented concepts (classes, access specifiers, inheritance, polymorphism) to the project. Jeremiah built a three-level inheritance chain for the integration module, Derrick added an abstract solver base class with two derived solvers and residual checks, Ibrahim implemented the Matrix class with 41 tests, and Delvin declared the vector operators with placeholder bodies. Erick defined the satellite state and added propagation input checks.
The main blockers are that `integration.hpp` and `integration.cpp` are not aligned, RK4 for vector states is incomplete, the vector operators are placeholders, and Derrick's tests need the C++23 module setup.
Stacy, Deogratius and Praise have now also submitted Week 3 reports (Praise's is on an unmerged branch). Only the team lead's individual report and integration note are still missing.

## 2. Team Status Overview

| Member | Assigned module | Completed this week | In progress | Blocker | Commit/PR link |
|---|---|---|---|---|---|
| Gilbert (team lead) | Integration/CMake | Editing, checking, creating and generating the csv files. | Integration of the commits and review | Some of the tests files had been named wrongly, so had to rename them. | - |
| Delvin | Vector | Operator overloads declared (`+`, `-`, scalar `*`, `dot`); placeholder bodies | Implementation | - | - |
| Ibrahim | Matrix | Matrix class implemented; `+`, `-`, `*`, scalar `*`; `test_matrix.cpp` (41 checks) | `Matrix * Vector` | Waits on the Vector class | - |
| Derrick | Linear solvers | Residual validation; `LinearSolver` base with two derived solvers; polymorphism tests | Iterative refinement (Week 4) | Needs C++23 module setup | suggested `feature/derrick-residual-validation` |
| Stacy | Decompositions | Report written (planned Cholesky, QR, Gram-Schmidt); Cholesky and QR committed 26 Oct | Compile fixes (done by Erick, 2 Nov) | Report says not yet implemented when written | `stacy-lead-matrix-decompositions` |
| Praise | Iterative solvers | Week 3 report on branch `asingwirepraise-iterative`; claims power iteration | - | Code not in any branch | - |
| Deogratius | Interpolation | Week 3 report: tests rewritten with classes (`test_interpolation3.cpp`) | - | - | `arindadeogratius-interpolation` |
| Jeremiah | Integration/RK methods | `BaseSolver` -> `NumericalIntegrator` -> `MidpointSolver`; polymorphism | RK4, Romberg and quadrature (Week 4) | - | - |
| Erick | Least squares, eigenvalues, satellite trajectory | Satellite state and propagation input checks; tests updated | Two-body dynamics; trajectory tests | RK header and source not aligned | - |

## 3. Individual Member Reports
The following are the member reports for their assigned modules, summarised from the individual report files.

### Gilbert (team lead):

The Week 3 work, the lead integrates and merges modules and remaining/ resolving conflicts.

### Delvin:

**Assigned responsibility:** Vectors (operator overloads)
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim

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

#### Repository check (lead review of the repository, 3 Nov)

- The operators were still `TODO` in `src/vector.cpp` on `main` (the finished versions came later, in `tests/`).

#### AI Use

- **Tool:** None declared in the individual report.
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Ibrahim:

**Assigned responsibility:** Matrix
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Derrick.

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

#### Repository check (lead review of the repository, 3 Nov)

- Nothing further to note.

#### AI Use

- **Tool:** None declared in the individual report.
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Derrick:

**Assigned responsibility:** Linear solvers
**Branch:** Suggested: `feature/derrick-residual-validation`.
**Commits:** Suggested: `feat: add residual validation and solver polymorphism`
**Reviewer(s):** Gilbert, Delvin.

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

#### Repository check (lead review of the repository, 3 Nov)

- Nothing further to note.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Stacy:

**Assigned responsibility:** Matrix decompositions
**Branch:** `Stacy-Elizabeth-Namuleme-patch-3` (merged), then `stacy-lead-matrix-decompositions` (PR #46, #53)
**Commits:** `Add Week 03 progress report for matrix algorithms`; `Implement Cholesky and QR decomposition functions` (26 Oct)
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Report describing how the remaining algorithms fit the plan: Cholesky (A = L·Lᵀ for symmetric positive-definite matrices), QR by Householder transformations, and modified Gram-Schmidt as another way to build an orthogonal basis.
- Explained what the tests need to check: reconstruction, orthogonality of Q, invalid inputs, and dependent columns for Gram-Schmidt.

#### In Progress

- The report says the routines were not yet implemented when it was written; it lists LU first, then Cholesky, Householder QR and modified Gram-Schmidt, each with tests.

#### Challenges / Blockers

- Numerical correctness and compatibility with the full project were still unverified when the report was written.

#### Next Week

- Implement the methods in small reviewable steps and add tests for reconstruction, orthogonality and invalid inputs.

#### Repository check (lead review of the repository, 3 Nov)

- Cholesky and QR were committed on 26 Oct (`e393157`). The first version had compile errors; Erick corrected them on 2 Nov (merged in PR #53).
- On the latest `origin/main` the decomposition file compiles and passes 15 checks written during this review (LU, Cholesky, QR, Gram-Schmidt).

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Praise:

**Assigned responsibility:** Iterative solvers
**Branch:** `asingwirepraise-iterative` (not merged into `main`)
**Commits:** `report for week 3` (24 Oct)
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Week 3 report on power iteration and OOP: the report says power iteration was added to `src/iterative_solvers.cpp`.
- OOP part: `IterationOptions` and `IterationResult` are structs with public members; `Matrix` and `Vector` keep their data private; the three solver functions share the same input and result style.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

-not sated.

#### Next Week

- Not stated in the report.

#### Repository check (lead review of the repository, 3 Nov)

- The branch contains only the report file. Power iteration and Gauss-Seidel are still `TODO` on `main` and on every branch.
- `iterative_solvers` has free functions and structs, no class hierarchy or virtual functions, so the report's inheritance and polymorphism points need to refer to code that exists.
- The report contains leftover `[cite: 8]` markers and no AI-use declaration.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Deogratius:

**Assigned responsibility:** Interpolation (tests)
**Branch:** `arindadeogratius-interpolation`
**Commits:** `Create InterpolationWk3.md` (26 Oct)
**Reviewer(s):** To be confirmed

#### Completed

- Edited and updated `test_interpolation.cpp` from Week 2 so that it uses classes with data members and member functions, as taught that week.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Not stated in the individual report.

#### Repository check (lead review of the repository, 3 Nov)

- The class-based tests are in `test_interpolation3.cpp` (`TestResult`, `InterpolationTester`); `tests/test_interpolation.cpp` on `main` is still a 5-line placeholder, and neither file was in the CMake test list.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Jeremiah:

**Assigned responsibility:** Numerical integration
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Structured the integration module with multilevel inheritance: `BaseSolver` (grandparent; input validation) -> `NumericalIntegrator` (parent; holds the virtual step function) -> `MidpointSolver` (child; overrides the step for RK2).
- Demonstrated runtime polymorphism with a base-class pointer (`NumericalIntegrator*`) pointing at a concrete child object.

#### In Progress

- Not stated in the individual report.

#### Challenges / Blockers

- Not stated in the individual report.

#### Next Week

- Add RK4, Romberg and Gaussian quadrature into the inheritance tree in Week 4.

#### Repository check (lead review of the repository, 3 Nov)

- Nothing further to note.

#### AI Use

- **Tool:** None declared in the individual report (member to confirm)
- **Purpose:** -
- **Reason it was used:** -
- **What the team verified or changed:** -

### Erick:

**Assigned responsibility:** Least squares, eigenvalues and satellite trajectory
**Branch:** -
**Commits:** -
**Reviewer(s):** Gilbert, Ibrahim.

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

#### Repository check (lead review of the repository, 3 Nov)

- Nothing further to note.

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
| Stacy's report says the decompositions were not started; the code was committed on 26 Oct and fixed on 2 Nov | Stacy, Erick | Report and code disagree | Update the report to match what was done |
| Praise's Week 3 report is on an unmerged branch and describes power iteration that is not in any branch | Praise | Report claims code that cannot be checked | Push the code or correct the report; remove `[cite: 8]` leftovers |
| No Week 3 report from Gilbert; integration note missing | Gilbert | Incomplete submission | Submit before the deadline |

## 6. Next Week's Shared Goals

1. Implement the vector operators and `Matrix * Vector`.
2. Finish the RK2/RK4 vector-state interface, then two-body propagation.
3. Complete interpolation, quadrature, Romberg, polynomial fitting and eigenvalues (Week 4 plan).
4. Collect the missing Week 3 reports and write the integration note.

## 7. Conclusion

Week 3 introduced inheritance and polymorphism in the integration and linear-solver modules and produced a tested Matrix class. All members have now submitted a Week 3 report. The remaining work is integration: aligning the RK interface, moving the vector operators into `src/vector.cpp`, and moving the solver classes onto the main library types.
