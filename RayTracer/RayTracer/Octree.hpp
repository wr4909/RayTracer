#ifndef Octree_hpp
#define Octree_hpp

#include <vector>
#include "Point3D.hpp"
#include "BBox.hpp"
#include "GeometricObject.hpp"

using namespace std;

class Ocnode{
    
public:
    Ocnode(const double x, const double y, const double z, const double length, const int height);
    
    void add(GeometricObject* shape);
    void createChildren();
    void getGeomList(Ray& viewRay, vector<GeometricObject*>& array);
    
    vector<Ocnode*> children;   //child nodes of the given OcTree node
    vector<GeometricObject*> shapes;    //shapes stored in this node (only non-empty if node is leaf node)
    Point3D* center;            //center of bounding box for this OcTree node
    double length;              //length of bounding box
    int height;                 //OcTree height for this node
    BBox box;            //bounding box
    double maxSize;             //maximum number of elements stored in this node before it branches
};

class Octree{
    
public:
    Ocnode* root;               //top of octree
    
    Octree();                   
    void add(GeometricObject* shape);
    void getGeomList(Ray& viewRay, vector<GeometricObject*>& array);
};



#endif
