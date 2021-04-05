#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

class Polynomial {
public:
    // coefficients of the polynomial in the form ax^3 + bx^2 + cx + d
    double a, b, c, d;
    // boundaries
    double from, to;

    Polynomial();
    Polynomial(double a, double b, double c, double d);
    Polynomial GetDerivative() const;
    double GetValue(double x) const;
};

#endif // POLYNOMIAL_H
