// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/ray-traced-images.zip

#include <math.h>
#include "Point3D.hpp"

/*
 Function name: Point3D
 Function purpose: Default Constructor
 Parameters: none
 Return value: n/a
 output: none
 */
Point3D::Point3D(){
    x = y = z = 0;
}

/*
 Function name: Point3D
 Function purpose: Constructor
 Parameters: a - sets a Point position to (a,a,a)
 Return value: n/a
 output: none
 */
Point3D::Point3D(const double a){
    x = y = z = a;
}

/*
 Function name: Point3D
 Function purpose: Constructor
 Parameters: a - sets a Point position to (a,b,c)
 Return value: n/a
 output: none
 */
Point3D::Point3D(const double a, const double b, const double c){
    x = a;
    y = b;
    z = c;
}

/*
 Function name: Point3D
 Function purpose: Copy Constructor
 Parameters: p - point to copy from
 Return value: n/a
 output: none
 */
Point3D::Point3D(const Point3D& p){
    x = p.x;
    y = p.y;
    z = p.z;
}

/*
 Function name: ~Point3D
 Function purpose: Destructor
 Parameters: none
 Return value: n/a
 output: none
 */
Point3D::~Point3D(){}

/*
 Function name: =
 Function purpose: assignment operator
 Parameters: rhs - the point to copy coordinates from
 Return value: reference to current point
 output: none
 */
Point3D& Point3D::operator=(const Point3D& rhs){
    if (this == &rhs)
        return (*this);
    
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    
    return (*this);
}

/*
 Function name: distance
 Function purpose: find distance between two points
 Parameters: p the other point
 Return value: distance between two points
 output: none
 */
double Point3D::distance(const Point3D& p) const{
    return (sqrt((x - p.x)*(x - p.x) + (y - p.y)*(y - p.y) + (z - p.z)*(z - p.z)));
}

/*
 Function name: ()
 Function purpose: call operator
 Parameters: a,b,c values to assign to current point
 Return value: none
 output: none
 */
void Point3D::operator() (const double a, const double b, const double c){
    x = a;
    y = b;
    z = c;
}

/*
 Function name: ()
 Function purpose: call operator
 Parameters: p value to copy to current point
 Return value: none
 output: none
 */
void Point3D::operator() (const Point3D& p){
    x = p.x;
    y = p.y;
    z = p.z;
}

// non-member function

// --------------------------------------------- operator*
// multiplication by a matrix on the left

Point3D
operator* (const Matrix& mat, const Point3D& p) {
    return (Point3D(mat.m[0][0] * p.x + mat.m[0][1] * p.y + mat.m[0][2] * p.z + mat.m[0][3],
                    mat.m[1][0] * p.x + mat.m[1][1] * p.y + mat.m[1][2] * p.z + mat.m[1][3],
                    mat.m[2][0] * p.x + mat.m[2][1] * p.y + mat.m[2][2] * p.z + mat.m[2][3]));
}


// #419end



std::ostream & operator<<(std::ostream & out, Point3D const & point)
{
    out << "(" << point.x << "," << point.y << ","
    << point.z << ")";
    return out;
}