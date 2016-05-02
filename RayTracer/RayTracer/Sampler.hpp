#ifndef Sampler_hpp
#define Sampler_hpp

#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Triangle.hpp"
#include "Plane.hpp"
#include "Sphere.hpp"
#include "Maths.hpp"
#include "Camera.hpp"
#include <vector>
#include <string>
#include "World.hpp"

using namespace std;

class Sampler{
    
public:
    vector<Point3D> samples;
    vector<Point3D> hemisphereSamples;
    
    Sampler();
    void multijitter(vector<Point3D>& samplePts, ViewPlane& viewplane, int hindex, int vindex, int numSamples);
};

#endif
