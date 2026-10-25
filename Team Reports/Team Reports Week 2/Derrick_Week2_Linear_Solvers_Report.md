# Week 2 Individual Progress Report — Class-Based Linear Solvers

**Student/member:** Derrick  
**Responsibility:** Linear Solvers module  
**Language standard:** C++23

## 1. What class did I create?

I organized the Week 2 code around two classes: GaussianSolver and BackSubstitutionSolver. GaussianSolver performs Gaussian elimination with partial pivoting. BackSubstitutionSolver solves an upper-triangular system. I also used SolverOptions to store the pivot tolerance, and Matrix and Vector aliases to make declarations easier to read.

## 2. Why did I create these classes?

The classes group each solver's operations and settings in one place. This makes the code easier to follow and lets the tests create a solver object and call its solve function instead of placing all the work inside main().

## 3. What data does each class hold?

Both solver classes hold one private member, options_, of type SolverOptions. SolverOptions contains the public double pivot_tolerance, used to decide when a pivot is too small. The matrix and right-hand-side vector are passed to solve() and are not stored as class members.

## 4. What member functions operate on that data?

GaussianSolver has a public constructor and solve(const Matrix& A, const Vector& b) const. It copies the system, chooses the largest pivot in each column, swaps rows when needed, eliminates entries below the pivot, and finishes with back substitution. BackSubstitutionSolver has a public constructor and solve(const Matrix& U, const Vector& b) const, which solves from the last row upward.

## 5. Which members are private and which are public?

The options_ member is private in both classes so outside code cannot directly change the stored settings. Constructors and solve() are public so other parts of the program can create and use solver objects. SolverOptions is a struct, so pivot_tolerance is public by default. No protected members or inheritance relationship are used in this Week 2 design.

## 6. How are the classes designed and used?

The tests create a GaussianSolver object and call gaussian.solve(A, b) for a general square system. Another test system needs a row swap and checks partial pivoting. The tests also create a BackSubstitutionSolver object and call back.solve(U, rhs). A singular matrix case checks that GaussianSolver reports an error.

## 7. Testing and evidence

The source tests cover known answers for both methods, a pivoting case, and a singular matrix.

## 8. AI-use declaration

Tool: ChatGPT. Purpose: help organize the report and explain the class structure. Reason: to communicate how the solver classes are organized and used.
