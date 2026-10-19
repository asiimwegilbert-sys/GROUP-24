Week 3 Progress Report
Name: Nakibinge Jeremiah
Component: Numerical Integration Module

For week 3, I adjusted our codebase structure to actively incorporate the newly taught object-oriented programming concepts. I structured our numerical integration engine using three distinct architectural layers to implement multilevel inheritance:

1. BaseSolver (Grandparent class): Encapsulates input vector stability validation.
2. NumericalIntegrator (Parent class): Inherits validation functions and establishes our primary virtual function framework.
3. MidpointSolver (Child class): Inherits the complete operational layout and explicitly overrides the virtual step execution function to perform specific RK2 math loop calculations.

I demonstrated runtime polymorphism inside the main wrapper framework using a base class pointer (NumericalIntegrator*) targeting a concrete child instance to process simulation data. This fully fulfills our core OOP coursework targets. The remaining engine components (RK4, Romberg, and Gaussian Quadrature) will be added into this inheritance tree during Week 4.
