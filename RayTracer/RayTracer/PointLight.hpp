#ifndef PointLight_hpp
#define PointLight_hpp

#include "Light.hpp"

class PointLight : public Light{
    
public:
    PointLight();
    PointLight(const Point3D& origin, double a, double d, double s);
    void operator()(const Point3D& origin, double a, double d, double s);
    
    Point3D o;
};

#endif
