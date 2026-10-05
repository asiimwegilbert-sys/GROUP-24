# Week 1 — Ibrahim Matrix Module

## Member

Ibrahim

## Assigned Responsibility

Matrix module

## Completed This Week

Prepared the initial design for the Matrix module, including:

- Proposed Matrix public API.
- Matrix storage layout.
- Matrix dimension rules.
- Matrix indexing convention.
- Invalid-input behaviour.
- Validation and testing requirements.
- Integration considerations for future numerical methods.

## Branch

feature/ibrahim-matrix

## Commit
docs: define matrix API and dimension rules

## Pull Request

To be created after the Week 1 design commit.

## Reviewer

To be assigned during pull request review.

## Design Summary

The proposed Matrix class will use std::vector<double> with row-major
storage. Matrix elements will be accessed using zero-based (row, column)
indexing.

The API will support construction, dimension queries, element access,
addition, subtraction, multiplication, scalar multiplication, transpose,
square-matrix checking, and approximate comparison.

## Dimension Rules

Matrix addition and subtraction require equal dimensions.

Matrix multiplication requires:

***text
A(m x n) × B(n x p) = C(m x p)
