#include "polynomial.h"
#include <vector>
#include <cmath>

Polynomial::Polynomial() : a(0), b(0), c(0), d(0) {}

Polynomial::Polynomial(double a, double b, double c, double d)
    : a(a), b(b), c(c), d(d) {}

Polynomial Polynomial::GetDerivative() const {
  return {0, 3 * a, 2 * b, c};
}

double Polynomial::GetValue(double x) const {
  return a * std::pow(x, 3) + b * std::pow(x, 2) + c * x + d;
}

Polynomial Polynomial::GetCoefficientsFromVector(std::vector<double>::iterator from) {
    return {*(from + 0), *(from + 1), *(from + 2), *(from + 3)};
}

void Polynomial::InsertCoefficientsIntoVector(std::vector<double>::iterator from) const {
    *(from + 0) = a;
    *(from + 1) = b;
    *(from + 2) = c;
    *(from + 3) = d;
}
