# Week 1 Progress Report

**First Submission:**
**Project:** Satellite Trajectory Numerical Computing Library  
**Submitted Work:** Reports and structure of the project.

## 1. Weekly Summary

>We had to meetings, one physical and an online one to decide on thee project that was idea and had a wider coverage of the modules that we were assigned to.
>Among the project proposals the group members researched about, there included the satellite/aerospace tracjectory trackingproject, the structural engineering project, that included bridges and skyscrappers stress measurements, data science and computer imagery that included facial recognition.
> A poll was later created and considering the factorslike how popular, coverage and workload, satellite trajectory numerical computing library was chosen as our final project.
>We were able to create the structure of the code that was to handle our project.
>Gilbert assigned group members which part of the code they are to lead, and they also had to select other members to aid them.
>A plan and workflow was also drafted to aid in the smooth operation and up to date work.
## 2. Team Status Overview

| Member | Assigned module | Completed this week | In progress | Blocker | Commit/PR link |
|---|---|---|---|---|---|
| Gilbert | Integration/CMake | Initial scaffold, CMake file, member assignments, plan and workflow | Integrate member work and review | Team was still learning the CMake workflow | - |
| Delvin | Vector | Designed `Vector` constructors, storage, access, norm and operator API | Implement and test the agreed API | - | - |
| Ibrahim | Matrix | Proposed row-major storage, API, dimension rules and validation cases | Implement and test the Matrix API | Dependent on the team scaffold and build setup | commit `5645c3c` |
| Derrick | Linear solvers | Prepared initial forward/back substitution design and size/diagonal checks | Add Gaussian elimination and partial pivoting | Initial implementation used a separate C++23 named-module setup | `feature/derrick-linear-solvers` |
| Stacy | Decompositions | Documented LU, Cholesky, modified Gram-Schmidt and Householder QR designs, APIs and test plan | Implement and test the decomposition methods | Depends on the Matrix API | `feature/stacy-decompositions` |
| Praise | Iterative solvers | Report describes the solver result type and a Jacobi implementation with size and diagonal checks | Plan Gauss-Seidel and power iteration | No specific blocker reported | - |
| Deogratius | Interpolation | Researched linear, Lagrange, Newton and polynomial interpolation and its trajectory use | Turn research into function requirements and a test plan | No code was written this week, per the report | - |
| Jeremiah | Integration/RK methods | Designed header signatures for RK2, RK4, Gaussian quadrature and Romberg | Implement the numerical loops | No specific blocker reported | - |
| Erick | Least squares/eigenvalues/satellite trajectory | Implemented and tested orbital-period calculation; reports 8 registered tests passed | Resolve module dependencies and the vector-state RK interface | Decomposition/solver and integration APIs still developing | PR #8 |

## 3. Individual Member Reports
The member summaries are based on individual reports where available. Gilbert's lead-work summary is based on the Week 1 team notes; no separate individual report from him was identified.

### Gilbert (team lead):

**Assigned responsibility:** Project coordination, integration and CMake
**Source:** Week 1 team notes; no separate individual Week 1 report was identified.

#### Completed

- Helped establish the project scaffold and initial CMake setup.
- Assigned module responsibilities and organized supporting members.
- Drafted the project plan and workflow after the group selected the satellite trajectory library.

#### In Progress

- Establishing the build and review workflow and preparing to integrate member branches.

#### Challenges / Blockers

- The team notes say the group was still learning CMake and had limited time after changing project assignments.
- This is a summary of lead work recorded in the team notes, not a separately submitted personal report.

### Ibrahim:

**Assigned responsibility:** Matrix  
**Branch:** ``  
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/commit/5645c3c4e806ef728d508cc02c3eb79adf5f7063`  
 
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- Report about the matrix module he is going to do.
- ibrahim-matrix-design.md
- week-01-ibrahim.md

#### In Progress

- The next step is to implement the agreed Matrix API, add the tests and make sure it works with the group's existing CMake structure

#### Challenges / Blockers

- Incomplete code from other members and ourselves.
- Nothing to use to run or test.


#### Next Week

- I will implement the Matrix class and its tests and then connect it to the team's CMake/build structure.

#### AI Use

 

- **Tool:** Chatgpt 
- **Purpose:** Had to consult by any means to maximise understanding
- **Reason it was used:** ChatGPT was used to help organise the initial Matrix design and documentation
- **What the team verified or changed:** Checking the proposed API and implementation against the group's actual repository before merging anything

### Jeremiah:

**Assigned responsibility:** Numerical Integration
**Branch:** ``  
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/commit/eb7e49fbb7d3c7e41b2df1f54be7eca0d18839f6`  
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- For week 1, my main focus was mapping out the initial architecture for our numerical solver layout. I worked on designing the basic structure for the integration hpp header file, making sure we have the correct function blueprints ready for the runge kutta methods (both rk2 and rk4). I also laid down the initial signatures for the gaussian quadrature and romberg integration options so the entire math module template is clean

#### In Progress

- I plan to start working on the actual mathematical loops inside integration cpp to handle the state updates and orbital physics calculations.

#### Challenges / Blockers

- Incomplete code from other members and ourselves.
- Nothing to use to run or test.


#### Next Week

- Next week, I plan to start working on the actual mathematical loops inside integration cpp to handle the state updates and orbital physics calculations.

#### AI Use

- **Tool:** None.
- Jeremiah's report states that no AI tools were used this week.

### Deogratius:

**Assigned responsibility:** Interpolation methods
**Branch:** ``  
**Report:** `Team Reports/Team Reports Week 1/Deo_week1_report`  
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- Researched linear, Lagrange, Newton, and polynomial interpolation.
- Mapped the interpolation files and described how interpolation can estimate satellite positions between solver time steps.
- The report explicitly says no code was written during Week 1.

#### In Progress

- Turning the research into a function and test plan.

#### Challenges / Blockers

- Incomplete code from other members and ourselves.
- Nothing to use to run or test.


#### Next Week

- Lagrange Direct formula: weighted sum of contributions from each data point (barycentric form for stability).

#### AI Use

- No AI-use statement is included in this individual report.

### Delvin:

**Assigned responsibility:** Vectors
**Branch:** ``  
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/blob/feature/Delvin-project-report-1/docs/reports/report%201.md`  
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Designed the `sat::num::Vector` API, including default, size and initializer-list constructors; size, bounds-checked element access and norm; and the planned addition, subtraction, scalar multiplication and dot-product operations.
- Proposed `std::vector<double>` storage and documented the header structure and public interface.

#### In Progress

- Implement the designed API and add tests.

#### AI Use

- No AI-use statement is included in this individual report.

### Derrick:

**Assigned responsibility:** Linear solvers
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Prepared the initial linear-solver design for systems `A x = b`, including forward and back substitution.
- Documented square-matrix and right-hand-side size requirements, plus checks for zero or very small diagonal values.
- The report describes an initial module version; no Week 1 build/test result is included.

#### In Progress

- Add Gaussian elimination and partial pivoting.

#### AI Use

- The report includes suggested ChatGPT disclosure text.

### Praise:

**Assigned responsibility:** Iterative solvers
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Designed a header/source split and a result structure containing the solution, iteration count, convergence status and residual.
- The individual report describes implementing Jacobi with separate old/new iterates, matrix/vector size validation and zero-diagonal checks.
- The report says the solver was connected to the project's test setup; it does not provide specific test commands or outputs.

#### In Progress

- Gauss-Seidel and power iteration were included in the design plan; the Week 1 report does not claim they were implemented.

#### AI Use

- No AI-use statement is included in this individual report.

### Stacy:

**Assigned responsibility:** Matrix decompositions
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Documented the module design, API/result types, numerical assumptions, error handling and test plan for LU with partial pivoting, Cholesky, Householder QR and modified Gram-Schmidt.
- The report's checklist marks normal, edge-case and invalid-input testing, relevant test runs and a clean build as not yet completed.

#### In Progress

- Implement and test the decomposition methods after agreeing interfaces with the Matrix and solver owners.

#### AI Use

- No AI-use statement is included in this individual report.

### Erick:

**Assigned responsibility:** Least squares, eigenvalues and satellite trajectory
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Implemented the orbital-period calculation with checks for positive semi-major axis and gravitational parameter.
- Added three trajectory tests; the report says CMake/MinGW were configured and all 8 registered tests passed.
- Reviewed module dependencies and identified the mismatch between scalar RK interfaces and a satellite state containing position and velocity vectors.

#### In Progress

- Design least-squares and eigenvalue approaches and agree on the RK interface for trajectory propagation.

#### AI Use

- **Tool:** ChatGPT
- **Purpose:** Clarify requirements and dependencies, troubleshoot the CMake/MinGW setup, and assist with test design.
- **Verification:** Erick's report says AI suggestions were reviewed before use.

## 4. Decisions Made This Week

| Decision | Reason | Affected modules/members |
|---|---|---|
| None at the moment | | |

## 5. Issues and Blockers Requiring Team Action

| Issue | Owner | Impact | Action before next Monday |
|---|---|---|---|
| Matrix and Vector APIs still need implementation and alignment | Ibrahim, Delvin | Matrix operations and downstream modules depend on stable interfaces | Agree the public APIs, implement the classes and add focused tests |
| Scalar RK state does not match the satellite position/velocity state | Jeremiah, Erick | Satellite propagation cannot be finalized against the current interface | Agree on a vector-valued state interface before implementing propagation |
| Build tooling and CMake setup are still being established | Gilbert, Erick | Members need a repeatable way to build and run tests | Document and verify the CMake/MinGW workflow |

## 6. Next Week's Shared Goals

1. Complete the matrix and vector module
2. Run some tests and examples 

## 7. Conclusion

Week 1 established the project scope, team responsibilities, initial repository structure and module designs. Some initial code and tests were reported, including the orbital-period calculation, but most modules still needed implementation, integration and verification.