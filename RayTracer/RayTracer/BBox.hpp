#ifndef BBox_hpp
#define BBox_hpp

#include "Point3D.hpp"
#include "Ray.hpp"
#include <iostream>
#include <algorithm>

using namespace std;

class BBox{
    
public:
    double x0,x1,y0,y1,z0,z1;//values to help find corners of the box
    
    BBox();
    
    void operator()(const double minX, const double maxX, const double minY, const double maxY, const double minZ, const double maxZ);
    
    bool contains(Point3D& pt);
    bool overlap(BBox& other);
    bool hitTime(const Ray& viewRay);
};

#endif