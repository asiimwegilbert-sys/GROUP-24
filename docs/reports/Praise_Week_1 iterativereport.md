Introduction
This report explains how I planned and started the iterative solvers module for our satellite trajectory project. For Week 1, my focus was on setting up our project files, designing the public interface menu, and implementing the first core math tool: the Jacobi Method. This tool helps us solve big linear equation systems as we work toward predicting satellite paths.

Architecture Design
I split the work into two files. First, a header file  acts like a menu listing our tools and result structures. Second, the source file  holds the step-by-step math instructions.
Instead of building a brand-new way to store numbers, I use standard C++ lists, helping the math tools fit smoothly with the rest of the project files.
Because iterative math loops over and over until it gets close to the right answer, we set a limit on how many times it can loop and how close the answer needs to be so it stops safely if anything gets stuck.
The solvers are hooked directly into the project's main testing system to run quick checks and make sure answers are accurate.

Brach Setup and Git Workflow
The Main Branch holds the clean, final and working version of our project code. 
The Developing Branch is where all the different working parts are brought together to see if they fit and run properly before updating the main project.
The Feature Branch is the private workspace branch where the solver code is written and tested separately. 
Clear commit notes are wriited everytime work is saved and uploaded to explain what changed.
Before adding new code into the main project, teammates review it and run tests to ensure everything works without errors.

Week 1 Implementation Tasks
Created the header file and designed the SolverResult package to neatly bundle our solution vector, iteration count, convergence status, and final residual error.
Implemented the Jacobi method by separating the main diagonal numbers from the rest of the matrix. I used a temporary working list to calculate new values safely without overwriting old ones halfway through a loop step.
Verified that matrix and vector sizes match correctly and that zero values on the diagonal are caught to prevent division errors.