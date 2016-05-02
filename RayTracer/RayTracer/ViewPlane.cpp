#include "ViewPlane.hpp"

ViewPlane::ViewPlane(){
    s(0,0,0);
    hres = 0;
    vres = 0;
    hDir(0,0,0);
    vDir(0,0,0);
}

ViewPlane::ViewPlane(const Point3D& startPt, const Vector3D& hDir, const Vector3D& vDir, double horizRes, double vertRes){
    s = startPt;
    hres = horizRes;
    vres = vertRes;
    this->hDir = hDir;
    this->vDir = vDir;
}

void ViewPlane::operator()(const Point3D& startPt, const Vector3D& hDir, const Vector3D& vDir, double horizRes, double vertRes){
    s = startPt;
    hres = horizRes;
    vres = vertRes;
    this->hDir = hDir;
    this->vDir = vDir;
}

Point3D ViewPlane::getPoint(int horizIndex, int vertIndex){
    Point3D tempPt(s + (hDir*horizIndex/hres) + (vDir*vertIndex/vres));
    return tempPt;
}