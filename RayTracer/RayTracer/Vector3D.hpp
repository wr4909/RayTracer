#ifndef Vector3D_hpp
#define Vector3D_hpp

#include <string>
#include "Matrix.hpp"
// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/ray-traced-images.zip

class Normal;
class Point3D;

class Vector3D{
    
public:
    
    double x, y, z,w;
    
    Vector3D();
    Vector3D(double a);
    Vector3D(double _x, double _y, double _z);
    Vector3D(double _x, double _y, double _z, double _w);
    Vector3D(const Vector3D& v);
    Vector3D(const Normal& n);
    Vector3D(const Point3D& p);
    Vector3D(const Point3D& p1, const Point3D& p2);
    
    ~Vector3D();
    
    Vector3D& operator= (const Vector3D& rhs);
    Vector3D& operator= (const Normal& rhs);
    Vector3D& operator= (const Point3D& rhs);
    Vector3D operator- (void) const;
    Vector3D operator* (const double scale) const;
    Vector3D operator- (const Vector3D& v) const;
    Vector3D operator/ (const double a) const;
    
    Vector3D operator+ (const Vector3D& v) const;
    
    Vector3D& operator+= (const Vector3D& v);
    
    double operator* (const Vector3D& b) const; //dot product
    
    Vector3D operator^ (const Vector3D& v) const; //cross product
    
    void operator() (const double _x, const double _y, const double _z);
    void operator() (const Vector3D& v);
    
    double length();
    
    double len_squared();
    
    double dot(const Normal& v) const;
    
    double dot(const Vector3D& v) const;
    
    void normalize();
    
    Vector3D& hat();
    
    Vector3D cross(const Vector3D& v) const;
    
    Vector3D reflect() const;
    
    //#419end
    
};

std::ostream & operator<<(std::ostream & out, Vector3D const & v);

inline Vector3D
Vector3D::operator- (void) const {
    return (Vector3D(-x, -y, -z));
}


// ---------------------------------------------------------------------  len_squared
// the square of the length

inline double
Vector3D::len_squared(void) {
    return (x * x + y * y + z * z);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Vector3D
Vector3D::operator* (const double a) const {
    return (Vector3D(x * a, y * a, z * a));
}

// ----------------------------------------------------------------------- operator/
// division by a double

inline Vector3D
Vector3D::operator/ (const double a) const {
    return (Vector3D(x / a, y / a, z / a));
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vector3D
Vector3D::operator+ (const Vector3D& v) const {
    return (Vector3D(x + v.x, y + v.y, z + v.z));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vector3D
Vector3D::operator- (const Vector3D& v) const {
    return (Vector3D(x - v.x, y - v.y, z - v.z));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline double
Vector3D::operator* (const Vector3D& v) const {
    return (x * v.x + y * v.y + z * v.z);
}


// ----------------------------------------------------------------------- operator^
// cross product

inline Vector3D
Vector3D::operator^ (const Vector3D& v) const {
    return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector3D&
Vector3D::operator+= (const Vector3D& v) {
    x += v.x; y += v.y; z += v.z;
    return (*this);
}

// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Vector3D 											// prototype
operator* (const double a, const Vector3D& v);

inline Vector3D
operator* (const double a, const Vector3D& v) {
    return (Vector3D(a * v.x, a * v.y, a * v.z));
}

// non-inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a matrix on the left

Vector3D 											// prototype
operator* (const Matrix& mat, const Vector3D& v);

#endif