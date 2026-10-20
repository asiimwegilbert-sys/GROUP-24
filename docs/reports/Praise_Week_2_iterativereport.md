
During Week 2, I expanded our linear solvers module by successfully implementing the Gauss-Seidel iterative method in our source file . This method provides a faster, more efficient way to solve linear equation systems compared to the Jacobi method by using newly calculated numbers immediately..


To adhere to our project's object-oriented design, our module utilizes structured configuration and result types to organize data cleanly:
We created two main structures to manage our data: IterationOptions (for configuration settings) and IterationResult (for holding the output data).
This is because instead of passing many separate variables back and forth through our functions, grouping them into structures makes the code much cleaner, easier to read, and safer to maintain.

IterationOptions holds data members for configuration: tolerance (to control precision) and max_iterations (to limit loop steps).
IterationResult holds data members for output: solution (a Vector containing the final answer), iterations (how many steps it took), and converged (a boolean flag showing if it successfully finished).

The global-scoped solver functions like gauss_seidel(...) and jacobi(...) take IterationOptions as input parameters to configure how they run, and they process data through custom Matrix and Vector classes. They then construct and return an IterationResult object containing the computed findings

In our IterationOptions and IterationResult structs, the data members are public by design. This allows the main program, the unit tests, and our solver functions to easily read and write configuration settings and results directly without unnecessary boilerplate getter/setter code.

I wrote the step-by-step math logic for Gauss-Seidel with key improvements:

 Unlike Jacobi (which waits for an entire loop step to finish), Gauss-Seidel uses the newest calculated numbers immediately. As soon as a new variable value is found, it is used right away in the next equation, helping the math converge to the correct answer much faster.
 Maintained rigorous input validation to ensure matrix and vector sizes match, and added guards against zero or near-zero numbers on the main diagonal to prevent division errors.
 Tracked the maximum difference between each iteration step and stopped the loop successfully once the error dropped below our target tolerance threshold.



Wrapped up the calculations using our standard `SolverResult` package, ensuring we capture the solution vector, total iterations run, convergence status, and final residual error just like we did in Week 1.

---