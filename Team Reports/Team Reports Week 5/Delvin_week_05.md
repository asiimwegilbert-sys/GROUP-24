Week 5 Report
Overview
This week focused on developing a standalone test suite for the sat::num::Vector module. The objective was to verify correctness of constructors, norm calculation, vector arithmetic operations, and error handling before integration with higher-level numerical modules. The testing phase ensured reliability and compliance with the project workflow requirements.
Progress
Developed standalone Vector tests.
Tested constructors.
Tested size().
Tested element access.
Tested norm().
Tested vector addition.
Tested vector subtraction.
Tested scalar multiplication.
Tested dot product.
Tested dimension mismatch exceptions.
The test suite increased confidence in the correctness of the Vector module and prepared it for integration with Matrix and trajectory-related modules. Since Vector is a dependency for other numerical components, validating its behavior helps prevent downstream errors.