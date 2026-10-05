ARINDA DEOGRATIUS KEVIN 
WEEK 1 REPORT TO UNDERSTAND MY ROLE IN GROUP PROJECT 

Interpolation Lead

PROJECT: Satellite Trajectory Numerical Computing Library (C++17, from scratch)
ROLE: Lead for Interpolation Methods

1. Understanding My Role

I am responsible for the interpolation module, which lets the library estimate values between known data points. 
In the satellite context, this means estimating a satellite's position at times the RK4 propagator did not directly compute.

I am to implement and test three methods:

a) Lagrange
Direct formula: weighted sum of contributions from each data point (barycentric form for stability).

b) Newton
Divided-difference coefficients; efficient evaluation and easy to add new points.

c) Polynomial
Finds the coefficients of the unique degree n-1 polynomial through n points.

All three describe the same unique polynomial, so their results must agree. That is a key test of correctness.
