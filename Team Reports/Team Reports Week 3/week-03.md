# Week 3 Progress Report

> Team summary compiled from the Week 3 member reports and repository review. Reported work is distinguished from work verified in the integrated source.

## Completed

| Member | Module | Reported work |
|---|---|---|
| Gilbert | Integration and CMake | Coordinated merging and review; no separate Week 3 individual report was identified. |
| Delvin | Vector | Declared vector addition, subtraction, scalar multiplication and dot-product operators; the reported bodies were placeholders and pseudocode was drafted. |
| Ibrahim | Matrix | Implemented the Matrix class, constructors, access, transpose, identity, arithmetic operators and 41 checks, according to his report. |
| Derrick | Linear solvers | Reported residual checks and a polymorphic `LinearSolver` base with Gaussian and back-substitution derived classes; his report does not claim the tests were compiled or run. |
| Stacy | Decompositions | Reported design and validation requirements for LU, Cholesky, Householder QR and modified Gram-Schmidt; numerical correctness and full-project compatibility remained unverified. |
| Praise | Iterative solvers | Week 3 report describes power iteration and shared option/result types; the implementation claim was not confirmed in the reviewed repository. |
| Deogratius | Interpolation | Updated interpolation tests to use `TestResult` and `InterpolationTester`; no integrated test result was reported. |
| Jeremiah | Integration | Described `BaseSolver` → `NumericalIntegrator` → `MidpointSolver` inheritance and runtime polymorphism for RK2. |
| Erick | Least squares, eigenvalues and trajectory | Defined a six-element position/velocity state, added propagation input checks, and retained and verified the orbital-period function. |

## In Progress

- Implement vector operators and connect `Matrix * Vector` to the Vector API.
- Finish vector-state RK2/RK4 and the two-body satellite model.
- Add iterative refinement and extend the integration inheritance tree with RK4, Romberg and Gaussian quadrature.
- Align interpolation tests and implementation with the project API and build.

## Challenges / Blockers

- Vector operators were still placeholders in the report/repository review, preventing dependent vector operations.
- The RK interface and implementation were not yet aligned for vector-valued satellite states.
- Derrick's tests depended on a C++23 named-module setup, unlike the project's C++17 CMake build.
- Praise's power-iteration implementation claim was not verified in the reviewed source.

## Next Week

- Implement the vector operations and `Matrix * Vector`.
- Complete the RK methods and two-body trajectory path.
- Continue interpolation, quadrature, Romberg, polynomial fitting and eigenvalue work.

## Reports Received

Individual Week 3 reports are present for Delvin, Ibrahim, Derrick, Stacy, Praise, Deogratius, Jeremiah and Erick. Gilbert's separate individual report/integration note was not identified.

## AI Use

- The team report declares Claude assistance for CMake guidance.
- Individual AI-use statements remain as recorded in the member reports; no additional individual usage is inferred here.
