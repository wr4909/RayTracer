#include "Normal.hpp"
// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

/*
 Function name: Normal
 Function purpose: Default Constructor
 Parameters: none
 Return value: n/a
 output: none
 */
Normal::Normal(){
    x = y = z = 0.0;
}

/*
 Function name: Normal
 Function purpose: Constructor
 Parameters: a - sets a Normal vector to (a,a,a)
 Return value: n/a
 output: none
 */
Normal::Normal(double a){
    x = y = z = a;
}

/*
 Function name: Normal
 Function purpose: Constructor
 Parameters: _x,_y,_z coordinates to assign the Normal's coordinates to
 Return value: n/a
 output: none
 */
Normal::Normal(double _x, double _y, double _z){
    x = _x;
    y = _y;
    z = _z;
}

/*
 Function name: Normal
 Function purpose: Copy Constructor
 Parameters: n - Normal vector to copy from
 Return value: n/a
 output: none
 */
Normal::Normal(const Normal& n){
    x = n.x;
    y = n.y;
    z = n.z;
}

/*
 Function name: Normal
 Function purpose: Copy Constructor
 Parameters: v - regular vector to copy from
 Return value: n/a
 output: none
 */
Normal::Normal(const Vector3D& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

/*
 Function name: Normal
 Function purpose: Destructor
 Parameters: none
 Return value: n/a
 output: none
 */
Normal::~Normal(){
    
}

Normal&
Normal::operator= (const Normal& rhs) {
    if (this == &rhs)
        return (*this);
    
    x = rhs.x; y = rhs.y; z = rhs.z;
    
    return (*this);
}

Normal Normal::reflect() const{
    Normal temp(-x,-y, -z);
    return temp;
}

Normal&
Normal::operator= (const Vector3D& rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

Normal&
Normal::operator= (const Point3D& rhs) {
    x = rhs.x; y = rhs.y; z = rhs.z;
    return (*this);
}

/*
 Function name: normalize
 Function purpose: scales normal vector to unit normal vector
 Parameters: none
 Return value: n/a
 output: none
 */
void Normal::normalize(){
    double length = sqrt(x*x + y*y + z*z);
    x /= length; y /= length; y /= length;
}

/*
 Function name: ()
 Function purpose: Assign Call Operator
 Parameters: _x,_y,_z - coordinate values to assign to Normal vector
 Return value: n/a
 output: none
 */
void Normal::operator() (const double _x, const double _y, const double _z){
    x = _x;
    y = _y;
    z = _z;
}

/*
 Function name: ()
 Function purpose: Copy Assign Call Operator
 Parameters: v - vector's values to assign to Normal vector
 Return value: n/a
 output: none
 */
void Normal::operator() (const Vector3D& v){
    x = v.x;
    y = v.y;
    z = v.z;
}

// #419end