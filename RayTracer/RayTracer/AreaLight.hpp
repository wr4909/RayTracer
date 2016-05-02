#ifndef AreaLight_hpp
#define AreaLight_hpp

#include "Rectangle.hpp"

class AreaLight : GeometricObject{
    
public:
    
    AreaLight();
    AreaLight(Rectangle& geom);
    AreaLight(const AreaLight& other);
    void operator()(Rectangle& geom);
    virtual Normal getNormal(Point3D& pt);
    virtual AreaLight* clone(void) const;
    
    Rectangle shape;
};

#endif
