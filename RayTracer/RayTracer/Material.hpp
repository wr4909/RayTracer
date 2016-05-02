#ifndef Material_hpp
#define Material_hpp

#include <string>
#include "rgbapixel.h"

class Material{
public:
    RGBAPixel color;
    double kd;
    double ks;
    double directScale;
    double ior; //index of refraction
    std::string reflectProperty;
    double transparency;
    
    Material();
    Material(const RGBAPixel& c, double d, double s);
    Material(const RGBAPixel& c, double d, double s, std::string& property);
    
    void operator()();
    void operator()(const RGBAPixel& c, double d, double s);
    void operator()(const Material& material);
};

#endif
