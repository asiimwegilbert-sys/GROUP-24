This week was designated as the stabilisation period for the numerical methods. My specific responsibility was to finish stability 
tests for the decomposition routines and document assumptions such as positive definiteness.

Implementation;
The module implementation contains four decomposition approaches. LU uses partial pivoting and returns the row permutation alongside 
L and U, making the identity P*A = L*U explicit. Cholesky checks symmetry and positive definiteness before returning L and its 
transpose. Householder QR and modified Gram–Schmidt return thin Q and R factors. The public header also provides a convenience Gram–Schmidt
function that returns Q alone.
The implementation validates non-empty and finite inputs, checks matrix dimensions, and uses a configurable positive tolerance.
The tests check reconstruction identities, orthogonality and invalid-input behaviour. A small example program demonstrates the returned 
factors.

Verification and limitations;
The decomposition tests should be run independently as well as through the project test suite. A successful focused test run only establishes
the behaviour of this module and its directly compiled dependencies. It does not prove that every project module builds. Any unrelated 
integration failure should be reported to the responsible owner rather than silently changed as part of this contribution.

The next stage is to run the module tests in the current integrated repository, verify the tolerance choices on representative matrices,
inspect the final diff, and obtain a teammate's review before merging.
