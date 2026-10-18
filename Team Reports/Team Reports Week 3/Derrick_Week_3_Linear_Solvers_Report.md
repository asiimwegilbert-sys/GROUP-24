# Week 3 Individual Progress Report — Linear Solvers

**Student/member:** Derrick
**Assigned responsibility:** Linear Solvers module
**Language standard:** C++23

## 1. Work completed
I extended the Week 2 solver with residual and solution-validation functions. `calculateResidual` calculates r = b − A*x, `residualNorm` calculates the Euclidean norm, and `isSolutionAccurate` compares that norm with a tolerance.

## 2. Implementation
The module keeps back substitution and Gaussian elimination with partial pivoting. I added checks for invalid dimensions and tests for a known solution, a deliberately inaccurate solution, and invalid matrix dimensions.

## 3. Testing and evidence
Test source is included for these cases. This package does not claim a successful compiler run because C++23 named-module support and build commands depend on the compiler used.

## 4. Git workflow
Suggested branch: `feature/derrick-residual-validation`
Suggested commit: `feat: add residual validation helpers`
Create the branch and commit in the team repository and request teammate review.

## 5. Limitations and next steps
A small residual is useful but does not guarantee that a matrix is well-conditioned. Next week I plan to add iterative refinement and integration checks.

## 6. AI-use declaration
Tool: ChatGPT. Purpose: help organize the report and clarify residual validation. Reason: present the work clearly. What I verified or changed: reviewed the function descriptions and test examples and kept the report focused on this week's work.
