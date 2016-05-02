#ifndef World_hpp
#define World_hpp

#include <vector>
#include "GeometricObject.hpp"
#include "Triangle.hpp"
#include "Sphere.hpp"
#include "Octree.hpp"
#include "Rectangle.hpp"
#include "Camera.hpp"
#include "PointLight.hpp"
#include "AreaLight.hpp"

using namespace std;

class World{
    
public:
    vector<GeometricObject*> shapes;    //list of all shapes in the space
    void addShapesToTree(vector<GeometricObject*>& objs);   //adds an arra of shapes to this world
    void addShapesToList();             //adds the shapes to an array
    void addShapesToTree();             //adds the shapes to an OcTree
    GeometricObject* getFirstObjectHit(Ray& viewRay, vector<GeometricObject*>& shapes, Point3D& hitPt);
    World();                            //constructor
    double ka;  //ambient light scale
    Octree* tree;                       //OcTree data structure for acceleration
    Camera camera;
    PointLight ptLight;
    AreaLight areaLight;
    int rayCount;
};

#endif /* World_hpp */
