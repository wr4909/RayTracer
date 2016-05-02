#include "PointLight.hpp"

PointLight::PointLight(){
    
}

PointLight::PointLight(const Point3D& origin, double a, double d, double s){
    o(origin);
    kd = d;
    ks = s;
    ka = a;
}

void PointLight::operator()(const Point3D& origin, double a, double d, double s){
    o(origin);
    kd = d;
    ks = s;
    ka = a;
}