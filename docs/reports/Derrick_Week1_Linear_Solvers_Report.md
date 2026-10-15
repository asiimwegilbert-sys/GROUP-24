# Week 1 — Derrick Linear Solvers Module

## Member

Derrick

## Assigned Responsibility

Linear Solvers module

## Completed This Week

Prepared the first version of the Linear Solvers module, including:

- Basic design of the Linear Solvers functions.
- C++23 named module setup.
- Back substitution.
- Forward substitution.
- Basic checking of matrix and vector sizes.
- Checking for zero or very small diagonal values.
- A simple test program.

## Branch

`feature/derrick-linear-solvers`

## Commit

`feat: add basic linear solver functions`

## Pull Request

To be created after the Week 1 work is checked.

## Reviewer

To be assigned during pull request review.

## Design Summary

The Linear Solvers module is used for solving equations in the form:

`A x = b`

The first version uses simple `std::vector` containers for matrices and vectors. The main idea is to keep the code easy to understand while still allowing it to be used by the other parts of the satellite trajectory project.

The module contains functions for forward substitution and back substitution. These functions solve triangular systems by using simple loops.

## Dimension Rules

The matrix must be square.

The right-hand-side vector must have the same number of elements as the matrix has rows.

A zero or very small diagonal value is treated as a problem because division by it would give an incorrect result.

You can write it like this in the **AI Use** section of your Week 1 report:

### AI Use

* **Tool:** ChatGPT
* **Purpose:** To help organize and explain the Week 1 Linear Solvers report.
* **Reason it was used:** I used AI to help me structure the report and clarify some of the basic ideas for the Linear Solvers module.
* **What I verified or changed:** I reviewed the suggestions, made changes where necessary, and checked that the final report matched the work completed for Week 1.

## Next Step

In Week 2, Gaussian elimination and partial pivoting will be added so that the module can solve more general systems of linear equations.
