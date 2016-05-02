#ifndef Rectangle_hpp
#define Rectangle_hpp

#include "Triangle.hpp"

class Rectangle : public GeometricObject{
    
public:
    
    Rectangle();
    Rectangle(const Point3D p, const Vector3D v1, const Vector3D v2);
    Rectangle(const Point3D p1, const Point3D p2, const Point3D p3, const Point3D p4);
    void operator()(const Point3D p1, const Point3D p2, const Point3D p3, const Point3D p4);
    void operator()(Rectangle& rhs);
    Rectangle& operator= (const Rectangle& rhs);
    
    virtual Rectangle*
    clone(void) const;
    
    virtual double hit(Ray& ray, Point3D& pt);
    
    virtual RGBAPixel rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual RGBAPixel rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& ray, vector<GeometricObject*>& shapes);
    
    virtual void calculateBBox();
    
    virtual BBox& getBBox();
    
    vector<Point3D> generatePoints(int samples);
    
    virtual Normal
    getNormal(Point3D& pt);
    
    Triangle t1, t2;
    int trigNumber;
};

#endif
