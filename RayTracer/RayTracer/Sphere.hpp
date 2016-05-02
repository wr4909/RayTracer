#ifndef Sphere_hpp
#define Sphere_hpp

#include "GeometricObject.hpp"
#include "Maths.hpp"
#include "Rectangle.hpp"
#include "AreaLight.hpp"

class Sphere : public GeometricObject{
    
public:
    
    Point3D c; //center of sphere
    double r; //radius
    
    Sphere();
    
    Sphere(const Point3D& p, const double radius);
    
    Sphere(const Point3D& p, const double radius, const Material& materialParam);
    
    Sphere(const Point3D& p, const double radius, const Material& _material, PNG* _texture);
    
    Sphere(const Sphere& s);
    
    virtual Sphere*
    clone(void) const;
    
    ~Sphere();
    
    Sphere& operator= (Sphere& rhs);
    
    virtual double hit(Ray& ray, Point3D& pt);
    
    virtual RGBAPixel castDirectionalLight(DirectionalLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual void calculateBBox();
    
    virtual BBox& getBBox();
    
    virtual Normal getNormal(Point3D& pt);
    
    virtual RGBAPixel* mapToTexture(Point3D& pt);
};

#endif