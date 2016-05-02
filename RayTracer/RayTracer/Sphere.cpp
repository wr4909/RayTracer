#include "Sphere.hpp"
#include "Point3D.hpp"
#include "Maths.hpp"
#include <algorithm>

Sphere::Sphere(){
    c(0, 0, 0);
    r = 0.0;
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    material.directScale = 1.0;
    calculateBBox();
}

Sphere::Sphere(const Point3D& p, const double radius){
    c(p);
    r = radius;
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    material.directScale = 0.2;
    calculateBBox();
}

Sphere::Sphere(const Sphere& s){
    c = s.c;
    r = s.r;
    material(s.material);
    material.directScale = 1.0;
    calculateBBox();
}

Sphere::Sphere(const Point3D& p, const double radius, const Material& _material) : GeometricObject(_material, false){
    c(p);
    r = radius;
    material.directScale = 1.0;
    calculateBBox();
}

Sphere::Sphere(const Point3D& p, const double radius, const Material& _material, PNG* _texture) : GeometricObject(_material, false, _texture){
    c(p);
    r = radius;
    material.directScale = 1.0;
    calculateBBox();
}

Sphere::~Sphere(){
    
}

Sphere*
Sphere::clone(void) const{
    return (new Sphere(*this));
}

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/
Sphere& Sphere::operator= (Sphere& rhs){
    if (this == &rhs)
        return (*this);
    
    GeometricObject::operator= (rhs);
    
    c = rhs.c;
    r = rhs.r;
    material(rhs.material);
    calculateBBox();
    
    return (*this);
}
// #419end

double Sphere::hit(Ray & ray, Point3D& pt){
    double dd = ray.d.dot(ray.d);
    double ocd = 2 * (ray.o - c).dot(ray.d);
    double ocr = (ray.o - c).dot(ray.o - c) - (r*r);
    
    double abc[3] = { dd, ocd, ocr };
    double sol[2];
    int solutions = Maths::solveQuadratic(abc, sol);
    
    double t;	//time ray hits Sphere
    if (solutions == 0){
        return false;
    }
    if (solutions == 1){
        t = sol[0];
    }
    else{
        t = fmin(sol[0], sol[1]);
    }
    if (t < 0)
        return false;
    pt(ray.o + ray.d*t);
    return t;
}

RGBAPixel Sphere::castDirectionalLight(DirectionalLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    
    Point3D tempPt(pt+lightSrc.dir.reflect()*0.01);
    Ray backtraceRay(tempPt,lightSrc.dir.reflect(),"shadow");
    double tHitLight = std::numeric_limits<double>::max();
    bool shadow = false;
    
    Point3D trash(0,0,0);
    for(int i = 0; i < shapes.size(); i++){
        double tHitAnotherShape = shapes[i]->hit(backtraceRay,trash);
        if(tHitAnotherShape < tHitLight && tHitAnotherShape > 0){
            shadow = true;
            break;
        }
    }
    
    //pt's intersection with viewRay and sphere
    Vector3D normal(c, pt); //normal from center to hitPoint
    normal.normalize();
    
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    //Ambient Lighting
    r += 0.08 * 30;
    g += 0.08 * 30;
    b += 0.08 * 30;
    
    RGBAPixel temp(r*material.color.red, r*material.color.green ,r*material.color.blue);
    
    if(shadow){
        return temp;
    }
    
        
    //Diffuse Lighting
    Vector3D reflectRay = (lightSrc.dir.reflect()).hat();
    double product = reflectRay.dot(normal);
    if (product <= 0){
        temp(r,g,b);
        return temp;
    }
    r += material.color.red*product * material.kd;
    g += material.color.green*product * material.kd;
    b += material.color.blue*product * material.kd;
    
    //Specular Lighting
    double epsilon = 10.0;
    Vector3D rVec(lightSrc.dir - normal*lightSrc.dir.dot(normal)*2.0);
    double rw0e = pow(rVec.dot(viewRay.d.reflect()),epsilon);
    
    r += material.color.red*rw0e * material.ks;
    g += material.color.green*rw0e * material.ks;
    b += material.color.blue*rw0e * material.ks;
    
    
    //cap off maximum color values
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    temp(r,g,b);
    return temp;
}

void Sphere::calculateBBox(){
    box.x0 = c.x - r;
    box.x1 = c.x + r;
    box.y0 = c.y - r;
    box.y1 = c.y + r;
    box.z0 = c.z - r;
    box.z1 = c.z + r;
}

BBox& Sphere::getBBox(){
    return box;
}

Normal Sphere::getNormal(Point3D& pt){
    Normal vec(pt - c);
    return vec;
}

RGBAPixel* Sphere::mapToTexture(Point3D& pt){
    double unitX = (pt.x-c.x) / r;
    double unitY = (pt.y-c.y) / r;
    double unitZ = (pt.z-c.z) / r;
    
    double theta = acos(unitY);
    double phi = atan(unitX/unitZ);
    
    double x = phi / (2*Maths::PI);
    double y = 1-(theta/Maths::PI);
    
    double u = (x+1)/2;
    double v = (y+1)/2;
    
    RGBAPixel* pixel = mapToImage(u,v);
    return pixel;
}