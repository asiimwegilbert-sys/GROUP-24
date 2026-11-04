The fifth week is the integration and stabilisation checkpoint for the satellite trajectory library. My responsibility at this stage 
is to verify that the Matrix Decompositions module behaves consistently with the shared library and remains usable by other modules.
I am to verify the defining identities using representative matrices. For LU, the test must apply the returned row permutation to A 
before comparing it with L*U. For Cholesky, the product L*L-transpose must match the symmetric positive-definite input. For both QR 
implementations, Q*R must reconstruct A and Q-transpose*Q must be close to the identity matrix.
I will also check failure behaviour. LU should reject singular matrices, Cholesky should reject non-symmetric or non-positive-definite
matrices, and QR should reject matrices with dependent columns or unsupported dimensions. Invalid tolerances and non-finite entries 
should be rejected consistently.
The module uses the shared Matrix interface and is exposed through `decompositions.hpp`. The example demonstrates how a caller can 
access the factors and, for LU, the row permutation. The final integration check should include the full CMake build and 
`ctest --test-dir build --output-on-failure`. If another module prevents the full build, I will record the exact error and distinguish it
from the focused decomposition test result.
Before the contribution is considered complete, I need to run the tests on the current release candidate, review compiler warnings, inspect 
the pull request diff, and request review from another team member. Any tolerance adjustment must be supported by test evidence and discussed
if it changes the public behaviour.
