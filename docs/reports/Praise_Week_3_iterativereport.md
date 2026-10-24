## Week 3 Progress Report: Power Iteration & Object-Oriented Programming

### 1. Overview
In Week 3, we finished our linear solvers by adding the **Power Iteration method** to our code (`src/iterative_solvers.cpp`). This helps us find eigenvalues and eigenvectors ($Ax = \lambda x$) for satellite paths. We also looked at how our program uses Object-Oriented Programming (OOP).

### 2. OOP Principles in Our Program
Our project uses key OOP ideas to stay organized:
* **Encapsulation:** We group our settings into `IterationOptions` and our answers into `IterationResult` so our code stays clean instead of using messy scattered variables.
* **Inheritance:** Just like family traits passed down through generations (like the *Money Heist* example our teacher shared), our program shares common configuration settings and rules across different math tools.
* **Polymorphism:** All three solvers (`jacobi`, `gauss_seidel`, and `power_iteration`) use the exact same input style and return results the same way, making them easy to swap and use together.

### 3. Class Layout and Access Types
Our classes and structures are organized with clear access levels:
* **`IterationOptions` Structure:**
  * **Access:** `public`[cite: 8]
  * **Data inside:** `tolerance` and `max_iterations`
  * **Why:** Lets the main program and tests easily change settings.
* **`IterationResult` Structure:**
  * **Access:** `public`[cite: 8]
  * **Data inside:** `solution`, `iterations`, and `converged`
  * **Why:** Safely packages and shows the final answers.
* **`Matrix` & `Vector` Classes:**
  * **Access:** Public functions (`.rows()`, `(i, j)`) with private inner parts hidden safely to protect the data[cite: 8].


### 4. How Power Iteration Math Works
* **Matrix-Vector Multiplication:** We multiply matrix $A$ by our current vector at every step.
* **Rayleigh Quotient:** We estimate the eigenvalue dynamically.
* **Normalization:** We scale the vector so numbers don't get too big.
* **Stopping Check:** We stop looping once the error drops below our target tolerance.