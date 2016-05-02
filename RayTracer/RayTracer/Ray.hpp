#pragma once
// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

#include "Point3D.hpp"
#include "Vector3D.hpp"

class Ray{
    
public:
    
    Point3D o;
    Vector3D d;
    
    Ray(const Point3D& origin, const Vector3D& dir);
    
    Ray(const Point3D& origin, const Vector3D& dir, std::string prop);
    
    Ray(const Ray& ray);
    
    Ray& operator= (Ray& rhs);
    
    ~Ray();
    
    void operator()(const Point3D& origin, const Vector3D& dir);
    void operator()(const Ray& ray);
    
    std::string property;
    
    int recurseLevel;
};



// #end