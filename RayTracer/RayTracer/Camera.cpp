// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

#include "Camera.hpp"
#include "World.hpp"
#include <stdio.h>

Camera::Camera(){
    eye(0, 0, 500);
    lookat(0, 0, 0);
    ra = 0.0;
    up(0, 1, 0);
    u(1, 0, 0);
    v(1, 0, 0);
    w(0, 0, 1);
    updateViewPlane();
}

Camera::Camera(Camera& c){
    eye(c.eye);
    lookat(c.lookat);
    ra = c.ra;
    up(c.up);
    u(c.u);
    v(c.v);
    w(c.w);
    updateViewPlane();
}

Camera::~Camera(){
    
}

Camera&
Camera::operator= (Camera& rhs){
    if (this == &rhs)
        return (*this);
    
    eye = rhs.eye;
    lookat = rhs.lookat;
    ra = rhs.ra;
    up = rhs.up;
    u = rhs.u;
    v = rhs.v;
    w = rhs.w;
    
    return (*this);
}

void
Camera::compute_uvw(){
    w = eye - lookat;	//w is opposite of view plane
    w.normalize();
    u = up.cross(w).hat();
    v = w.cross(u);
    
    if (eye.x == lookat.x && eye.z == lookat.z){
        if (eye.y > lookat.y){
            u = Vector3D(0, 0, 1);
            v = Vector3D(1, 0, 0);
            w = Vector3D(0, 1, 0);
        }
        if (eye.y < lookat.y){
            u = Vector3D(1, 0, 0);
            v = Vector3D(0, 0, 1);
            w = Vector3D(0, -1, 0);
        }
    }
}
// #419end

void Camera::updateViewPlane(){
    viewPlane(Point3D(0,0,0),Vector3D(1024,0,0),Vector3D(0,1024,0),1024,1024);
}

void Camera::render_scene(World& world, PNG& image){
    double rayCount = 0;
    double totalCount = image.width()*image.height();
    GeometricObject* object = NULL;
    
    RGBAPixel pixelColor(255,255,255);
    for(int i = 0; i < image.width(); i++){
        for(int j = 0; j < image.height(); j++){
            Ray viewRay(eye,Vector3D(eye,viewPlane.getPoint(i,j)),"view"); //from eyePt to viewPlane
            
            Point3D hitPt;
            
            object = world.getFirstObjectHit(viewRay,world.shapes,hitPt);
            if(object != NULL)
                pixelColor = object->rayTrace(world.ptLight, hitPt, viewRay,world.shapes);
            
            *image(i,j) = pixelColor;
            pixelColor(255,255,255);
            object = NULL;
            rayCount ++;
            cout << rayCount / totalCount * 100 << endl;
        }
    }
    world.rayCount += (int)rayCount;
}