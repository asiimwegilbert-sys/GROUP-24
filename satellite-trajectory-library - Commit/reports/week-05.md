# Week 5 Progress Report

**Project:** Satellite Trajectory Numerical Computing Library  
**Checkpoint:** Before Monday, November 2, 2026  
**Repository verification update:** November 6, 2026

## Summary

Week 5 focused on integrating the numerical methods with the satellite trajectory example and checking the release candidate. The individual reports describe work on vector tests, Matrix review, decompositions, iterative solvers, numerical integration, least squares, eigenvalues, and satellite propagation.

The November 6 repository verification found that several existing tests and examples were not being built by CMake. In particular, the decomposition test was a placeholder that returned success without testing anything, and the interpolation test and trajectory-interpolation example had filenames that prevented CMake from finding them. The active Matrix implementation also lacked the declared Matrix-times-Vector operation. These gaps were addressed in the follow-up changes, and the verification results below include those changes.

## Member Status

| Member | Area | Week 5 evidence |
|---|---|---|
| Delvin | Vector | Individual report describes a standalone test suite for construction, access, norm, arithmetic, dot product, and dimension errors. The registered vector tests pass. |
| Ibrahim | Matrix | The report notes that CMake builds `src/Matrix3.cpp`. Matrix tests pass; the follow-up added the missing Matrix-times-Vector definition to that active source file and covered it in the registered Matrix tests. |
| Derrick | Direct solvers | No Week 5 individual report was supplied. No personal work is inferred here. |
| Stacy | Decompositions | The Week 5 report describes the intended integration and stability checks. A real decomposition test suite was added during follow-up verification; LU, Cholesky, Householder QR, and modified Gram-Schmidt checks pass. |
| Praise | Iterative solvers | The individual report says the iterative module was finalized and reviewed. The registered solver tests pass. |
| Deogratius | Interpolation | No Week 5 individual report was supplied. No personal work is inferred here. |
| Jeremiah | Integration | The individual report describes integration and edge-case verification. The registered integration and trajectory tests pass. |
| Erick | Least squares, eigenvalues, trajectory | The individual report describes least-squares fitting, eigenvalue work, drag support, and trajectory tests. The registered least-squares, eigenvalue, and trajectory tests pass. |
| Gilbert | Team integration, CMake, release coordination | See [Gilbert's Week 5 report](../../Team%20Reports/Team%20Reports%20Week%205/Gilbert_week_05.md) for merged PRs, CMake organization, demonstrations, and visual assets. |

Individual reports are present in `Team Reports/Team Reports Week 5/` for Gilbert, Delvin, Ibrahim, Praise, Stacy, Jeremiah, and Erick. Derrick's and Deogratius's individual reports have not been created or edited.

## Integration Fixes in This Verification Update

- Implemented the declared Matrix-times-Vector operation in the `Matrix3.cpp` source file selected by CMake, and added coverage for its values, identity behavior, and dimension mismatch.
- Replaced the placeholder decomposition test with checks for reconstruction identities, orthogonality, and invalid inputs.
- Replaced the Week 3 vector-operator placeholder with a real test, registered it in CMake, and gave it a descriptive filename.
- Registered the existing interpolation test and trajectory-interpolation example, whose original filenames were not discovered by the build rules.
- Completed the linear-algebra example and fixed the decomposition example to call the public Gram-Schmidt QR function.
- Added the decomposition and linear-solver examples to the CMake example targets.

## Verification

Commands were run from the project directory:

| Command | Result |
|---|---|
| `cmake -S . -B build` | Passed |
| `cmake --build .\build` | Passed |
| `ctest --test-dir .\build --output-on-failure` | Passed: 17 of 17 registered tests |
| Smoke-run all configured examples | Passed: all 7 executables exited with code 0 |

The example smoke run covered interpolation, integration, linear algebra, satellite trajectory, trajectory interpolation, decompositions, and linear solvers.

## Remaining Notes

- The successful build and tests verify the configured targets on this Windows/MinGW environment; a separate clean-machine build was not performed.
- `src/` and `include/` contain no explicit TODO or placeholder markers. All 17 C++ test source files in `tests/` are now registered with CMake. Some targets intentionally retain overlapping historical coverage.

## AI Use

AI assistance was used in this follow-up to inspect the repository, fix the Matrix-times-Vector integration gap, complete and register tests and examples, run the verification commands, and draft this report. The group should review the changes and report wording before submission. This statement does not make claims about AI use by individual members.
