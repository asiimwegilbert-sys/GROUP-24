This week, I focused on building out the Matrix module, sticking 
closely to the interface architecture we mapped out in Week 1.
Inside the Matrix class, I implemented the core structural 
functions—like tracking row/column sizes and setting up zero-based 
element access. From there, I built out the primary math operations, 
including transpose, matrix addition, subtraction, matrix 
multiplication, and scalar multiplication. To make the class robust, I 
added strict error-checking to catch incompatible dimensions and 
out-of-bounds indices early.
Under the hood, I chose to keep the raw matrix data completely private, 
structuring it with row-major storage using std::vector<double>.
