#include "polynome.h"
#include <cmath>

Polynome::Polynome(): a(0), b(0), c(0), d(0) {}

Polynome::Polynome(double a, double b, double c, double d): a(a), b(b), c(c), d(d) {}

Polynome Polynome::GetDerivative() const {
    return Polynome(0, 3*a, 2*b, c);
}

double Polynome::GetValue(double x) const {
    return a * std::pow(x, 3) + b * std::pow(x, 2) + c * x + d;
}
