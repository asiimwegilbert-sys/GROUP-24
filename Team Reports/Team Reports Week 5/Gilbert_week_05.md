# Week 5 Report — Gilbert

**Role:** Team lead — project integration, CMake, release coordination  
**Project:** Satellite Trajectory Numerical Computing Library  
**Evidence:** Git history, current `main` branch, repository files, and the final build/test run

## Overview

In Week 5 I focused on bringing the team’s modules together on `main`, organizing the project’s CMake build, and preparing demonstrations that make the satellite simulation easier to run and understand. This report separates my integration/build work from code contributed by individual module owners.

## Integration and Merges to `main`

I coordinated the final integration through reviewed pull requests and checked that the combined project could be built and demonstrated. The Git history shows these module changes reaching `main`:

| Pull request | Integrated work visible in the merge |
|---|---|
| #75 | Praise’s iterative solver implementation in `src/iterative_solvers.cpp`. |
| #77 | Erick’s least-squares implementation in `src/least_squares.cpp`. |
| #78 | Deogratius’s interpolation source and tests, plus the interpolation example. |
| #79 | Jeremiah’s numerical integration implementation in `src/integration.cpp`. |
| #87 | Erick’s trajectory solver updates and expanded trajectory tests. |

Other Week 5 merges carried integration evidence and supporting build/test work: #81 updated CMake configuration; #82 added iterative-solver report/test changes; #83 added Delvin’s report and vector tests; #84 added Ibrahim’s report; #86 added Deogratius’s Week 1 report; #88 added Jeremiah’s integration report and numerical-accuracy test; and #89 added Erick’s Week 5 report. Those report/test-only merges are not described as new module implementations.

The merges represent contributions by the module owners. My responsibility was coordinating and integrating the reviewed work, not claiming authorship of those implementations.

## CMake and Build Organization

I organized the top-level `CMakeLists.txt` so that the project builds as a C++17 library and provides `BUILD_TESTS` and `BUILD_EXAMPLES` options. The library target collects `vector.cpp`, `Matrix3.cpp`, interpolation, integration, iterative solvers, linear solvers, decompositions, least squares, eigenvalues, and trajectory solver sources; it exposes the public `include/` directory and applies compiler warnings. Separate executable targets build the examples, and the test targets are registered with CTest.

At the final verification, CMake built seven demonstrations: interpolation, integration, linear algebra, satellite trajectory, trajectory interpolation, decompositions, and linear solvers. It also registered all 17 C++ test source files in `tests/`, including the earlier weekly test files after they were made into runnable tests.

My CMake-related history includes the October CMake edit and the November organization/build commits. The final project verification was:

| Command | Result |
|---|---|
| `cmake -S . -B build` | Passed |
| `cmake --build .\build` | Passed |
| `ctest --test-dir .\build --output-on-failure` | Passed: 17 of 17 tests |
| Smoke-run all configured example executables | Passed: all 7 exited successfully |

## Demonstrations and Visuals

- Extended `examples/satellite_trajectory_example.cpp` to make the simulated orbit viewable from the console and to export trajectory data as CSV and an SVG image.
- Added and updated the generated orbit assets in `data/`, including `orbit_trajectory.csv`, `orbit_trajectory.svg`, `orbit_trajectory_cpp.csv`, and `orbit_trajectory_cpp.svg`. The SVG labels the RK4 two-body simulation and plots its orbit, start, end, and Earth reference.
- Added `examples/plot_trajectory.py` as an additional workflow for turning trajectory CSV data into an SVG.
- Added `examples/orbit_live_demo.html`, a local browser-based visualization with playback, reset, speed, and drag controls. It is an educational simulation; its visual scale and drag controls are not calibrated flight predictions.
- Updated the README with build commands, orbit-demo instructions, and guidance for opening or generating the visuals.

The repository history records these visual/demo additions under my commits `c4ff2e3` (“Visuals and csv files”), `3158b60` (“Added visuals to demostrate the simulations”), and `02fdb43` (“Presenting a live demo simulation.”).

## Remaining Work and Limitations

The build and tests establish that the configured targets pass in the available Windows/MinGW environment. I did not perform a separate clean-machine build. The numerical results are demonstrations and representative tests, not certification of flight-ready orbital predictions.

## AI Use

This report was prepared with AI assistance to summarize repository history and verified project evidence. The team should review it and ensure the final submission reflects its own account of the work.
