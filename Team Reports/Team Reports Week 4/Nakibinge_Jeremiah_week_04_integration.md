Week 3 & 4 Final Progress Report
Name: Nakibinge Jeremiah
Component: Numerical Integration Module

### Part 1: Structural OOP Consolidation
For Week 4, I completed the encapsulation of our entire numerical simulation suite inside our Object-Oriented Programming framework. Every single core mathematical routine now interfaces explicitly through inheritance lineages using virtual method resolutions.

1. Trajectory ODE Tree Expansion:
- Built ClassicalRK4Solver as a secondary child class derived from TrajectorySolver.
- Overrode 'compute_step(...)' to run our 4th-order Runge-Kutta numerical calculations cleanly.

2. Scalar Quadrature Area Tree:
- Introduced a separate base class called QuadratureIntegrator defining a generalized virtual interface for area integrations.
- Implemented GaussLegendreSolver (Child A) and RombergSolver (Child B) as derived classes overriding the 'integrate(...)' method.

### Part 2: Program Deconstruction & Design Goals
1. What classes did you create?
We finalized two distinct family structures: an ODE tracking sequence (BaseSolver -> TrajectorySolver -> MidpointSolver / ClassicalRK4Solver) and an area evaluation tree (QuadratureIntegrator -> GaussLegendreSolver / RombergSolver).

2. Why?
To eliminate messy independent functions, structuring our team's simulation module into manageable, reusable components that leverage compile-time type grouping.

3. What data does it hold?
The system utilizes 'protected' specifiers to encapsulate state size loops and step size metrics ('time_step') inside the core trajectory managers, hiding them from illegal overrides.

4. Why are some members protected and others public?
Member parameters are protected so that specialized child classes can pull parameters implicitly from their parent context without manual instantiation, while wrapper function configurations remain public to allow the group's global main driver routine to access them cleanly.
