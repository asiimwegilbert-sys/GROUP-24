 WEEK 2 REPORT 

NAME: ARINDA DEOGRATIUS KEVIN 
ROLE: INTERPOLATION TESTS(test data and edge cases)
WEEK TARGET:To make the library foundation usable.

Tasks Completed 
I wrote "tests/test_interpolation.cpp" (48 lines) with 2 test cases. It uses only standard C++ headers ('<iostream>', '<vector>', '<cmath>', '<stdexcept>') and no external libraries or testing frameworks.
 
  1. Known cubic (test data): data from the cubic y = 2x^3 - 3x^2 + x - 5 is interpolated by Lagrange, Newton and polynomial fit. Each result at x = 1.5 is compared with the exact value.
  
  2. Bad input throws (edge cases): 'std::invalid_argument' is expected for duplicate nodes and for x/y lists of different sizes.

 I also compiled the test file with '-Wall -Wextra' and ran it against a temporary reference implementation to confirm the tests are correct: 2/2 tests passed, 0 failures.

Full build and test output is attached to the pull request: [PR link here]

In progress

Running the tests against the group's real 'interpolation.hpp/.cpp' once it is merged, and fixing any mismatch in function names or behaviour.
 Confirming my test file is picked up by Gilbert's CMake configuration.

Blockers

The tests assume this API: 'lagrangeInterpolate', 'newtonDividedDifferences', 'newtonEvaluate', 'polynomialFit', throwing 'std::invalid_argument' on bad input. If the implementation uses different names or behaviour, I need to know them. 
 Waiting on the CMake setup so the tests can be built through the project build.

Next week

I am to  run the two tests against the merged implementation if it is ready and fix any failures.

I expect to add more edge cases: exact values at the nodes, unsorted nodes, queries near a node, empty input and a single point.

Also add accuracy tests: sin(x) against the theoretical error bound, and Runge's function with equispaced versus Chebyshev nodes.

I want to add a circular-orbit interpolation example to link the module to the satellite part of the project.

I am to add Newton-specific tests (for example, adding a new node and reusing coefficients).

I will then update the tests to use the group's 'Vector' class once it is available.

 AI-use

Tool: Claude
To make research on how it i could possibly run interpolation tests in C++ and to know what the structure of the 'test_interpolation.cpp' file would look like. 
