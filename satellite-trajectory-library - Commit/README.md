# Satellite Trajectory Numerical Computing Library

## Description
A reusable C++ numerical-computing library with satellite trajectory analysis as its main demonstration.
The program uses the following methods to track the satellite trajhectory, predicting the path of a spacecraft orbiting Earth or moving between planets.
| Numerical method                 | Satellite-trajectory use                          |
| -------------------------------- | ---------------------------------------------------------- |
| Lagrange interpolation           | Estimate satellite position between known time samples     |
| Newton interpolation             | Efficient interpolation of trajectory data                 |
| Polynomial interpolation         | Approximate position, velocity, or altitude functions      |
| Jacobi iteration                 | Solve selected linear systems iteratively                  |
| Gauss–Seidel iteration           | Solve systems such as numerical estimation problems        |
| RK2                              | Basic satellite trajectory propagation                     |
| RK4                              | More accurate satellite trajectory propagation             |
| Gaussian quadrature              | Approximate orbital integrals                              |
| Romberg integration              | High-accuracy integration of trajectory-related functions  |
| Least-squares polynomial fitting | Fit altitude or position data                              |
| Gaussian elimination             | Solve matrix equations                                     |
| LU decomposition                 | Repeated linear-system solutions                           |
| Cholesky decomposition           | Solve symmetric positive-definite systems                  |
| QR decomposition                 | Stable least-squares calculations                          |
| Gram–Schmidt orthogonalization   | Construct orthogonal bases and support QR                  |
| Matrix inversion                 | Invert small matrices when required                        |
| Determinant computation          | Analyze matrix properties and singularity                  |
| Power iteration                  | Estimate the dominant eigenvalue and eigenvector           |
| Eigenvalue computation           | Analyze matrices arising from trajectory or fitting models |
| Least-squares solution           | Estimate trajectory parameters from observations           |

## Required methods
Lagrange interpolation; Newton interpolation; polynomial interpolation; Jacobi; Gauss-Seidel; RK2; RK4; Gaussian quadrature; least-squares polynomial fitting; Romberg integration; Gaussian elimination; LU; Cholesky; QR; Gram-Schmidt; matrix inversion; determinant; power iteration; eigenvalue computation; least-squares solution.

## Build
The project is configured to build with tests enabled by default.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

If you want to build only the library and examples without tests:

```bash
cmake -S . -B build_no_tests -DBUILD_TESTS=OFF -DBUILD_EXAMPLES=ON
cmake --build build_no_tests
```

## Orbit demo
Build and run the console demo:

```powershell
cmake -S . -B build
cmake --build build --config Debug
.\build\satellite_trajectory_example.exe
```

The demo prints an ASCII orbit view and selected position/altitude samples. To
generate the standalone SVG directly from C++ (no Python needed), run:

```powershell
.\build\satellite_trajectory_example.exe --svg data\orbit_trajectory.svg
```

Open the SVG in a browser to view the orbit plot. You can also generate both
the SVG and CSV in one run:

```powershell
.\build\satellite_trajectory_example.exe --svg data\orbit_trajectory.svg --csv data\orbit_trajectory.csv
```

The optional `examples\plot_trajectory.py` script can still create an SVG from
the simulation output if you prefer the Python workflow.

## Structure
- `include/`: public interfaces
- `src/`: implementations
- `tests/`: tests
- `examples/`: usage demonstrations
- `reports/`: weekly and final reports
- `data/`: optional input and generated output

## AI-use declaration
- Tool: Manus AI
- Purpose: Creating the frame, structure and blueprint, and also to organise the workflow of our project.
- Reason: To provide a structure for the group to review and complete, since we didnt know some of the work required, like the src, and also how to present the frame of the project. It made the layout just like it was needed. 
- What was changed: We included our CMake file, report status, team assignments, and also edited the workflow to allign with our needs and proposals.
