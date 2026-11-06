# Week 5 

- Implemented *least-squares solving using QR decomposition* and added polynomial fitting using a Vandermonde matrix.
- Continued development of the *eigenvalue module* using QR iteration.
- Extended the trajectory model with *optional atmospheric drag* and a simplified exponential atmospheric-density model.
- Updated trajectory propagation so orbital decay results naturally from drag-induced energy loss.
- Expanded trajectory tests to cover orbital period, circular orbit propagation, time progression, drag effects, and invalid inputs.
- Successfully built the project and ran the registered CMake tests, with all current tests passing.
- Identified a project integration issue: linear_solvers uses a different matrix representation from the main sat::num::Matrix used by least squares, decompositions, and eigenvalues.
- Next steps are to register least_squares_tests in CMake, expand test coverage, and continue numerical validation.

# AI Use
ChatGPT was used to review implementations, explain numerical methods, identify matrix compatibility issues, and help design appropriate tests.