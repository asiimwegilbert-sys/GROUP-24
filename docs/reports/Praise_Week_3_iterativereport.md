## Week 3 Progress Report: Power Iteration & Object-Oriented Programming (OOP) Architecture

### 1. Overview
During Week 3, we completed our linear solvers module by implementing the **Power Iteration method** in our source file (`src/iterative_solvers.cpp`). Beyond the mathematical implementation of eigenvalue and eigenvector analysis ($Ax = \lambda x$), this week’s focus emphasizes Object-Oriented Programming (OOP) principles, clean class design, and architectural documentation as outlined in the project guidelines[cite: 8].

### 2. Object-Oriented Principles in Our Program
To comply with robust software engineering standards and project requirements[cite: 8], our satellite trajectory library implements core OOP principles:

* **Encapsulation:** 
  We bundle configuration parameters into `IterationOptions` and output results into `IterationResult`. This protects internal data integrity by grouping related states and behaviors into cohesive structures, preventing scattered global variables.
* **Inheritance:** 
  Following modular design philosophy and hierarchical relationships, our configuration and data structures pass down standard attributes (like tolerance and iteration caps) to specialized math operations, allowing extended capabilities without rewriting base configurations.
* **Polymorphism:** 
  Our solver functions (`jacobi`, `gauss_seidel`, and `power_iteration`) share a uniform interface structure. They accept standardized `Matrix`, `Vector`, and `IterationOptions` parameters and return an `IterationResult` package. This consistent signature allows different numerical algorithms to be invoked polymorphically across the trajectory library.

### 3. Class Layout, Access Specifiers, and Visual Documentation
In accordance with our design specifications and assignment instructions[cite: 8], our classes and structures organize members with clear access controls:

* **`IterationOptions` Structure:**
  * **Access:** `public`[cite: 8]
  * **Member Data:** `double tolerance`, `std::size_t max_iterations`
  * **Purpose:** Allows unrestricted read/write access for configuration setup by the main program and unit tests.
* **`IterationResult` Structure:**
  * **Access:** `public`[cite: 8]
  * **Member Data:** `Vector solution`, `std::size_t iterations`, `bool converged`
  * **Purpose:** Packages and exposes computed solver outcomes cleanly to external modules.
* **`Matrix` & `Vector` Classes:**
  * **Access:** Encapsulated with `public` interfaces[cite: 8] (such as `.rows()` and operator overloading `(i, j)`) and `protected` / `private`[cite: 8] underlying memory representations to safeguard data containment.



### 4. Implementing the Power Iteration Math Logic
* **Matrix-Vector Multiplication:** Multiplying matrix $A$ by the current vector approximation $x_k$ at each step.
* **Rayleigh Quotient Estimation:** Calculating the dominant eigenvalue $\lambda$ approximation dynamically.
* **Vector Normalization:** Scaling the resulting vector to prevent numerical overflow.
* **Convergence Verification:** Stopping when the residual error falls beneath the specified tolerance.