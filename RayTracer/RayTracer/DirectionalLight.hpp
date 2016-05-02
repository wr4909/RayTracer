#ifndef DirectionalLight_hpp
#define DirectionalLight_hpp

#include "Light.hpp"

class DirectionalLight : Light{
    
public:
    DirectionalLight(const Vector3D& origin, double a, double d, double s);
    
    Vector3D dir;
};

#endif
