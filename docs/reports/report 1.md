# Report on sat::num::Vector Class Progress

## Purpose in Project
The `sat::num::Vector` class is a foundational component for the Satellite Trajectory Numerical Computing Library. It provides a clean abstraction for handling mathematical vectors, which are essential in numerical simulations, trajectory calculations, and linear algebra operations.

---

## Step-by-Step Breakdown

### 1. Header Guard
```cpp
#pragma once
Ensures the header file is included only once during compilation.

    2. The includes;
#include <cstddef> - Provides std::size_t for safe indexing
#include <initializer_list> - Enables convenient initialization of vectors.
#include <vector> - Provides dynamic array storage for vector elements.

    3. The namespace;
    namespace sat::num { - Organizes code under sat::num to avoid naming conflicts.

    4. Class Declaration;
    class Vector { - Defines the vector class to represent mathematical vectors

    5. Constructors;
    (i) Default constructor;
    Vector() = default; - Creates an empty vector.
    (ii) Size constructor;
    explicit Vector(std::size_t size, double value = 0.0); - Initializes a vector of given size with all elements set to a specified value.
    (iii) Initializer List Constructor;
    Vector(std::initializer_list<double> values); - Allows direct initialization with a list of values.
    
    6. Member Functions;
    (i) Size;
    std::size_t size() const noexcept; - Returns the number of elements in the vector
    (ii) Element Access;
    double& operator[](std::size_t index);
const double& operator[](std::size_t index) const; - Provides indexed access to elements. Non-const version allows modification, const version ensures read-only access.
    (iii) Norm;
    double norm() const; - Computes the magnitude of the vector.

    7. Private Data Member;
    std::vector<double> values_; - Stores the vector’s numerical values using dynamic array storage.

    8. Non-Member Operator Overloads;
    (i) Addition;
    Vector operator+(const Vector&, const Vector&); - Performs element-wise vector addition.
    (ii) Subtraction;
    Vector operator-(const Vector&, const Vector&); - Performs element-wise vector subtraction.
    (iii) Scalar Multiplication;
    Vector operator*(double, const Vector&); - Scales a vector by a scalar value.
    (iv) Dot Product;
    double dot(const Vector&, const Vector&); - Computes the dot product, returning a scalar.

    Conclusion
The sat::num::Vector class establishes a robust base for numerical computing in the project. It balances simplicity with extensibility, ensuring that future trajectory and satellite computations can be built on a reliable vector abstraction.













