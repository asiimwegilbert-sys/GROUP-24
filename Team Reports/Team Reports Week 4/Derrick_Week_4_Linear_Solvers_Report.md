# Week 4 Individual Progress Report — Linear Solvers

**Student/member:** Derrick  
**Assigned responsibility:** Linear Solvers module  
**Language standard:** C++23

## 1. Work completed

In Week 4, I integrated the previous solver functions and added iterative refinement. solveWithRefinement obtains an initial solution, calculates the residual, solves for a correction, and adds it to the estimate until the tolerance is reached or the iteration limit is used.

## 2. Inheritance in the code

LinearSolver remains the abstract base class. GaussianSolver and BackSubstitutionSolver inherit from it, and Week 4 adds RefinementSolver as another derived class. RefinementSolver overrides solve and calls solveWithRefinement.

## 3. Polymorphism in the code

The tests create LinearSolver pointers for GaussianSolver and RefinementSolver, then call solve through the base interface. The same call invokes different implementations depending on the actual object, demonstrating runtime polymorphism.

## 4. How refinement uses earlier work

The refinement function reuses solveGaussian for the initial solution and correction system. It uses calculateResidual and residualNorm to decide whether the answer meets the tolerance. This connects Week 3 validation to Week 4 refinement.

## 5. Testing and evidence

The test source compares direct and refined answers, checks residual accuracy, and rejects a negative iteration count.

## 6. Limitations and integration checklist

Iterative refinement may not improve every matrix.

## 7.  AI-use declaration

Tool: ChatGPT. Purpose: help organize the report and explain iterative refinement with inheritance and polymorphism. Reason: to describe the code and tests clearly.
