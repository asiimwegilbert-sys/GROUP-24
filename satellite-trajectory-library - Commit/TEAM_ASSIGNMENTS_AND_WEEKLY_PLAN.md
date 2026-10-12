# Team Assignments and Weekly Submission Plan

> Every member makes visible Git commits and contributes to the weekly report before the Monday of every week.

## 1. Team Responsibilities

| Member | Primary responsibility | Main files/modules | Individual evidence |
|---|---|---|---|
| Gilbert | Team lead, project integration, CMake, release coordination | `CMakeLists.txt`, `PROJECT_PLAN.md`, integration branches | Build logs, integration commits, merge coordination |
| Delvin |Lead-Vector foundation | `include/.../vector.hpp`, `src/vector.cpp`, vector tests | Vector API, operations, validation tests |
| Ibrahim |Lead-Matrix foundation | `include/.../matrix.hpp`, `src/matrix.cpp`, matrix tests | Matrix storage, indexing, arithmetic, dimension tests |
| Derrick |Lead-Direct linear solvers | `linear_solvers.hpp/.cpp`, linear-solver tests | Gaussian elimination, determinant, inverse |
| Stacy |Lead-Matrix decompositions | `decompositions.hpp/.cpp`, decomposition tests | LU, Cholesky, QR, Gram-Schmidt |
| Praise |Lead-Iterative numerical methods | `iterative_solvers.hpp/.cpp`, iterative-solver tests | Jacobi, Gauss-Seidel, power iteration |
| Deogratious |Lead-Interpolation methods | `interpolation.hpp/.cpp`, interpolation tests | Lagrange, Newton, polynomial interpolation |
| Jeremiah |Lead-Numerical integration | `integration.hpp/.cpp`, integration tests | RK2, RK4, Gaussian quadrature, Romberg integration |
| Erick |Lead- Least squares, eigenvalues, and satellite application | `least_squares`, `eigenvalues`, `trajectory_solver`, `examples/` | Fitting, eigenvalues, two-body propagation, examples |

### Shared responsibilities

- **All members:** review at least one other member's code each week.
- **All members:** write and maintain tests for their own modules.
- **All members:** understand the complete project, not only their assigned method.
- **Gilbert:** does not own all code review; the lead coordinates integration and release readiness.
- **Erick:** owns the satellite demonstration but depends on Delvin, Ibrahim, and Jeremiah for vector, matrix, and RK support, also he is free to assign members to help him where necessary.

## 2. Working Rules

1. Create one feature branch per member, for example `feature/member-02-vector`.
2. Make small focused commits; do not wait until the end of the week.
3. Use commit messages such as `feat: add vector norm` or `test: cover singular matrix case`.
4. Open a pull request for significant changes.
5. A module is not considered complete until its tests pass and another member reviews it.
6. Do not silently change another member's public API; discuss changes first.
7. Record blockers in the weekly report before the Monday checkpoint.
8. Keep the README and final report in the group's own words, as required by the instructions.

## 3. Weekly Submission Calendar

The project timeline starts on Sunday, October 4, 2026. Weekly work is submitted before each Monday checkpoint.

| Week | Submission checkpoint | Main objective | Required team submission |
|---|---|---|---|
| Week 1 | Before Mon, Oct 5 | Confirm design and ownership | Architecture decision, branch setup, interface review, individual plans |
| Week 2 | Before Mon, Oct 12 | Complete foundations and direct solvers | Vector, Matrix, Gaussian elimination, determinant, inverse, first tests |
| Week 3 | Before Mon, Oct 19 | Complete decompositions and iterative methods | LU, Cholesky, QR, Gram-Schmidt, Jacobi, Gauss-Seidel, power iteration |
| Week 4 | Before Mon, Oct 26 | Complete interpolation, integration, fitting, and eigenvalues | All remaining general numerical methods with tests |
| Week 5 | Before Mon, Nov 2 | Integrate satellite application and stabilize library | RK2/RK4 trajectory propagation, examples, full test run, documentation draft |
| Final | Thu, Nov 5 | Submit and present complete project | Final source package, reports, final README, AI declaration, GitHub repository |

## 4. Individual Weekly Deliverables

### Week 1 — before Monday, October 5

**Everyone submits:**

- One short design note explaining their assigned module.
- A feature branch with at least one meaningful planning or interface commit.
- A list of questions, assumptions, and validation rules.
- Their section for `reports/week-0x.md`.

**Member-specific outputs:**

- **Gilbert:** final repository tree, CMake target plan, branch/PR convention.
- **Delvin:** proposed `Vector` API and behavior for invalid indices and size mismatches.
- **Ibrahim:** proposed `Matrix` API, storage layout, and dimension rules.
- **Derrick:** Gaussian-elimination algorithm notes and singular-matrix policy.
- **Stacy:** decomposition input requirements and expected output structures.
- **Praise:** convergence criteria and iteration-result format.
- **Deogratious:** interpolation input validation and coefficient representation.
- **Jeremiah:** RK and quadrature interface notes, step-size conventions.
- **Erick:** least-squares and eigenvalue method notes, tolerance policy.
- **Erick:** orbital state format, units, gravitational parameter, and trajectory example plan.

### Week 2 — before Monday, October 12

**Target:** Make the library foundation usable.

- **Gilbert:** configure CMake for all current source and test files; run a clean build.
- **Delvin:** implement `Vector`, vector arithmetic, dot product, norm, and tests.
- **Ibrahim:** implement `Matrix`, indexing, transpose, identity, and basic operations.
- **Derrick:** implement Gaussian elimination, determinant, and inverse using the shared matrix type.
- **Stacy:** review matrix API compatibility and prepare decomposition test fixtures.
- **Praise:** prepare convergence utilities and test matrices for iterative solvers.
- **Deogratious:** write interpolation test data and edge-case tests while the implementation is developed.
- **Jeremiah:** write RK2/RK4 and integration test functions with known analytical results.
- **Erick:** prepare least-squares and eigenvalue examples and expected-result calculations.
- **Erick:** create orbital-state validation tests and the initial satellite example skeleton.

**Required Monday submission:**

- Updated source and tests for completed work.
- `reports/week-02.md` with completed, in-progress, blockers, next week, and AI-use sections.
- Build output or test evidence attached to the pull request.

### Week 3 — before Monday, October 19

**Target:** Complete core linear algebra and iterative methods.

- **Gilbert:** merge reviewed branches, resolve API conflicts, and publish an integrated build.
- **Delvin:** add vector edge-case tests and support any matrix/vector interface corrections.
- **Ibrahim:** finish matrix multiplication, matrix-vector multiplication, and dimension validation.
- **Derrick:** add pivoting, singularity checks, and direct-solver regression tests.
- **Stacy:** implement LU, Cholesky, QR, and Gram-Schmidt with reconstruction/orthogonality tests.
- **Praise:** implement Jacobi, Gauss-Seidel, and power iteration with convergence and non-convergence tests.
- **Deogratious:** complete interpolation implementation if blocked; otherwise review solver modules.
- **Jeremiah:** complete RK2/RK4 scalar-step implementations and validate order behavior.
- **Erick:** implement least-squares solution support using the available decomposition API.
- **Erick:** connect orbital state data to the RK interface without yet requiring the final propagator.

**Required Monday submission:**

- Passing tests for completed linear-algebra and iterative modules.
- Pull requests reviewed by at least one other member.
- Updated `reports/week-03.md`.
- A short integration note from Gilbert describing merged modules and remaining conflicts.

### Week 4 — before Monday, October 26

**Target:** Complete the remaining numerical coverage.

- **Gilbert:** run a clean-environment build and create a coverage checklist against the assignment list.
- **Delvin:** review numerical APIs for consistent error handling and tolerance use.
- **Ibrahim:** optimize or correct matrix operations needed by fitting and trajectory code.
- **Derrick:** verify direct solvers on edge cases and document singular-input behavior.
- **Stacy:** finish decomposition stability tests and document assumptions such as positive definiteness.
- **Praise:** finish iterative-solver stopping conditions and iteration-result reporting.
- **Deogratious:** implement and test Lagrange, Newton, and polynomial interpolation.
- **Jeremiah:** implement Gaussian quadrature and Romberg integration; complete integration tests.
- **Erick:** complete polynomial least-squares fitting and eigenvalue computation.
- **Erick:** prepare trajectory output format and example data path under `data/`.


### Week 5 — before Monday, November 2

**Target:** Integrate and stabilize the full application.

- **Gilbert:** freeze the public API, run full clean build/test, and prepare release branch.
- **Delvin:** perform vector/matrix API review and fix integration regressions.
- **Ibrahim:** perform matrix performance and dimension-validation review.
- **Derrick:** review all direct-solver failure cases and exception messages.
- **Stacy:** verify decomposition identities and numerical tolerances.
- **Praise:** verify convergence behavior and document iteration limits.
- **Deogratious:** add a trajectory-sample interpolation demonstration.
- **Jeremiah:** implement/finish the satellite RK2 and RK4 propagation path with Erick.
- **Erick:** add a parameter-estimation or trajectory-fitting example using least squares.
- **Erick:** finish the two-body satellite trajectory example and output a readable trajectory result.

**Required Monday submission:**

- Fully integrated project on the release branch.
- `ctest --test-dir build --output-on-failure` results.
- Completed examples that demonstrate the library.
- README draft covering build, use, structure, examples, limitations, and contributions.
- Updated `reports/week-05.md`.

### Final week — November 2 to November 5

**Everyone:**

- Review the final branch.
- Confirm that your commits and contribution are visible in Git history.
- Read enough of the entire project to explain it during the presentation.
- Submit your personal contribution summary to Gilbert.
- Verify that your AI-use declaration is accurate.

**Gilbert:** final packaging, GitHub repository check, clean-machine build, and submission checklist.

**Delvin:** final Vector/Matrix API explanation for the presentation.

**Ibrahim:** final matrix data-structure and dimension-validation explanation.

**Derrick:** direct-solver explanation and edge-case demonstration.

**Stacy:** decomposition explanation and numerical-stability discussion.

**Praise:** iterative-method convergence explanation.

**Deogratious:** interpolation demonstration.

**Jeremiah:** integration and RK2/RK4 demonstration.

**Erick:** least-squares/eigenvalue demonstration.

**Erick:** satellite trajectory demonstration and application explanation.

## AI usage:
We used AI to create an orgainised plan after we assigned and also made a rough work for this plan. 
