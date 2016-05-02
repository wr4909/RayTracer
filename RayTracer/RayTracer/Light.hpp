#ifndef Light_hpp
#define Light_hpp

#include <string>
#include "Ray.hpp"
#include "rgbapixel.h"

using namespace std;

class Light{
    
public:
    Light();
    double kd;  //diffuse intensity
    double ks;  //specular intensity
    double ka;  //ambient intensity
    double e;   //specular exponent
};

#endif