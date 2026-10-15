Introduction
This report explains how I design and planned the iterative solvers part of our satellite trajectory project. I am going to use three tools namely, Jacobi, Gauss-Seidel and Power Iteration. They are going to help solve big equation systems and find important numbers that is Eigen values, quickly and safely.
Architecture Design
The code is organized to be neat and easy for everyone on the team to read and work with, thsis is how the setup is.
The menu is separated from the work, this is through splitting the work into two files. First, the header file acting like a menu that lists all the tools we can use. Secondly, the source file having the actual step by step math instructions.
Instead of building a brand new way to store numbers, standard C++ lists. This helps the math tools to fit smoothly with the rest of the project files without needing complicated extra setups.
Since iterative math loops over and over until it gets close to the right answer, it could theoretically run forever, using safety rules fixes this. A limit on how many times it can loop is set and how close the answer needs to be is also set. So if the math gets stuck or doesn’t work, the program stops safely and tells us.
For testing, the solvers are hooked directly into the projects main testing system that let us run quick checks to make sure the math answers are accurate, even when testing difficult or tricky numbers.
Brach Setup and Git Workflow
The Main Branch holds the clean, final and working version of our project code. 
The Developing Branch is where all the different working parts are brought together to see if they fit and run properly before updating the main project.
The Feature Branch is the private workspace branch where the solver code is written and tested. Using this keeps changes separate until they are completely ready.
The clear commit notes explain what changed every time work is saved and uploaded.
Before adding the new solver code into the main project, teammates review it and run the tests to make sure everything works without errors.
Plans and Implementation Tasks
•	Writing the Math Code
In the Jacobi Method, the main diagonal numbers are separated from the rest of the matrix. This lets us calculate new values safely without overwriting the old ones halfway through a loop step.
In the Gauss-Seidel Method, the newest numbers are used to calculate instead of waiting for a full step to finish. This helps it reach the final answer faster.
In the power iteration, a repeating loop is setup to multiply matrices and vectors, clean up the numbers at each step and find the most important scaling factor.
•	Testing the code 
During standard check, Jacobi and Gauss-Seidel solvers are run on easy math problems to make sure they converge to the correct answers.
During the Edge Cases and safety limits test, difficult situations like when the numbers don’t line up neatly or when a math problem hits the maximum iteration safety limit are tested.
During the Eigen value Check, the power iteration tool is tested against numbers that are already known as correct to verify accuracy.
•	Final Checks and summing up all together.
Once all the code and tests are written, the full build and test commands are run together to make sure everything passes smoothly.
