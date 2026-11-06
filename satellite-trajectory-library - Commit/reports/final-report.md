# Final Report

## Problem and Objectives

The project implements a reusable C++ numerical-computing library and demonstrates its use in satellite trajectory analysis. Its objectives are to provide foundational vector and matrix operations, common numerical methods, tests for the public functionality, and examples that show how the methods can be combined.

## Library Design

The public interfaces are under `include/satellite_trajectory/`, implementations are under `src/`, tests are under `tests/`, and runnable demonstrations are under `examples/`. CMake builds the library, registered tests, and configured examples using C++17.

The library includes vector and matrix types, interpolation, iterative and direct solvers, matrix decompositions, least-squares and eigenvalue methods, numerical integration, and satellite propagation. The direct linear-solver module also exposes templated solver classes in the `sat_trajectory` namespace; this interface is distinct from the `sat::num` Matrix and Vector API.

## Numerical Methods

The implemented and exercised methods include:

- Vector arithmetic and dot products; matrix arithmetic, matrix-vector multiplication, transpose, and identity.
- Lagrange and Newton interpolation and polynomial interpolation.
- Gaussian elimination and related solver classes, iterative refinement, Jacobi, Gauss-Seidel, and power iteration.
- LU decomposition with pivoting, Cholesky decomposition, Householder QR, and modified Gram-Schmidt.
- Least-squares solution and polynomial fitting, and QR-based eigenvalue computation.
- RK2/RK4 integration, Gaussian quadrature, and Romberg integration.

The tests cover representative known answers, reconstruction and orthogonality identities, and selected invalid inputs. Passing these tests is useful evidence of correctness for the tested cases; it is not a proof of numerical accuracy for every input or a substitute for broader scientific validation.

## Satellite Application

The satellite module propagates position and velocity states using RK methods and a two-body gravity model. The trajectory example displays propagated orbit samples. A separate trajectory-interpolation example uses Lagrange and Newton interpolation to estimate positions between RK4 sample times and compares them with circular-orbit reference values.

The README also describes an optional simplified atmospheric-drag model and an in-browser educational demonstration. These are illustrative, not calibrated flight-prediction tools.

## Testing and Results

Verification was performed on November 6, 2026, from the project directory on Windows with MinGW:

| Command | Result |
|---|---|
| `cmake -S . -B build` | Passed |
| `cmake --build .\build` | Passed |
| `ctest --test-dir .\build --output-on-failure` | Passed: 17 of 17 registered tests |
| Smoke-run all configured example executables | Passed: 7 of 7 exited with code 0 |

The test run includes interpolation, matrix, vector construction and operations, linear-solver, decomposition, eigenvalue, integration accuracy, least-squares, iterative-solver, and trajectory tests, including the legacy weekly test sources. The example run includes interpolation, integration, linear algebra, satellite trajectory, trajectory interpolation, decompositions, and linear solvers.

During this verification, a placeholder decomposition test that returned success without assertions was replaced with substantive tests. The interpolation test and trajectory-interpolation example were registered after their filenames were normalized. Building the linear-algebra example also exposed a missing Matrix-times-Vector definition in the active CMake source; that implementation and its tests were added. The reported test count therefore reflects the updated code, not the earlier placeholder suite.

Limitations: a separate clean-machine build was not performed. Some registered legacy test targets duplicate coverage from the consolidated tests. The test suite checks representative inputs and does not establish production-grade physical accuracy.

## Contributions

The Week 5 individual reports describe work in the following areas:

| Member | Assigned area | Report status |
|---|---|---|
| Gilbert | Team integration, CMake, release coordination | Week 5 contribution report supplied, including Git-history evidence for merges, build organization, demonstrations, and visuals. |
| Delvin | Vector | Week 5 report supplied. |
| Ibrahim | Matrix | Week 5 report supplied. |
| Derrick | Direct linear solvers | No Week 5 individual report supplied; no report was created as part of this update. |
| Stacy | Matrix decompositions | Week 5 report supplied. |
| Praise | Iterative solvers | Week 5 report supplied. |
| Deogratius | Interpolation | No Week 5 individual report supplied; no report was created as part of this update. |
| Jeremiah | Numerical integration | Week 5 report supplied. |
| Erick | Least squares, eigenvalues, and satellite application | Week 5 report supplied. |


## AI-Use Declaration

The existing project materials declare AI use for initial planning and workflow organization, and Erick's Week 5 report declares ChatGPT use for implementation review, numerical-method explanations, and test design. For this follow-up, AI assistance was used to inspect and modify the build configuration, source, tests, and examples; run the documented verification commands; and draft this report. The group should review and edit the report and confirm that all final declarations reflect its members' actual use.
