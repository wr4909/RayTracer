#ifndef GeometricObject_hpp
#define GeometricObject_hpp

#include "Point3D.hpp"
#include "Normal.hpp"
#include "Vector3D.hpp"
#include "Ray.hpp"
#include <math.h>
#include <UnixImageIO/png.h>
#include "png.h"
#include "rgbapixel.h"
#include "Light.hpp"
#include "DirectionalLight.hpp"
#include "PointLight.hpp"
#include "Maths.hpp"
#include "BBox.hpp"
#include <vector>
#include "Material.hpp"
class AreaLight;
class Sampler;

using namespace std;

class GeometricObject{
    
public:
    
    Material material;
    bool isLightSrc;
    BBox box;
    PNG* texture;
    
    GeometricObject();
    
    GeometricObject(const GeometricObject& object);
    
    GeometricObject(const Material& material, bool isLightSrc, PNG* texture);
    
    GeometricObject(const Material& material, bool isLightSrc);
    
    virtual GeometricObject*
    clone(void) const;
    
    virtual double hit(Ray& ray, Point3D& pt);
    
    virtual RGBAPixel castDirectionalLight(DirectionalLight& lightSrc, Point3D& vPt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual RGBAPixel rayTrace(PointLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual RGBAPixel rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    virtual void calculateBBox();
    
    virtual BBox& getBBox();
    
    virtual Normal getNormal(Point3D& pt);
    
    virtual RGBAPixel* mapToTexture(Point3D& pt);
    
    virtual RGBAPixel* mapToImage(double u, double v);
};

#endif /* GeometricObject_hpp */
