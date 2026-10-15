# Week __ Progress Report

**First Submition:**
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
| Asher | Integration/CMake | CMake, Report integration | Integration of the commits and review | |  |
| Delvin | Vector | Report |  | | |
| Ibrahim | Matrix | report | | | |
| Derrick | Linear solvers | Report | | | |
| Stacy | Decompositions | Report | | | |
| Praise | Iterative solvers | Report | | | |
| Deogratious | Interpolation | Report | | | |
| Jeremiah | Integration/RK methods | Report | | | |
| Erick | Least squares/eigenvalues/satellite trajectory | Report | | | |

## 3. Individual Member Reports
The folowing are the copies of some of the reports the group members did about their assigned modules

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

If AI tools were used, complete every field:

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

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Deogracious:

**Assigned responsibility:** Integration
**Branch:** ``  
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/commit/3fefcdf8c2a53f34afe3342602642286cfd455e0`  
**Reviewer(s):** Gilbert, Delvin.

#### Completed

- Report

#### In Progress

- I am responsible for the interpolation module, which lets the library estimate values between known data points. In the satellite context, this means estimating a satellite's position at times the RK4 propagator did not directly compute

#### Challenges / Blockers

- Incomplete code from other members and ourselves.
- Nothing to use to run or test.


#### Next Week

- Lagrange Direct formula: weighted sum of contributions from each data point (barycentric form for stability).

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Delvin:

**Assigned responsibility:** Vectors
**Branch:** ``  
**Commits:** `https://github.com/asiimwegilbert-sys/GROUP-24/blob/feature/Delvin-project-report-1/docs/reports/report%201.md`  
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Report

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Derrick:

**Assigned responsibility:** 
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim.

#### Completed

- Report

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Praise:

**Assigned responsibility:** 
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Report

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Stacy:

**Assigned responsibility:** 
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Report

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

### Erick:

**Assigned responsibility:** 
**Branch:** ``  
**Commits:** ``  
**Reviewer(s):** Gilbert, Ibrahim, Delvin.

#### Completed

- Report

#### AI Use

If AI tools were used, complete every field:

- **Tool:** None
- **Purpose:** NOne
- **Reason it was used:** None
- **What the team verified or changed:** None

> No AI tools were used this week.

## 5. Decisions Made This Week

Record technical decisions that affect more than one module. Include the reason and affected members.

| Decision | Reason | Affected modules/members |
|---|---|---|
|  | | |
| None at the moment | | |

## 6. Issues and Blockers Requiring Team Action

| Issue | Owner | Impact | Action before next Monday |
|---|---|---|---|
| | | | |
| | | | 

## 7. Next Week's Shared Goals

1. Complete the matrix and vector module
2. Run some tests and examples 

 ## 8. Conclusion.