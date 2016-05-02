#ifndef TriangleMesh_hpp
#define TriangleMesh_hpp

#include <iostream>
#include <fstream>
#include <string>
#include "GeometricObject.hpp"
#include "Triangle.hpp"
#include "World.hpp"

class TriangleMesh : public GeometricObject{
    
public:
    void loadMesh(World& world);
    void Tokenize(const string& str,
                  vector<string>& tokens,
                  const string& delimiters = " ");
    
private:
    vector<int> vertices;   //contains x,y,z coordinates for each triangle index in the mesh
};

#endif
