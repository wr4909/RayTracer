#include "World.hpp"
#include "Instance.hpp"

World::World(){
    ka = 1.0;
    ptLight(Point3D(512,512,1000),ka, 0.7, 0.5); //point light
    Rectangle rect1(Point3D(500,50,600),Vector3D(0,300,300),Vector3D(300,0,0));
    areaLight(rect1);
    addShapesToList();
    rayCount = 0;
}

GeometricObject* World::getFirstObjectHit(Ray& viewRay, vector<GeometricObject*>& list, Point3D& hitPt){
    double shortestTime = pow(10, 6);
    double tempTime = 1000;
    
    GeometricObject* object = NULL;
    
    for (int k = 0; k < list.size(); k++){
        tempTime = (*(list[k])).hit(viewRay, hitPt);
        if (0 < tempTime && tempTime < shortestTime){
            shortestTime = tempTime;
            object = list[k];
        }
    }
    return object;
}

void World::addShapesToList(){
    PNG* texture = new PNG("./input/fire_texture.png");
    string property = "glossy";
    Material redMaterial(RGBAPixel(255,0,0), 0.7, 0.7);
    redMaterial.ior = 1.8;
    redMaterial.transparency = 0.5;
    Material purpleMaterial(RGBAPixel(255,0,255),0.5,0.5);
    Material greenMaterial(RGBAPixel(0,255,0), 0.5, 0.5, property);
    Material blueMaterial(RGBAPixel(0,0,255),0.7,0.5, property);
    
    Sphere* s1 = new Sphere(Point3D(512-150,600,300), 150, purpleMaterial);
    shapes.push_back(s1);
    
    Sphere* s2 = new Sphere(Point3D(512+150,600,300), 150, blueMaterial);
    shapes.push_back(s2);
    
    Sphere* s3 = new Sphere(Point3D(512-300,600,700), 100, greenMaterial);
    shapes.push_back(s3);
    
    Sphere* s4 = new Sphere(Point3D(512,600,500), 50, redMaterial);
    shapes.push_back(s4);
    
    Sphere* s5 = new Sphere(Point3D(512+150,600,700), 150, greenMaterial, texture);
    shapes.push_back(s5);
}

void World::addShapesToTree(vector<GeometricObject*>& objs){
    tree = new Octree();
    for(int i = 0; i < objs.size(); i++){
        tree->add(objs[i]);
    }
}

void World::addShapesToTree(){
    tree = new Octree();
}