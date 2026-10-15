# Week 2 — Derrick Linear Solvers Module

## Member

Derrick

## Assigned Responsibility

Linear Solvers module

## Completed This Week

Built on the Week 1 back-substitution work by adding:

- Gaussian elimination.
- Partial pivoting.
- Row swapping.
- Singular and nearly singular pivot checking.
- Tests for a normal system.
- A test where row swapping is required.
- A singular matrix test.
- Reuse of back substitution after elimination.

## Branch

`feature/derrick-linear-solvers`

## Commit

`feat: add gaussian elimination with pivoting`

## Pull Request

To be created after the Week 2 implementation and tests are checked.

## Reviewer

To be assigned during pull request review.

## Design Summary

The Week 2 solver changes a general square system into an upper triangular system using Gaussian elimination. After that, the back-substitution function from Week 1 is used to get the answer.

Partial pivoting was added by looking for the largest absolute value in the current column and swapping rows when necessary.

## Test 1 — Normal System

The system used was:

`2x + y = 5`

`x + 3y = 6`

The expected answer is:

`x = 1.8`

`y = 1.4`

## Test 2 — Partial Pivoting

The system used was:

`y = 2`

`2x + y = 4`

The first pivot is zero, so the rows have to be swapped.

The expected answer is:

`x = 1`

`y = 2`

## Test 3 — Singular Matrix

The system used was:

`x + 2y = 3`

`2x + 4y = 6`

The second equation is a multiple of the first one, so the matrix is singular. The program detects this and throws an error.

## AI Use

**Tool:** ChatGPT

**Purpose:** To help organize the Week 2 report and explain the steps of Gaussian elimination and partial pivoting.

**Reason it was used:** It helped me understand how the Week 2 work builds on the Week 1 back-substitution function.

**What I verified or changed:** I checked the example systems, reviewed the code logic, and kept the report focused on the work completed in Week 2.

## Next Week

In Week 3, I plan to improve input validation and add residual calculations and more edge-case tests.
