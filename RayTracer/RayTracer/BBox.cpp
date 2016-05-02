#include "BBox.hpp"
#include <limits>

using namespace std;

//Default constructor creates a bounding box with no dimensions
BBox::BBox(){
    x0 = x1 = y0 = y1 = z0 = z1 = 0.0;
}

//assigns attributes to given values
void BBox::operator()(double minX, double maxX, double minY, double maxY, double minZ, double maxZ){
    this->x0 = minX;
    this->y0 = minY;
    this->z0 = minZ;
    this->x1 = maxX;
    this->y1 = maxY;
    this->z1 = maxZ;
}

//Returns whether or not a given point is inside a bounding box
bool BBox::contains(Point3D& pt){
    return (x0<=pt.x) && (y0<=pt.y) && (z0<=pt.z) && (x1>=pt.x) && (y1>=pt.y) && (z1>=pt.z);
}

//check if two bounding boxes touch each other
bool BBox::overlap(BBox& other){
    if(this->x0 > other.x1) return false;
    if(this->x1 < other.x0) return false;
    if(this->y0 > other.y1) return false;
    if(this->y1 < other.y0) return false;
    if(this->z0 > other.z1) return false;
    if(this->z1 < other.z0) return false;
    return true;
}

// #419begin #type=1 #src=https://tavianator.com/fast-branchless-raybounding-box-intersections/
//returns whether or not the viewing ray hits the bounding box
bool BBox::hitTime(const Ray& viewRay){
    double tmin = -1.0, tmax = std::numeric_limits<double>::max();
    
    if(viewRay.d.x != 0.0) {
        double tx1 = (x0 - viewRay.o.x)/viewRay.d.x;
        double tx2 = (x1 - viewRay.o.x)/viewRay.d.x;
        
        tmin = max(tmin, min(tx1, tx2));
        tmax = min(tmax, max(tx1, tx2));
    }
    
    if (viewRay.d.y != 0.0) {
        double ty1 = (y0 - viewRay.o.y)/viewRay.d.y;
        double ty2 = (y1 - viewRay.o.y)/viewRay.d.y;
        
        tmin = max(tmin, min(ty1, ty2));
        tmax = min(tmax, max(ty1, ty2));
    }
    
    if (viewRay.d.z != 0.0) {
        double tz1 = (z0 - viewRay.o.z)/viewRay.d.z;
        double tz2 = (z1 - viewRay.o.z)/viewRay.d.z;
        
        tmin = max(tmin, min(tz1, tz2));
        tmax = min(tmax, max(tz1, tz2));
    }
    
    return (tmax >= tmin);
}
// #419end