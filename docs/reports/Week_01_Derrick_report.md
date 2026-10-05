 Week 1 — Derrick Linear Solvers Module

Member

Derrick

Assigned Responsibility

Linear Solvers module

 Completed This Week

Prepared the initial design and implementation plan for the Linear Solvers module, including:

* Proposed Linear Solvers public API.
* C++23 named-module structure.
* Back-substitution algorithm for triangular systems.
* Gaussian elimination with partial pivoting.
* Matrix and vector dimension validation.
* Singular and nearly singular system detection.
* Residual calculation and solution verification.
* Testing requirements and edge-case handling.
* Integration considerations for future numerical methods.

 Branch

`feature/derrick-linear-solvers`

Commit

`feat: implement C++23 linear solvers module`

 Pull Request

To be created after the Week 1 Linear Solvers implementation commit.

Reviewer

To be assigned during pull request review.

Design Summary

The proposed Linear Solvers module will provide numerical routines for solving systems of linear equations of the form:

A x = b

The module will use C++23 named-module syntax and provide a public `Vector` and `Matrix` interface based on `std::vector<double>`.

The API will support:

* Forward substitution.
* Back substitution.
* Gaussian elimination.
* Partial pivoting.
* Residual norm calculation.
* Iterative solution refinement.
* Input and dimension validation.
* Singular and nearly singular matrix detection.

The Linear Solvers module is designed to integrate with the Matrix module and provide the numerical foundation required by later satellite trajectory computations.

Solver Rules

Back substitution is used for upper-triangular systems:

U x = b

Gaussian elimination transforms a general square system into an upper-triangular system before applying back substitution.

Partial pivoting requires selecting the largest available absolute pivot in the current column and exchanging rows when necessary.

The solver will reject systems that are:

* Empty.
* Non-square.
* Ragged or inconsistently sized.
* Dimensionally incompatible with the right-hand-side vector.
* Singular or nearly singular.
* Containing non-finite numerical values.

The default pivot tolerance is:

1 × 10⁻¹²
