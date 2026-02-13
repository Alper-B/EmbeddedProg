#ifndef AALTO_ELEC_CPP_GEOMVECTOR_CLASS
#define AALTO_ELEC_CPP_GEOMVECTOR_CLASS

#include <cmath>
#include <iostream>

class GeomVector {
public:
    GeomVector(double x, double y, double z) : x_(x), y_(y), z_(z) {}

    double Length() const;

    GeomVector operator+(const GeomVector& a);
    GeomVector operator/(double a) const;
    bool operator<(const GeomVector& a) const;
    bool operator>(const GeomVector& a) const;
    bool operator==(const GeomVector& a) const;
    bool operator!=(const GeomVector& a) const;

    friend GeomVector operator*(double a, const GeomVector& b);
    friend std::ostream& operator<<(std::ostream& out, const GeomVector& a);

private:
    double x_, y_, z_;
};

#endif