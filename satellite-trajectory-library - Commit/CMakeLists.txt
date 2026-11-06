cmake_minimum_required(VERSION 3.16)
project(satellite_trajectory_library VERSION 0.1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
option(BUILD_TESTS "Build tests" OFF)
option(BUILD_EXAMPLES "Build examples" ON)
add_library(satellite_trajectory
    src/vector.cpp
    src/Matrix3.cpp
    src/interpolation.cpp
    src/integration.cpp
    src/iterative_solvers.cpp
    src/linear_solvers.cpp
    src/decompositions.cpp
    src/least_squares.cpp
    src/eigenvalues.cpp
    src/trajectory_solver.cpp
)
target_include_directories(satellite_trajectory PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(satellite_trajectory PUBLIC cxx_std_17)
#Compiler Warnings 
if(MSVC)
  target_compile_options(satellite_trajectory PRIVATE /W4)
else()
  target_compile_options(satellite_trajectory PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Build examples and tests
if(BUILD_EXAMPLES)
  foreach(name IN ITEMS interpolation integration linear_algebra satellite_trajectory)
    add_executable(${name}_example examples/${name}_example.cpp)
    target_link_libraries(${name}_example PRIVATE satellite_trajectory)
  endforeach()
endif()

# Build tests
if(BUILD_TESTS)
  enable_testing()

  # Only include the test sources that correspond to real, compilable tests.
  # Several legacy files in tests/ are placeholders or misnamed and are intentionally excluded
  # until they are restored or renamed to a stable, valid target name.
  foreach(name IN ITEMS
      matrix
      vector
      linear_solvers
      decompositions
      eigenvalues
      integration
      least_squares
      solvers
      trajectory
  )
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/tests/test_${name}.cpp")
      add_executable(test_${name} "tests/test_${name}.cpp")
      target_link_libraries(test_${name} PRIVATE satellite_trajectory)
      add_test(NAME ${name}_tests COMMAND test_${name})
    endif()
  endforeach()
endif()
