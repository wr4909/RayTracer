#include "Rectangle.hpp"
#include "AreaLight.hpp"

Rectangle::Rectangle(){
    
}

Rectangle::Rectangle(const Point3D p, const Vector3D v1, const Vector3D v2) : t1(p,p+v1,p+v2), t2(p+v1+v2,p+v2,p+v1){
    isLightSrc = false;
}

void Rectangle::operator()(Rectangle& rhs){
    t1.v0 = rhs.t1.v0;
    t1.v1 = rhs.t1.v1;
    t1.v2 = rhs.t1.v2;
    
    t2.v0 = rhs.t2.v0;
    t2.v1 = rhs.t2.v1;
    t2.v2 = rhs.t2.v2;
}

Rectangle*
Rectangle::clone(void) const{
    return (new Rectangle(*this));
}

Rectangle& Rectangle::operator= (const Rectangle& rhs){
    if(this == &rhs)
        return (*this);
    
    isLightSrc = rhs.isLightSrc;
    t1 = rhs.t1;
    t2 = rhs.t2;
    trigNumber = rhs.trigNumber;
    material = rhs.material;
    return (*this);
}

void Rectangle::calculateBBox(){
    box.x0 = Maths::min(std::min(t1.v0.x,t2.v0.x), std::min(t1.v1.x,t2.v1.x), std::min(t1.v2.x,t2.v2.x));
    box.x1 = Maths::max(std::max(t1.v0.x,t2.v0.x), std::max(t1.v1.x,t2.v1.x), std::max(t1.v2.x,t2.v2.x));
    box.y0 = Maths::min(std::min(t1.v0.y,t2.v0.y), std::min(t1.v1.y,t2.v1.y), std::min(t1.v2.y,t2.v2.y));
    box.y1 = Maths::max(std::max(t1.v0.y,t2.v0.y), std::max(t1.v1.y,t2.v1.y), std::max(t1.v2.y,t2.v2.y));
    box.z0 = Maths::min(std::min(t1.v0.z,t2.v0.z), std::min(t1.v1.z,t2.v1.z), std::min(t1.v2.z,t2.v2.z));
    box.z1 = Maths::max(std::max(t1.v0.z,t2.v0.z), std::max(t1.v1.z,t2.v1.z), std::max(t1.v2.z,t2.v2.z));
}

BBox& Rectangle::getBBox(){
    return box;
}

double Rectangle::hit(Ray& ray, Point3D& pt){
    trigNumber = 1;
    double time = t1.hit(ray,pt);
    if(time <= 0){
        time = t2.hit(ray,pt);
        trigNumber = 2;
    }
    return time;
}

RGBAPixel Rectangle::rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    if(isLightSrc){
        RGBAPixel pixel(255,255,255);
        return pixel;
    }
    if(trigNumber == 1){   //hits t1
        return t1.rayTrace(lightSrc, pt, viewRay, shapes);
    }
    else{
        return t2.rayTrace(lightSrc, pt, viewRay, shapes);
    }
}

RGBAPixel Rectangle::rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& ray, vector<GeometricObject*>& shapes){
    RGBAPixel pixel(255,255,255);
    if(isLightSrc)
        return pixel;
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    int dim = 20;
    int total_rays = dim*dim;
    
    vector<Point3D> lightPts = lightSrc.shape.generatePoints(total_rays);
    
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            Point3D samplePt(lightPts[i*dim+j]);
            
            Vector3D dir(pt, samplePt); //direction from shape hit point to light source
            dir.normalize();
            Point3D rayPt(pt+(dir*0.01));
            Ray backtraceRay(rayPt,dir); //ray from hit point on shape to light source
            
            double tHitLight = samplePt.distance(rayPt);
            
            bool hitShape = false;
            
            Point3D trash(0,0,0);
            for(int k = 0; k < shapes.size(); k++){
                double tHitAnotherShape = shapes[k]->hit(backtraceRay,trash);
                if(tHitAnotherShape > 0 && tHitAnotherShape < tHitLight){
                    hitShape = true;
                    break;
                }
            }
            if(!hitShape){
                PointLight ptLt(samplePt, 1, material.kd, material.ks);
                RGBAPixel tempPixel = rayTrace(ptLt, pt, ray, shapes);
                r += tempPixel.red;
                g += tempPixel.green;
                b += tempPixel.blue;
            }
        }
    }
    
    
    r = r / total_rays;
    g = g / total_rays;
    b = b / total_rays;
    
    pixel(r,g,b);
    
    
    return pixel;
}


//samples is sqrt(total number of sample points)
vector<Point3D> Rectangle::generatePoints(int samples){
    vector<Point3D> array;
    
    int sideLength = sqrt(samples);
    
    Vector3D dir01(t1.v0, t1.v1);
    dir01 = dir01 / sideLength;
    Vector3D dir03(t2.v2, t2.v1);
    dir03 = dir03 / sideLength;
    
    for(int i = 0; i < sideLength; i++){
        for(int j = 0; j < sideLength; j++){
            Point3D pt(t1.v0 + i*dir01 + j*dir03);
            array.push_back(pt);
        }
    }
    return array;
}

Normal
Rectangle::getNormal(Point3D& pt){
    return t1.n;
}




