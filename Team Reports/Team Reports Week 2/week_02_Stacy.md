Progress report for Week 2 on Matrix decompositions.
During Week 2, my assigned Matrix Decompositions implementation has not yet begun, so there are no completed source-code changes or verified
test results for this period. The module still needs an initial review of the existing interfaces and the numerical expectations used by the 
rest of the satellite trajectory library.

The first algorithm planned for implementation is LU decomposition. In this method, a square matrix is represented using lower- and upper-triangular matrices;
when partial pivoting is needed, a permutation matrix or equivalent pivot information must also be tracked. Pivoting is important because it helps avoid unstable
divisions and supports cases where a suitable pivot is not already on the diagonal. Validation is also necessary so that invalid dimensions and unsuitable input 
matrices are handled deliberately rather than producing misleading results.
This describes the intended technical direction The practical priority remains checking the agreed function signatures and project conventions before implementing
the method.

Challenges and Lessons
Because the implementation has not started, I have not yet verified how the LU routine would behave on singular matrices, matrices requiring row swaps, or invalid 
inputs. These are test cases that must be considered during implementation rather than problems I can claim to have solved during this reporting period.

Next Steps
The next stage is to implement LU decomposition with pivot tracking, then test whether the factors reconstruct the original matrix under the chosen permutation 
convention. I will also check validation behaviour for unsuitable inputs and record any build or integration issues when they are actually encountered.
