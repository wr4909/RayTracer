#ifndef ViewPlane_hpp
#define ViewPlane_hpp

#include "Point3D.hpp"
#include "Vector3D.hpp"

class ViewPlane{
public:
    Point3D s;
    Vector3D hDir, vDir;
    double hres, vres;
    
    ViewPlane();
    
    ViewPlane(const Point3D& startPt, const Vector3D& hDir, const Vector3D& vDir, double horizRes, double vertRes);
    
    void operator()(const Point3D& startPt, const Vector3D& hDir, const Vector3D& vDir, double horizRes, double vertRes);
    
    Point3D getPoint(int horizIndex, int vertIndex);
};

#endif