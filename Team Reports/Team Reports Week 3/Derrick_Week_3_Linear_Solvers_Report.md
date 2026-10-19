# Week 3 Individual Progress Report — Linear Solvers

**Student/member:** Derrick  
**Assigned responsibility:** Linear Solvers module  
**Language standard:** C++23

## 1. Work completed

In Week 3, I added residual validation and introduced an object-oriented design for the linear solver. The module retains back substitution and Gaussian elimination, and adds functions to calculate the residual vector, its Euclidean norm, and whether a solution is within a tolerance.

## 2. Inheritance in the code

I created an abstract base class named LinearSolver. It declares a pure virtual solve function. GaussianSolver and BackSubstitutionSolver inherit from LinearSolver and override solve, each calling its own solver function.

## 3. Polymorphism in the code

The tests store derived solver objects using std::unique_ptr<LinearSolver> and call solve through a base-class pointer. The actual object determines which override runs. GaussianSolver handles a general square system, while BackSubstitutionSolver is for an upper-triangular system.

## 4. Residual validation

calculateResidual computes r = b - A*x. residualNorm measures the size of the residual, and isSolutionAccurate checks it against a tolerance. This helps assess whether the solution satisfies the original equations.

## 5. Testing and evidence

The test source covers known answers for both solvers, polymorphic calls, residual checks, and an inaccurate solution. Tests are included as source; successful compilation or execution is not claimed.

## 6. Git workflow

Suggested branch: feature/derrick-residual-validation. Suggested commit: feat: add residual validation and solver polymorphism. Create the branch and commit in the team repository and request teammate review.

## 7. Limitations and next steps

BackSubstitutionSolver expects an upper-triangular matrix. A small residual does not guarantee a well-conditioned matrix. Compile and run the tests with the team's C++23 named-module setup. Week 4 adds iterative refinement as another solver implementation.

<img width="3010" height="2660" alt="IMG_20261019_151523_007" src="https://github.com/user-attachments/assets/550b394c-cbc7-4f0e-a9a9-9e705137885b" />
