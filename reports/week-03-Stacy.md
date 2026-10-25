Progress report for Week 03..
Instead, this stage identifies how the remaining algorithms fit into the overall plan and what needs to be checked once coding begins.

Cholesky decomposition expresses a suitable symmetric positive-definite matrix as a product of a lower-triangular matrix and its transpose.
QR decomposition represents a matrix as the product of an orthogonal matrix and an upper-triangular matrix. The planned QR approach uses
Householder transformations, while modified Gram–Schmidt provides another way to construct an orthogonal basis. These methods have different 
assumptions and numerical properties, so their validation and tests need to reflect those differences.

Before implementing these routines, I need to make sure their interfaces match the project's existing matrix representation and that errors
are reported consistently. For example, Cholesky should reject matrices that do not satisfy its requirements, while QR tests should check both 
reconstruction and the orthogonality of the resulting matrix. Gram–Schmidt also needs attention to linearly dependent or nearly dependent input columns.

I have faced a few difficulites since the routines had not yet been implemented, their numerical correctness and compatibility with the full project were still unverified.
The main lesson for the next stage is to work incrementally: implement one method, check its mathematical properties with focused tests, 
and only then move to the next method. Any whole-project build issue should be distinguished from a failure in the decomposition code itself.

Next Steps
The next stage is to implement the planned methods in small, reviewable steps, beginning with LU and then proceeding to Cholesky
Householder QR, and modified Gram–Schmidt. I will add tests for reconstruction, orthogonality where applicable, and invalid inputs,
and report only results that have actually been observed.
