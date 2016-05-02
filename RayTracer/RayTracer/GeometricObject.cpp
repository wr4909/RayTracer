#include "GeometricObject.hpp"

#include "AreaLight.hpp"
#include "Sampler.hpp"

#include <iostream>

GeometricObject::GeometricObject(){
    material();
    isLightSrc = false;
    texture = NULL;
}

GeometricObject::GeometricObject(const GeometricObject& object){
    material = object.material;
    isLightSrc = false;
    box = object.box;
    texture = object.texture;
}

GeometricObject::GeometricObject(const Material& _material, bool _isLightSrc){
    material = _material;
    isLightSrc = _isLightSrc;
    texture = NULL;
}

GeometricObject::GeometricObject(const Material& _material, bool _isLightSrc, PNG* _texture){
    material = _material;
    isLightSrc = _isLightSrc;
    texture = _texture;
}

GeometricObject*
GeometricObject::clone(void) const{
    return nullptr;
}

double GeometricObject::hit(Ray& ray, Point3D& pt){ return -1; }

RGBAPixel GeometricObject::castDirectionalLight(DirectionalLight& lightSrc, Point3D& vPt, Ray& viewRay, vector<GeometricObject*>& shapes){ RGBAPixel hi(255,255,255,255); return hi; }

RGBAPixel GeometricObject::rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    
    RGBAPixel color = material.color;
    if(texture != NULL)
        color = *mapToTexture(pt);
    
    Vector3D dir(lightSrc.o,pt);
    dir.normalize();
    
    Point3D tempPt(pt+dir.reflect()*0.01);
    Ray backtraceRay(tempPt,dir.reflect(), "shadow"); //from hit point on shape to light source
    double tHitLight = lightSrc.o.distance(pt);
    bool shadow = false;
    
    Point3D trash(0,0,0);
    for(int i = 0; i < shapes.size(); i++){
        if(shapes[i]->isLightSrc)
            continue;
        double tHitAnotherShape = shapes[i]->hit(backtraceRay,trash);
        if(tHitAnotherShape < tHitLight && tHitAnotherShape > 0){
            shadow = true;
            break;
        }
    }
    
    //pt's intersection with viewRay and geometry
    Vector3D n(this->getNormal(pt));
    n.normalize();
    
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    //Ambient Lighting
    r += 0.04 * 30;
    g += 0.04 * 30;
    b += 0.04 * 30;
    
    RGBAPixel temp(r*color.red, g*color.green ,b*color.blue);
    
    if(shadow){
        return temp;
    }
    
    
    //Diffuse Lighting
    Vector3D reflectRay = (dir.reflect()).hat();
    double product = reflectRay.dot(n);
    if (product > 0){
        r += color.red*product * material.kd;
        g += color.green*product * material.kd;
        b += color.blue*product * material.kd;
    }
    
    //Specular Lighting
    
    
    double epsilon = 10.0;
    Vector3D rVec(dir - (n*dir.dot(n)*2.0));
    double spec = rVec.dot(viewRay.d.reflect());
    double rw0e;
    if(spec > 0)
        rw0e = pow(spec,epsilon);
    else
        rw0e = 0;
    if(product > 0){
        r += color.red*rw0e * material.ks * 0.5;
        g += color.green*rw0e * material.ks * 0.5;
        b += color.blue*rw0e * material.ks * 0.5;
    }
    r = r*material.directScale;
    g = g*material.directScale;
    b = b*material.directScale;
    
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
        
        vector<Point3D> samplepts = rect.generatePoints(100);
        
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
                if(nextShape != NULL && nextShape->material.transparency == 0){
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
    
    if(material.transparency > 0 && viewRay.recurseLevel == 0){
        double tempR = 255;
        double tempG = 255;
        double tempB = 255;
        
        Vector3D invNormal = n.reflect();
        Ray inverseRay(pt,invNormal);
        inverseRay.recurseLevel = viewRay.recurseLevel + 1;
        GeometricObject* nextShape = NULL;
        double minTime = 100000.0;
        double tHitAnotherShape = 0.0;
        for(int k = 0; k < shapes.size(); k++){
            if(shapes[k] == this)
                continue;
            
            tHitAnotherShape = shapes[k]->hit(inverseRay,recPt);
            if(tHitAnotherShape > 0.0 && tHitAnotherShape < minTime){
                nextShape = shapes[k];
                minTime = tHitAnotherShape;
            }
            if(nextShape != NULL && nextShape != this){
                recColor = nextShape->rayTrace(lightSrc, recPt, inverseRay, shapes);
                tempR = (recColor.red);
                tempG = (recColor.green);
                tempB = (recColor.blue);
            }
        }
        r = tempR * material.transparency + (r*(1-material.transparency));
        g = tempG * material.transparency + (g*(1-material.transparency));
        b = tempB * material.transparency + (b*(1-material.transparency));
    }
    
    //cap off maximum color values
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    temp(r,g,b);
    return temp;
}

RGBAPixel GeometricObject::rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    double r = 0.0;
    double g = 0.0;
    double b = 0.0;
    
    int dim = 6;   //6 for testing purposes. 25 for production purposes.
    int total_rays = dim*dim;
    
    vector<Point3D> lightPts = lightSrc.shape.generatePoints(total_rays);
    
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            Point3D samplePt(lightPts[i*dim+j]);
            
            Vector3D dir(pt, samplePt); //direction from shape hit point to light source
            dir.normalize();
            Point3D rayPt(pt+(dir*0.01));
            Ray backtraceRay(rayPt,dir, "shadow"); //ray from hit point on shape to light source
            
            double tHitLight = samplePt.distance(rayPt);
            
            bool hitShape = false;
            
            Point3D trash(0,0,0);
            for(int k = 0; k < shapes.size(); k++){
                if(shapes[k] == this)
                    continue;
                double tHitAnotherShape = shapes[k]->hit(backtraceRay,trash);
                if(tHitAnotherShape > 0 && tHitAnotherShape < tHitLight){
                    hitShape = true;
                    break;
                }
            }
            if(!hitShape){
                PointLight ptLt(samplePt, 1, material.kd, material.ks);
                RGBAPixel tempPixel = rayTrace(ptLt, pt, viewRay, shapes);
                r += tempPixel.red;
                g += tempPixel.green;
                b += tempPixel.blue;
            }
            
            r = r*material.directScale;
            g = g*material.directScale;
            b = b*material.directScale;
            
            //Mirror Reflection
            if(viewRay.recurseLevel < 3){
                Vector3D n(this->getNormal(pt));
                Vector3D recViewDir(viewRay.d - (2*viewRay.d*n)*n);
                recViewDir.normalize();
                Ray recViewRay(pt,recViewDir, "view");
                recViewRay.recurseLevel = viewRay.recurseLevel+1;
                Point3D recPt;
                RGBAPixel recColor;
                
                GeometricObject* nextShape = NULL;
                double minTime = 100000.0;
                double tHitAnotherShape = 0.0;
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
                    r += (recColor.red);
                    g += (recColor.green);
                    b += (recColor.blue);
                }
            }
        }
    }
    
    
    r = r / total_rays * 1.5;
    g = g / total_rays * 1.5;
    b = b / total_rays * 1.5;
    
    r =std::min((int)r,255);
    g =std::min((int)g,255);
    b =std::min((int)b,255);
    
    RGBAPixel pixel(r,g,b);
    
    
    return pixel;
}

void GeometricObject::calculateBBox(){
    
}

BBox& GeometricObject::getBBox(){
    return box;
}

Normal GeometricObject::getNormal(Point3D& pt){
    Normal n;
    return n;
}

RGBAPixel* GeometricObject::mapToTexture(Point3D& pt){
    return NULL;
}

RGBAPixel* GeometricObject::mapToImage(double u, double v){
    if(texture == NULL){
        cout << "ERROR: No texture contained.";
        return NULL;
    }
    int x = (int) (((double)(texture->width() - 1))* u);
    x = max(0,x);
    int y = (int) (((double)(texture->height() - 1))* v);
    y = max(0,y);
    return texture->operator()(x,y);
}
