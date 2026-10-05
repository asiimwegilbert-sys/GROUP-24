# Week 1 — Ibrahim Matrix Module
## Assigned part

Matrix module

## What I worked on this week

For Week 1, I worked on the initial design of the Matrix module. I mainly focused on the Matrix API, how the matrix data will be stored, and the rules for working with different matrix dimensions.

## Completed

- Proposed the main Matrix class interface.
- Decided on row-major storage using `std::vector<double>`.
- Defined zero-based indexing.
- Defined the dimension rules for addition, subtraction and multiplication.
- Defined how transpose and square matrices will work.
- Listed the invalid inputs that should be checked.
- Listed some questions that need to be agreed on by the group.
- Prepared the validation cases that I will use when implementing and testing.

## Branch

`feature/ibrahim-matrix`

## Commit

`docs: define matrix API and dimension rules`

## Questions / things to confirm

I still need the group to agree on the common numerical tolerance and the error-handling convention. We also need to decide where operations such as determinant and inverse should be placed.

## Validation plan

I plan to test both normal and invalid cases, including matrices with
different dimensions, valid and invalid multiplication, transpose,
out-of-range indices and invalid matrix construction.

## Next step

The next step is to implement the agreed Matrix API, add the tests and make sure it works with the group's existing CMake structure.

## AI use

ChatGPT was used to help organise the initial Matrix design and documentation.
I will check the proposed API and implementation against the group's actual repository before merging anything.

