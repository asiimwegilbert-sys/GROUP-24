#include <cassert>
#include <iostream>

int main()
{
    using sat::num::Vector;

    Vector v1{1,2,3};

    // Constructor test
    assert(v1.size() == 3);

    // Access test
    assert(v1[0] == 1);
    assert(v1[1] == 2);
    assert(v1[2] == 3);

    // Norm test
    Vector n{3,4};
    assert(std::abs(n.norm() - 5.0) < 1e-9);

    // Addition
    Vector a{1,2,3};
    Vector b{4,5,6};

    Vector c = a + b;

    assert(c[0] == 5);
    assert(c[1] == 7);
    assert(c[2] == 9);

    // Subtraction
    Vector d = b - a;

    assert(d[0] == 3);
    assert(d[1] == 3);
    assert(d[2] == 3);

    // Scalar multiplication
    Vector e = 2.0 * a;

    assert(e[0] == 2);
    assert(e[1] == 4);
    assert(e[2] == 6);

    // Dot product
    assert(dot(a,b) == 32);

    std::cout << "All Vector tests passed\n";
}