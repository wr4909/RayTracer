// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

#include "Ray.hpp"
#include <math.h>

Ray::Ray(const Point3D& origin, const Vector3D& dir){
    o(origin.x, origin.y, origin.z);
    d(dir.x, dir.y, dir.z);
    d.normalize();
}

Ray::Ray(const Point3D& origin, const Vector3D& dir, std::string prop){
    o(origin.x, origin.y, origin.z);
    d(dir.x, dir.y, dir.z);
    d.normalize();
    property = prop;
}

Ray::Ray(const Ray& ray){
    o(ray.o.x, ray.o.y, ray.o.z);
    d(ray.d.x, ray.d.y, ray.d.z);
    d.normalize();
}

Ray& Ray::operator= (Ray& rhs){
    if (this == &rhs)
        return (*this);
    
    o = rhs.o;
    d = rhs.d;
    d.normalize();
    
    return (*this);
}

Ray::~Ray(){
    
}

void Ray::operator()(const Point3D& origin, const Vector3D& dir){
    o(origin.x, origin.y, origin.z);
    d(dir.x, dir.y, dir.z);
    d.normalize();
}

void Ray::operator()(const Ray& ray){
    o(ray.o.x, ray.o.y, ray.o.z);
    d(ray.d.x, ray.d.y, ray.d.z);
    d.normalize();
}

// #end

