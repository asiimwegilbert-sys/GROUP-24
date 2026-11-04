Week 3 Progress Report
Name: Nakibinge Jeremiah
Component: Numerical Integration Module

### Part 1: Object-Oriented Principles Implemented

1. Encapsulation:
The 'time_step' (dt) member variable is placed under the 'protected' access specifier within the NumericalIntegrator class. This hides it safely from external unauthorized access outside the inheritance hierarchy, while still allowing derived child classes to access and use it inside their calculation loops.

2. Multilevel Inheritance:
Our system uses a three-tier class relationship tree matching class lecture concepts. 'BaseSolver' serves as the grandparent class which handles data validation. 'NumericalIntegrator' inherits publicly from BaseSolver to gain access to validation rules, and 'MidpointSolver' inherits publicly from NumericalIntegrator to build the concrete mathematical solver.

3. Runtime Polymorphism:
The parent class defines 'virtual State compute_step(...)'. The child class 'MidpointSolver' overrides this function using the 'override' keyword. In the main program function, a base class pointer (NumericalIntegrator*) is assigned the address of a concrete child instance. Calling the function through this base pointer executes the child's dynamic code structure at runtime.

### Part 2: Deconstruction Questions Response

1. What class did you create?
We created a 3-tier multilevel class structure: a grandparent base class named BaseSolver, a parent class named NumericalIntegrator, and a derived child class named MidpointSolver.

2. Why?
To build a modular simulation structure that organizes defensive input validation data independently from the mathematical integration step routines, allowing us to implement clean object inheritance as taught in class.

3. What data does it hold?
- BaseSolver holds no direct member variables.
- NumericalIntegrator encapsulates a protected floating-point variable named time_step (representing our simulation dt parameter).
- MidpointSolver inherits this step variable directly from its parent.

4. What functions operate on that data?
- validate_inputs(state, dt): A member function that performs boolean safety checks on our simulation bounds.
- compute_step(f, t, y): A virtual execution function that is overridden by the child class to process our Runge-Kutta 2nd Order (RK2) differential equation mathematics.

5. Why are some members private/protected and others public? How is the class used by the rest of the program?
- Protected Specifier (protected): The time_step data member is protected to enforce data encapsulation. This isolates the raw variable from external modifications by outside files, while safely permitting any subclass in our family tree to use it directly.
- Public Specifier (public): Functions like validate_inputs and constructors are public so the main satellite wrapper framework can call them.
- Usage: The main application interfaces with the system by establishing a base class pointer (NumericalIntegrator*) pointing to a concrete MidpointSolver instance, dynamically resolving the correct method at runtime via polymorphism.
