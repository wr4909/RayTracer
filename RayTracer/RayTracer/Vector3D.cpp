// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/ray-traced-images.zip

#include <math.h>

#include "Vector3D.hpp"
#include "Normal.hpp"
#include "Point3D.hpp"

Vector3D::Vector3D(){
    x = y = z = 0.0;
    w = 1;
}

Vector3D::Vector3D(double a){
    x = y = z = a;
}

Vector3D::Vector3D(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

Vector3D::Vector3D(double _x, double _y, double _z, double _w){
    x = _x;
    y = _y;
    z = _z;
    w = _w;
}

Vector3D::Vector3D(const Vector3D& vector){
    x = vector.x;
    y = vector.y;
    z = vector.z;
}

Vector3D::Vector3D(const Normal& n){
    x = n.x;
    y = n.y;
    z = n.z;
}

Vector3D::Vector3D(const Point3D& p){
    x = p.x;
    y = p.y;
    z = p.z;
}

Vector3D::Vector3D(const Point3D& p1, const Point3D& p2){
    x = p2.x - p1.x;
    y = p2.y - p1.y;
    z = p2.z - p1.z;
}

Vector3D::~Vector3D(){}

Vector3D& Vector3D::operator= (const Vector3D& rhs){
    if (this == &rhs)
        return (*this);
    
    x = rhs.x; y = rhs.y; z = rhs.z;
    
    return (*this);
}

Vector3D& Vector3D::operator= (const Normal& rhs){
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

Vector3D& Vector3D::operator= (const Point3D& rhs){
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

double Vector3D::length(){
    return sqrt(x*x + y*y + z*z);
}

void Vector3D::normalize(){
    double length = sqrt(x*x + y*y + z*z);
    x /= length; y /= length; z /= length;
}

Vector3D& Vector3D::hat(){
    double length = sqrt(x*x + y*y + z*z);
    x /= length; y /= length; z /= length;
    return (*this);
}

// #419end

void Vector3D::operator() (const double _x, const double _y, const double _z){
    x = _x;
    y = _y;
    z = _z;
}

void Vector3D::operator() (const Vector3D& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

double Vector3D::dot(const Normal& v) const{
    return (x*v.x) + (y*v.y) + (z*v.z);
}

double Vector3D::dot(const Vector3D& v) const{
    return (x*v.x) + (y*v.y) + (z*v.z);
}

Vector3D Vector3D::cross(const Vector3D& v) const{
    Vector3D temp((y*v.z) - (z*v.y), (z*v.x) - (x*v.z), (x*v.y) - (y*v.x));
    temp.normalize();
    return temp;
}

Vector3D Vector3D::reflect() const{
    Vector3D temp(-x,-y, -z);
    return temp;
}

Vector3D
operator* (const Matrix& mat, const Vector3D& v) {
    return (Vector3D(mat.m[0][0] * v.x + mat.m[0][1] * v.y + mat.m[0][2] * v.z + mat.m[0][3] * v.w,
                    mat.m[1][0] * v.x + mat.m[1][1] * v.y + mat.m[1][2] * v.z + mat.m[1][3] * v.w,
                    mat.m[2][0] * v.x + mat.m[2][1] * v.y + mat.m[2][2] * v.z + mat.m[2][3] * v.w,
                    mat.m[3][0] * v.x + mat.m[3][1] * v.y + mat.m[3][2] * v.z + mat.m[3][3] * v.w));
}

std::ostream & operator<<(std::ostream & out, Vector3D const & v)
{
    out << "(" << v.x << "," << v.y << ","
    << v.z<< ")";
    return out;
}