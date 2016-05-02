#include "Plane.hpp"
#include "limits.h"
#include <stdlib.h>

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

/*
 Function name: Plane()
 Function purpose: Default Constructor
 Parameters: none
 Return value: n/a
 output: none
 */
Plane::Plane() : GeometricObject(){
    a(0.0, 0.0, 0.0);
    n(0, 0, 1);
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
}

/*
 Function name: Plane()
 Function purpose:  Constructor
 Parameters: point - a point on the plane. normal - plane's normal vector
 Return value: n/a
 output: none
 */
Plane::Plane(const Point3D& point, const Normal& normal) : GeometricObject(), a(point), n(normal){
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    n.normalize();
}

/*
 Function name: Plane()
 Function purpose: Copy Constructor
 Parameters: plane - plane to copy attributes from
 Return value: n/a
 output: none
 */
Plane::Plane(const Plane& plane) : GeometricObject(plane), a(plane.a), n(plane.n){
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    n.normalize();
}

/*
 Function name: clone()
 Function purpose: creates a copy of current plane
 Parameters: none
 Return value: reference to a new plane, identical to current one
 output: none
 */
Plane* Plane::clone() const{
    return (new Plane(*this));
}

/*
 Function name: Plane()
 Function purpose: Destructor
 Parameters: none
 Return value: n/a
 output: none
 */
Plane::~Plane(){
}

/*
 Function name: =
 Function purpose: Assignment operator
 Parameters: rhs - Plane to copy attributes from
 Return value: current plane
 output: none
 */
Plane& Plane::operator= (const Plane& rhs){
    if (this == &rhs)
        return (*this);
    
    GeometricObject::operator= (rhs);
    
    a = rhs.a;
    n = rhs.n;
    
    return (*this);
}

/*
 Function name: ()
 Function purpose: Call operator
 Parameters: rhs - Plane to copy attributes from
 Return value: none
 output: none
 */
void Plane::operator() (Point3D p, Normal normal){
    a = p;
    n = normal;
}

/*
 Function name: hit
 Function purpose: see if the ray hits the plane
 Parameters: ray - viewing ray. pt - the point at which ray hits plane
 Return value: time at which ray hits plane
 output: pt
 */
//first see if/where the ray intersects the plane
double Plane::hit(Ray& ray, Point3D& pt){
    double d_dot_n = ray.d.dot(n);
    if (d_dot_n == 0.0) return false; // perpendicular, so not hit, so we dont care
    
    //(a-o)*n
    //a is any point on the plane
    //o is the origin of ray
    //n is normal vector
    Vector3D ao(a.x - ray.o.x, a.y - ray.o.y, a.z - ray.o.z);
    double aon = (ao.x*n.x) + (ao.y*n.y) + (ao.z*n.z);
    double t = aon / d_dot_n;
    return t;
}

// #419end

/*
 Function name: castLight
 Function purpose: calculatex pixel given lightRay and point of intersection
 Parameters: lightRay - the lighting ray. pt - intersection of viewing ray and plane
 Return value: pixel at given point with lighting
 output: none
 */
RGBAPixel Plane::castDirectionalLight(DirectionalLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    
    Point3D tempPt(pt+(lightSrc.dir.reflect()*0.01));
    Ray backtraceRay(tempPt,lightSrc.dir.reflect());
    double tHitLight = 10000;
    bool shadow = false;
    
    Point3D trash(0,0,0);
    for(int i = 0; i < shapes.size(); i++){
        double tHitAnotherShape = shapes[i]->hit(backtraceRay,trash);
        if(tHitAnotherShape < tHitLight && tHitAnotherShape > 0){
            shadow = true;
            break;
        }
    }
    
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    //Ambient Lighting
    r += 0.01 * 30;
    g += 0.01 * 30;
    b += 0.01 * 30;
    
    RGBAPixel temp(r*material.color.red,g*material.color.green,b*material.color.blue,255);\
    if(shadow){
        return temp;
    }
    
    //Diffuse Lighting
    Vector3D reflectRay = (lightSrc.dir.reflect()).hat();
    double product = reflectRay.dot(n);
    if (product <= 0){
        temp(r,g,b);
        return temp;
    }
    r += material.color.red*product * 0.7;
    g += material.color.green*product * 0.7;
    b += material.color.blue*product * 0.7;
    
    //Specular Lighting
    double epsilon = 10.0;
    Vector3D rVec(lightSrc.dir - n*lightSrc.dir.dot(n)*2.0);
    double rw0e = pow(rVec.dot(viewRay.d.reflect()),epsilon);
    
    r += material.color.red*rw0e * 0.5;
    g += material.color.green*rw0e * 0.5;
    b += material.color.blue*rw0e * 0.5;
    
    
    //cap off maximum color values
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    temp(r,g,b);
    return temp;
}


RGBAPixel Plane::rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    
    Vector3D dir(lightSrc.o,pt);
    dir.normalize();
    
    Point3D tempPt(pt+dir.reflect()*0.01);
    Ray backtraceRay(tempPt,dir.reflect(), "shadow"); //from hit point on shape to light source
    double tHitLight = 100000000;
    bool shadow = false;
    
    Point3D trash(0,0,0);
    for(int i = 0; i < shapes.size(); i++){
        double tHitAnotherShape = shapes[i]->hit(backtraceRay,trash);
        if(tHitAnotherShape < tHitLight && tHitAnotherShape > 0){
            shadow = true;
            break;
        }
    }
    
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    //Ambient Lighting
    r += 0.04 * 30;
    g += 0.04 * 30;
    b += 0.04 * 30;
    
    RGBAPixel temp(r*material.color.red, g*material.color.green ,b*material.color.blue);
    
    if(shadow){
        return temp;
    }
    
    //Diffuse Lighting
    Vector3D reflectRay = (dir.reflect()).hat();
    double product = reflectRay.dot(n);
    if (product <= 0){
        RGBAPixel temp(r,g,b,255);
        return temp;
    }
    r += material.color.red*product * 0.7;
    g += material.color.green*product * 0.7;
    b += material.color.blue*product * 0.7;
    
    //Specular Lighting
    double epsilon = 10.0;
    Vector3D rVec(dir - n*dir.dot(n)*2.0);
    double rw0e = pow(rVec.dot(viewRay.d.reflect()),epsilon);
    
    r += material.color.red*rw0e * 0.5;
    g += material.color.green*rw0e * 0.5;
    b += material.color.blue*rw0e * 0.5;
    
    
    //cap off maximum color values
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    temp(r,g,b);
    return temp;
    
}

Normal Plane::getNormal(Point3D& pt){
    return n;
}
