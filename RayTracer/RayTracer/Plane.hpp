#ifndef Plane_hpp
#define Plane_hpp

#include "GeometricObject.hpp"

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

class Plane : public GeometricObject{
    
public:
    
    Point3D a;
    Normal n;
    
    Plane();
    
    Plane(const Point3D& point, const Normal& normal);
    
    Plane(const Plane& plane);
    
    virtual Plane*
    clone(void) const;
    
    ~Plane();
    
    Plane& operator= (const Plane& rhs);
    
    void operator() (Point3D p, Normal normal);
    
    virtual double hit(Ray& ray, Point3D& point);
    
    virtual RGBAPixel castDirectionalLight(DirectionalLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual RGBAPixel rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    //virtual RGBAPixel rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual Normal getNormal(Point3D& pt);
    
    
};

#endif /* Plane_hpp */

// #419end