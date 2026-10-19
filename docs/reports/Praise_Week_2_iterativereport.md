
During Week 2, I expanded our linear solvers module by successfully implementing the **Gauss-Seidel iterative method** in our source file . This method provides a faster, more efficient way to solve linear equation systems compared to the Jacobi method.


I wrote the step-by-step math logic for Gauss-Seidel with key improvements:

* **In-Place Updates:** Unlike Jacobi (which waits for an entire loop step to finish), Gauss-Seidel uses the newest calculated numbers immediately. As soon as a new variable value is found, it is used right away in the next equation, helping the math converge to the correct answer much faster.
* **Dimension and Safety Checks:** Maintained rigorous input validation to ensure matrix and vector sizes match, and added guards against zero or near-zero numbers on the main diagonal to prevent division errors.
* **Convergence & Stopping Rules:** Tracked the maximum difference between each iteration step and stopped the loop successfully once the error dropped below our target tolerance threshold.



Wrapped up the calculations using our standard `SolverResult` package, ensuring we capture the solution vector, total iterations run, convergence status, and final residual error just like we did in Week 1.

---