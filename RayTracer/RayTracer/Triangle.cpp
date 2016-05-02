#include "Triangle.hpp"
#include <math.h>
#include "Rectangle.hpp"

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

/*
 Function name: Triangle
 Function purpose: Default Constructor
 Parameters: none
 Return value: n/a
 output: none
 */
Triangle::Triangle(){
    v0(0, 0, 0);
    v1(1, 0, 0);
    v2(0, 1, 0);
    n(0, 0, 1);
    plane(v2, n);
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    calculateBBox();
}
// #419end

/*
 Function name: Triangle
 Function purpose: Constructor
 Parameters: a,b,c - corners of the triangle
 Return value: n/a
 output: none
 */
Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c){
    v0 = a;
    v1 = b;
    v2 = c;
    Vector3D ab(a, b);
    Vector3D ac(b, c);
    n = ab.cross(ac);
    n.normalize();
    plane(v0, n);
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    calculateBBox();
}

Triangle::Triangle(const Point3D& a, const Point3D& b, const Point3D& c, Material& _material, PNG* _texture): GeometricObject(_material, false, _texture){
    v0 = a;
    v1 = b;
    v2 = c;
    Vector3D ab(a, b);
    Vector3D ac(b, c);
    n = ab.cross(ac);
    n.normalize();
    plane(v0, n);
    calculateBBox();
}

void Triangle::operator() (Point3D& a, Point3D& b, Point3D& c){
    v0 = a;
    v1 = b;
    v2 = c;
    Vector3D ab(a, b);
    Vector3D ac(b, c);
    n = ab.cross(ac);
    n.normalize();
    plane(v0, n);
    RGBAPixel tempColor(0,255,0);
    material(tempColor, 1, 1);
    calculateBBox();
}

Triangle::Triangle(const Triangle& trig){
    v0 = trig.v0;
    v1 = trig.v1;
    v2 = trig.v2;
    n = trig.n;
    plane = trig.plane;
    material = trig.material;
    calculateBBox();
}

Triangle*
Triangle::clone(void) const{
    return (new Triangle(*this));
}

Triangle&
Triangle::operator= (const Triangle& rhs){
    if(this == &rhs)
        return (*this);
    box = rhs.box;
    material = rhs.material;
    v0 = rhs.v0;
    v1 = rhs.v1;
    v2 = rhs.v2;
    n = rhs.n;
    plane = rhs.plane;
    return (*this);
}

double Triangle::hit(Ray& ray, Point3D& pt){
    
    double d_dot_n = ray.d.dot(n);
    if (d_dot_n == 0.0) return false; //perpendicular, so not hit, so we dont care.
    
    
    //(a-o)*n
    //a is any point on the plane (in this case, triangle)
    //o is the origin of ray
    //n is normal vector
    Vector3D ao(v2.x - ray.o.x, v2.y - ray.o.y, v2.z - ray.o.z);
    double aon = ao.dot(n);
    double t = aon / d_dot_n;
    
    if (t < 0)
        return -1;
    
    Point3D p(ray.o.x + (ray.d.x*t), ray.o.y + (ray.d.y*t), ray.o.z + (ray.d.z*t));
    pt(p);
    if (PointInTriangle(p, v0, v1, v2))
        return t;
    else
        return -1;
}

/*
 test if two points are on the same side of a line
 */
bool Triangle::SameSide(Point3D& p, Point3D& c, Point3D& a, Point3D& b){
    Vector3D cp1((a - p).cross(b - p));
    cp1.normalize();
    Vector3D cp2((a - c).cross(b - c));
    cp2.normalize();
    return (cp1.dot(cp2) >= 0);
}

/*
 see if a point is in the triangle
 */
bool Triangle::PointInTriangle(Point3D& p, Point3D& a, Point3D& b, Point3D& c){
    return (SameSide(p, a, b, c) && SameSide(p, b, c, a) && SameSide(p, c, a, b));
}

RGBAPixel Triangle::castDirectionalLight(DirectionalLight& lightSrc, Point3D& vPt, Ray& viewRay, vector<GeometricObject*>& shapes){
    Point3D tempPt(vPt+lightSrc.dir.reflect()*0.01);
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
    r += 0.08 * 30;
    g += 0.08 * 30;
    b += 0.08 * 30;
    
    RGBAPixel temp(r*material.color.red,g*material.color.green,b*material.color.blue,255);
    
    if(shadow){
        return temp;
    }
    
    //Diffuse Lighting
    Vector3D reflectRay = (lightSrc.dir.reflect()).hat();
    double product = reflectRay.dot(n);
    Normal tempNormal = n;
    if (product <= 0){
        /*
        temp(r,g,b);
        return temp;*/
        tempNormal = n.reflect();
    }
    r += material.color.red*product * 0.7;
    g += material.color.green*product * 0.7;
    b += material.color.blue*product * 0.7;
    
    //Specular Lighting
    double epsilon = 10.0;
    Vector3D rVec(lightSrc.dir - tempNormal*lightSrc.dir.dot(tempNormal)*2.0);
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

RGBAPixel Triangle::rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    Vector3D dir(lightSrc.o,pt);
    dir.normalize();
    
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    //Ambient Lighting
    r += 0.1 * 30;
    g += 0.1 * 30;
    b += 0.1 * 30;
    
    //Diffuse Lighting
    Vector3D reflectRay = (dir.reflect()).hat();
    double product = reflectRay.dot(n);
    Normal tempNormal = n;
    if (product <= 0){
        tempNormal = n.reflect();
    }

    r += material.color.red*product * 0.7;
    g += material.color.green*product * 0.7;
    b += material.color.blue*product * 0.7;
    
    //Specular Lighting
    double epsilon = 10.0;
    Vector3D rVec(dir - tempNormal*dir.dot(tempNormal)*2.0);
    double rw0e = pow(rVec.dot(viewRay.d.reflect()),epsilon);
    
    r += material.color.red*rw0e * 0.5;
    g += material.color.green*rw0e * 0.5;
    b += material.color.blue*rw0e * 0.5;
    
    
    //Reflections
    double minTime = 100000.0;
    double tHitAnotherShape = 0.0;
    Vector3D recViewDir(viewRay.d - (2*viewRay.d*n)*n); //direction of mirror reflection
    recViewDir.normalize();
    
    Ray recViewRay(pt,recViewDir, "view");
    recViewRay.recurseLevel = viewRay.recurseLevel+1;
    Point3D recPt;
    RGBAPixel recColor;
    
    //Mirror Reflection
    if(material.reflectProperty == "mirror" && viewRay.recurseLevel < 3){
        
        GeometricObject* nextShape = NULL;
        
        for(int k = 0; k < shapes.size(); k++){
            if(shapes[k] == this)
                continue;
            
            tHitAnotherShape = shapes[k]->hit(recViewRay,recPt);
            if(tHitAnotherShape > 0.0 && tHitAnotherShape < minTime){
                nextShape = shapes[k];
                minTime = tHitAnotherShape;
            }
        }
        if(nextShape != NULL){
            recColor = nextShape->rayTrace(lightSrc, recPt, recViewRay, shapes);
            r += (recColor.red); //* (1-material.directScale);
            g += (recColor.green);// * (1-material.directScale);
            b += (recColor.blue);// * (1-material.directScale);
        }
    }
    if(material.reflectProperty == "glossy" && viewRay.recurseLevel < 3){
        
        double tempR = 0.0;
        double tempG = 0.0;
        double tempB = 0.0;
        
        Vector3D axisA = Vector3D(1,0,0).cross(recViewDir).hat() * 1;
        Vector3D axisB = axisA.cross(recViewDir).hat() * 1;
        
        Point3D tempPt = pt + recViewDir - 0.5*axisA - 0.5*axisB;
        Rectangle rect(tempPt, axisA, axisB);
        
        vector<Point3D> samplepts = rect.generatePoints(16);
        
        for(int i = 0; i < samplepts.size(); i++){
            Vector3D indirectDir(pt,samplepts[i]);
            Ray indirectRay(pt,indirectDir);
            indirectRay.recurseLevel = viewRay.recurseLevel + 1;
            
            GeometricObject* nextShape = NULL;
            double minTime = 100000.0;
            double tHitAnotherShape = 0.0;
            for(int k = 0; k < shapes.size(); k++){
                if(shapes[k] == this)
                    continue;
                
                tHitAnotherShape = shapes[k]->hit(indirectRay,recPt);
                if(tHitAnotherShape > 0.0 && tHitAnotherShape < minTime){
                    nextShape = shapes[k];
                    minTime = tHitAnotherShape;
                }
                if(nextShape != NULL){
                    recColor = nextShape->rayTrace(lightSrc, recPt, recViewRay, shapes);
                    tempR += (recColor.red);
                    tempG += (recColor.green);
                    tempB += (recColor.blue);
                }
            }
        }
        r += tempR / samplepts.size();
        g += tempG / samplepts.size();
        b += tempB / samplepts.size();
    }
    
    
    //cap off maximum color values
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    RGBAPixel temp(r,g,b,255);
    return temp;
}

/*
 Calculates the bounding box for this triangle and stores them as box's attributes
 */
void Triangle::calculateBBox(){
    box.x0 = Maths::min(v0.x,v1.x,v2.x);
    box.x1 = Maths::max(v0.x,v1.x,v2.x);
    box.y0 = Maths::min(v0.y,v1.y,v2.y);
    box.y1 = Maths::max(v0.y,v1.y,v2.y);
    box.z0 = Maths::min(v0.z,v1.z,v2.z);
    box.z1 = Maths::max(v0.z,v1.z,v2.z);
}

/*
 Returns the bounding box for this triangle
 */
BBox& Triangle::getBBox(){
    return box;
}

Normal Triangle::getNormal(Point3D& pt){
    return n;
}


