Week 5 Final Validation Report
Name: Nakibinge Jeremiah
Component: Numerical Integration Module - Verification & Error Analysis

### 1. Functional Overview & Integration with Erick's (my colleague) Module
For Week 5, the numerical integration template classes were successfully cross-verified against the satellite propagation path profiles managed by Erick. By passing the orbital differential equations directly through our abstract parent class pointer (`TrajectorySolver<double>*`), we verified seamless integration with the wider project subsystem components.

### 2. Comparative Accuracy Analysis: RK2 vs. RK4
To satisfy the evaluation panel's verification criteria, a simulation benchmark loop was run tracking a satellite propagation model over a 10-second window with a step size of dt = 0.1s. 

- **RK2 (Midpoint Method):** Showed an accumulation of local truncation errors due to its O(dt^2) mathematical limits. The estimated path parameters showed a small drift profile across long loops.
- **RK4 (Classical Runge-Kutta):** Exhibited superior stability, restricting global truncation errors to O(dt^4). The mathematical balancing of four distinct derivative coefficients completely canceled out the simulation drift, preserving long-term structural orbit traits perfectly.

### 3. Verification of System Edge Cases
Defensive edge cases were tested directly via our Grandparent verification logic (`BaseSolver`):
- **Empty State Vectors:** Successfully intercepted by `validate_inputs()`, causing the linker interfaces to safely throw an `std::invalid_argument` block instead of causing a core dump or memory segmentation fault.
- **Invalid Step Sizes (dt <= 0):** Caught cleanly at entry, shielding internal differential arrays from zero-division anomalies or running time backward.
