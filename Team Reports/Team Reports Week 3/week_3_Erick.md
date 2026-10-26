# Week 3 Progress Report – Erick
# Completed

* Reviewed the updated RK2/RK4 integration work and confirmed that the integration module is being extended from scalar states to vector states.
* Identified the remaining mismatch between `integration.hpp` and `integration.cpp`.
* Defined the satellite propagation state in terms of 3D position and velocity components.
* Added validation for satellite propagation inputs, including:

  * Invalid position or velocity dimensions.
  * Non-positive time step.
  * Zero propagation steps.
  * Non-positive gravitational parameter.
* Updated trajectory tests to cover the new validation cases.
* Retained and verified the previously implemented orbital period calculation.

# In Progress

* Preparing the two-body orbital dynamics required for satellite propagation.
* Preparing trajectory tests for a circular Earth orbit.
* Waiting for the RK2/RK4 vector-state interface to be finalized before implementing full propagation.

# Challenges / Blockers

* The RK integration header and source files are not yet fully aligned.
* RK4 vector-state propagation is still incomplete, so `propagate_rk2()` and `propagate_rk4()` cannot yet be finalized.

# Next Week

* Finalize integration with the RK2/RK4 vector-state interface.
* Implement the two-body gravitational acceleration model.
* Complete satellite propagation using RK2 and RK4.
* Run trajectory accuracy and circular-orbit tests.

# AI Use

* **Tool:** ChatGPT
* **Purpose:** Used to review the RK interface, identify integration issues, design trajectory validation, and prepare trajectory test cases.
* **Reason:** To support understanding of the numerical integration requirements and organize the satellite trajectory implementation.
