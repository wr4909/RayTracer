#ifndef Triangle_hpp
#define Triangle_hpp

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

#include "GeometricObject.hpp"
#include "Plane.hpp"
#include "BBox.hpp"
class Rectangle;

class Triangle : public GeometricObject{
    
public:
    Point3D v0, v1, v2;
    Normal n;
    Plane plane;    //plane containing triangle
    
    Triangle();
    
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c);
    
    Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material& _material, PNG* _texture);
    
    Triangle(const Triangle& trig);
    
    virtual Triangle*
    clone(void) const;
    
    Triangle& operator= (const Triangle& rhs);
    
    void operator() (Point3D& a, Point3D& b, Point3D& c);
    
    void compute_normal();
    
    virtual double hit(Ray& ray, Point3D& pt);
    
    bool SameSide(Point3D& p1, Point3D& p2, Point3D& a, Point3D& b);
    
    bool PointInTriangle(Point3D& p, Point3D& a, Point3D& b, Point3D& c);
    
    virtual RGBAPixel castDirectionalLight(DirectionalLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual RGBAPixel rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual void calculateBBox();
    
    virtual BBox& getBBox();
    
    Normal getNormal(Point3D& pt);
};

#endif /* Triangle_hpp */

// #419end