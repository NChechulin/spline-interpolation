#include "polynome.h"


Polynome::Polynome(double a, double b, double c, double d): a(a), b(b), c(c), d(d) {}

Polynome Polynome::GetDerivative() const {
    return Polynome(0, 3*a, 2*b, c);
}
