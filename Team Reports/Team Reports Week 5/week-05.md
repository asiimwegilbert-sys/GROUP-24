# Week 5 Progress Report

**Project:** Satellite Trajectory Numerical Computing Library  
**Checkpoint:** Before Monday, November 2, 2026  
**Repository verification update:** November 6, 2026

## Summary

Week 5 focused on integrating the numerical methods with the satellite trajectory example and checking the release candidate. Individual reports describe work on vector tests, Matrix review, decompositions, iterative solvers, numerical integration, least squares, eigenvalues and satellite propagation.

The November 6 repository verification found that several existing tests and examples were not being built by CMake. The decomposition test was a no-op, the interpolation test and trajectory-interpolation example had filenames CMake did not discover, and the active Matrix implementation lacked the declared Matrix-times-Vector operation. These gaps were addressed in the follow-up changes.

## Member Status

| Member | Area | Week 5 evidence |
|---|---|---|
| Delvin | Vector | Individual report describes tests for construction, access, norm, arithmetic, dot product and dimension errors; registered vector tests pass. |
| Ibrahim | Matrix | Matrix tests pass; the follow-up added Matrix-times-Vector to the active CMake-selected source and covered it in the registered tests. |
| Derrick | Direct solvers | No Week 5 individual report was supplied; no personal work is inferred. |
| Stacy | Decompositions | Individual report describes integration and stability checks; the follow-up added real decomposition tests, which pass. |
| Praise | Iterative solvers | Individual report says the module was finalized and reviewed; registered solver tests pass. |
| Deogratius | Interpolation | No Week 5 individual report was supplied; no personal work is inferred. |
| Jeremiah | Integration | Individual report describes integration and edge-case verification; registered integration and trajectory tests pass. |
| Erick | Least squares, eigenvalues and trajectory | Individual report describes least-squares fitting, eigenvalue work, drag support and trajectory tests; registered tests pass. |
| Gilbert | Team integration, CMake and release coordination | See [Gilbert's Week 5 report](./Gilbert_week_05.md) for merge, CMake, demonstration and visual evidence. |

Individual reports are present for Gilbert, Delvin, Ibrahim, Praise, Stacy, Jeremiah and Erick. Derrick's and Deogratius's Week 5 reports were not created or edited.

## Integration and Verification

- Added the declared Matrix-times-Vector implementation to the active source and covered its values, identity behavior and dimension mismatch.
- Replaced the placeholder decomposition test with reconstruction, orthogonality and invalid-input checks.
- Made the vector-operator test runnable and registered it in CMake.
- Registered the existing interpolation test and trajectory-interpolation example.
- Completed the linear-algebra example and corrected the decomposition example to use the public Gram-Schmidt QR function.
- Added decomposition and linear-solver examples to CMake.

| Command | Result |
|---|---|
| `cmake -S . -B build` | Passed |
| `cmake --build .\build` | Passed |
| `ctest --test-dir .\build --output-on-failure` | Passed: 17 of 17 tests |
| Smoke-run all configured examples | Passed: all 7 exited successfully |

The smoke run covered interpolation, integration, linear algebra, satellite trajectory, trajectory interpolation, decompositions and linear solvers.

## Remaining Notes

- Verification was performed in the available Windows/MinGW environment; a separate clean-machine build was not performed.
- All 17 C++ test sources were registered with CMake. The example and test results verify configured targets, not flight-ready orbital predictions.

## AI Use

AI assistance was used in the follow-up repository inspection, integration fixes, test/example registration, verification and report drafting. This statement does not make claims about individual members' AI use.
