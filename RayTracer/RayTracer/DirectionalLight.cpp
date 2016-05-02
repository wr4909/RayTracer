#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight(const Vector3D& direction, double a, double d, double s){
    dir(direction);
    ka = a;
    kd = d;
    ks = s;
}