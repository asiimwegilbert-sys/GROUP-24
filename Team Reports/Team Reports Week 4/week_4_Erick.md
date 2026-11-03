# Week 4 Progress Report – Erick

# Completed

* Reviewed the finalized vector-based RK2 and RK4 integration interface.
* Updated the satellite trajectory module to use the RK2/RK4 integration functions.
* Represented the satellite propagation state as:

  * Position: `[x, y, z]`
  * Velocity: `[vx, vy, vz]`
* Implemented conversion between `OrbitalState` and the six-component RK state vector.
* Implemented the two-body gravitational model:

$$
\mathbf{a}=-\frac{\mu}{|\mathbf{r}|^3}\mathbf{r}
$$

* Implemented satellite propagation using:

  * `propagate_rk2()`
  * `propagate_rk4()`
* Retained the existing validation for invalid position/velocity dimensions, time step, propagation steps, and gravitational parameter.

# OOP Concepts Applied

# Inheritance

The updated integration module uses inheritance to create specialized numerical solvers from common base classes.

Examples include:

```cpp
class TrajectorySolver : public BaseSolver
```

```cpp
class MidpointSolver : public TrajectorySolver
```

```cpp
class ClassicalRK4Solver : public TrajectorySolver
```

This allows the RK2 and RK4 solvers to share common validation and solver behaviour.

# Polymorphism

Runtime polymorphism is implemented through virtual functions such as:

```cpp
virtual State compute_step(...)
```

The derived RK2 and RK4 solver classes override this method using:

```cpp
override
```

A base-class pointer can therefore call the appropriate RK2 or RK4 implementation at runtime.

# Encapsulation

Solver data and behaviour are grouped within classes. For example, `TrajectorySolver` manages the `time_step` internally and exposes numerical behaviour through solver methods rather than allowing external code to directly control the implementation details.

# In Progress

* Testing RK2 and RK4 satellite propagation using a circular Earth orbit.
* Checking numerical accuracy over a complete orbital period.

# Challenges

* The trajectory implementation depended on the RK integration interface being updated from scalar states to vector states.
* Integration between the trajectory and RK modules required agreement on a common six-component state representation.

# Next Week

* Complete circular-orbit trajectory tests.
* Compare RK2 and RK4 accuracy.
* Validate orbital behaviour over longer propagation periods.
* Continue eigenvalue and least-squares work as their required dependencies become available.

## AI Use

* **Tool:** ChatGPT
* **Purpose:** Used to review the updated RK interface, structure the satellite propagation implementation, verify the two-body orbital model, and identify OOP concepts used in the updated integration design.
* **Reason:** To support understanding of the numerical integration architecture and correctly connect the satellite trajectory module to the RK2/RK4 implementation.
