Week 2 Progress Report
Name: Nakibinge Jeremiah
Component: Numerical Integration

For week 2, I focused on making sure our simulation pipeline is completely stable before running any mathematics. I wrote a basic verification helper function called validate_simulation_inputs. This checks if the state array is completely empty or if the time step variable dt is negative or zero before running the solvers. 

This ensures that the RK2 and RK4 calculation steps will not crash if bad input data is passed to them. Everything compiles cleanly with zero warnings. Next week I will start aligning this logic with our main project wrapper.
