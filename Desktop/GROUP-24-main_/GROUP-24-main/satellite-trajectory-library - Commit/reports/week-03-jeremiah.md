Week 3 Progress Report
Name: Nakibinge Jeremiah
Component: Numerical Integration OOP Refactor

For week 3, I have made our numerical integration source files to utilize foundational Object-Oriented Programming principles as taught in our course unit. I introduced a base parent class called TrajectorySolver to store fundamental configuration data like our simulation time step.

I then created a derived child class called MidpointSolver that inherits directly from the parent class. This child class encapsulates our specific RK2 math calculation loops. In week 4, I will continue this inheritance layout to handle our RK4 engine steps, Gaussian quadrature, and Romberg integration methods.
