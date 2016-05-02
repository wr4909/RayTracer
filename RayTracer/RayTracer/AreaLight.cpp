#include "AreaLight.hpp"

AreaLight::AreaLight(){
}

AreaLight::AreaLight(Rectangle& geom){
    shape(geom);
    geom.isLightSrc = true;
}

AreaLight::AreaLight(const AreaLight& other){
    shape = other.shape;
}

void AreaLight::operator()(Rectangle& geom){
    shape(geom);
    geom.isLightSrc = true;
}

Normal AreaLight::getNormal(Point3D& pt){
    return shape.getNormal(pt);
}

AreaLight*
AreaLight::clone(void)const {
    return (new AreaLight(*this));
}