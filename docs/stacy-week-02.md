Week 02 report by Stacy Elizabeth Namuleme.
This week =, I moved the decompositions module from design to implementation. I implemented LU decompositions with partial pivoting and Cholesky decomposition in 'src/decompositions.cpp', following the interface defined in 'decompositions.hpp' and also wrote
unit tests for both in 'tests/test_decompositions.cpp',. The most important remaining risk is that Gram-Schmidt and Householder QR are not yet implemented

The tasks completed include;
LU decomposition with partial pivoting,
returning 'lower', 'upper', 'permutation' and 'swap_count'
then also Cholesky decomposition with symmetry and positive checks, unit tests for both, covering normal, edge and invalid cases
and the design note updated with current status.

The following remain in progress;
A modified Gram-Schmidt and Householder QR

Testing Completed 
[] Normal cases, [] edge cases, [] invalid inputs, []Relevant tests and []Clean build

Next Week's plan includes;
Implementing and testing Cholesky decomposition,
Implementing and testing modified Gram-Schmidt,
Implementing and testing Household QR. 
