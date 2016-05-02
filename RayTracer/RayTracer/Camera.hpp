#ifndef Camera_hpp
#define Camera_hpp

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

#include "png.h"
#include "ViewPlane.hpp"
#include "Ray.hpp"
#include <vector>

class World;

class Camera{
    
public:
    
    Camera();
    
    Camera(Camera& c);
    
    ~Camera();
    
    void set_eye(Point3D& p);
    
    void set_eye(float x, float y, float z);
    
    void set_lookat(const Point3D& p);
    
    void set_lookat(float x, float y, float z);
    
    void set_up_vector(Vector3D& v);
    
    void set_up_vector(float x, float y, float z);
    
    void set_roll(float ra);
    
    void compute_uvw();
    
    void render_scene(World& world, PNG& img);
    
    void updateViewPlane();
    
    Point3D eye;			//eye point
    Point3D lookat;			//lookat point
    float ra;				//roll angle
    Vector3D u, v, w;		//orthonormal basis vectors
    Vector3D up;			//up vector
    ViewPlane viewPlane;
    
    Camera& operator=(Camera& camera);
};

inline void
Camera::set_eye(Point3D& p){
    eye = p;
}

inline void
Camera::set_eye(float x, float y, float z){
    eye.x = x; eye.y = y; eye.z = z;
}

inline void
Camera::set_lookat(const Point3D& p){
    lookat = p;
}

inline void
Camera::set_lookat(float x, float y, float z){
    lookat(x, y, z);
}

inline void
Camera::set_up_vector(Vector3D& v){
    up = v;
}

inline void
Camera::set_up_vector(float x, float y, float z){
    up.x = x; up.y = y; up.z = z;
}

inline void 
Camera::set_roll(float r){
    ra = r;
}

#endif

// #419end