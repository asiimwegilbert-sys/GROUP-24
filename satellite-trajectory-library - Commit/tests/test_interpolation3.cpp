// tests/test_interpolation.cpp - Week 3 (ARINDA DEOGRATIUS KEVIN)
// Assumes interpolation.hpp provides: lagrangeInterpolate,
// newtonDividedDifferences, newtonEvaluate, polynomialFit
//
// Classes: TestResult (stores one test outcome) and InterpolationTester
// (runs tests, keeps results, reports).
// TestResult private: name, passed | public: constructor, getName, isPassed, print
// InterpolationTester private: tolerance, results, close(), throwsError(), record()
//   public: constructor, testKnownCubic, testBadInput, runAll, printReport, allPassed
// Use: main() makes one tester, runs all tests, prints the report and returns
// the exit code. Helpers are private because only the tester uses them.
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include "sat_trajectory/interpolation.hpp"
using std::vector; using std::string;
class TestResult {
private:
    string name;   // test description
    bool passed;   // true if the test passed
public:
    TestResult(const string& n, bool p) : name(n), passed(p) {}
    string getName() const { return name; }
    bool isPassed() const { return passed; }
    void print() const { std::cout << (passed ? "PASS" : "FAIL") << ": " << name << "\n"; }
};
class InterpolationTester {
private:
    double tolerance;            // how close two doubles must be to be equal
    vector<TestResult> results;  // outcome of every test run so far

    bool close(double a, double b) const { return std::fabs(a - b) < tolerance; }
    bool throwsError(const vector<double>& x, const vector<double>& y) const {
        try { lagrangeInterpolate(x, y, 0.5); }
        catch (const std::invalid_argument&) { return true; }
        return false;
    }
    bool record(const string& name, bool ok) {
        results.push_back(TestResult(name, ok)); return ok;
    }
public:
    InterpolationTester(double tol = 1e-9) : tolerance(tol) {}
    // Test 1: all three methods must match y = 2x^3 - 3x^2 + x - 5
    bool testKnownCubic() {
        vector<double> x = {-1, 0, 1, 2}, y;
        for (double xi : x) y.push_back(2*xi*xi*xi - 3*xi*xi + xi - 5);
        vector<double> newton = newtonDividedDifferences(x, y);
        vector<double> p = polynomialFit(x, y);   // p = {a0, a1, a2, a3}
        double q = 1.5, expected = 2*q*q*q - 3*q*q + q - 5;
        bool ok = close(lagrangeInterpolate(x, y, q), expected)
               && close(newtonEvaluate(x, newton, q), expected)
               && close(p[0] + p[1]*q + p[2]*q*q + p[3]*q*q*q, expected);
        return record("known cubic", ok);
    }
    // Test 2: duplicate nodes and mismatched sizes must both throw
    bool testBadInput() {
        return record("bad input throws",
            throwsError({0, 1, 1}, {0, 1, 2}) && throwsError({0, 1}, {0, 1, 2}));
    }
    void runAll() { testKnownCubic(); testBadInput(); }
    void printReport() const { for (const TestResult& r : results) r.print(); }
    bool allPassed() const {
        for (const TestResult& r : results) if (!r.isPassed()) return false;
        return true;
    }
};

int main() {
    InterpolationTester tester;   // default tolerance 1e-9
    tester.runAll(); tester.printReport();
    return tester.allPassed() ? 0 : 1;
}
