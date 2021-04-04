#ifndef POLYNOME_H
#define POLYNOME_H


class Polynome
{
public:
    // coefficients of the polynome in the form ax^3 + bx^2 + cx + d
    double a, b, c, d;
    // boundaries
    double from, to;

    Polynome();
    Polynome(double a, double b, double c, double d);
    Polynome GetDerivative() const;
    double GetValue(double x) const;
};

#endif // POLYNOME_H
