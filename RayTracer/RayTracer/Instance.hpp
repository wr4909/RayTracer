#ifndef Instance_hpp
#define Instance_hpp

#include "GeometricObject.hpp"
#include "Matrix.hpp"

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/
class Instance: public GeometricObject{
public:
    
    Instance(void);
    
    Instance(GeometricObject* obj_ptr);
    
    Instance(const Instance& instance);
    
    virtual Instance*
    clone(void) const;
    
    virtual
    ~Instance(void);
    
    Instance&
    operator= (const Instance& rhs);
				
    void
    set_object(GeometricObject* obj_ptr);
    
    void
    transform_texture(const bool transform);
    
    virtual void calculateBBox();
    
    virtual BBox& getBBox();
				
    virtual double hit(Ray& ray, Point3D& pt);
    
    //virtual RGBAPixel rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes);
    
    // affine tranformation functions
    
    void
    translate(const Vector3D& trans);
    
    void
    translate(const double dx, const double dy, const double dz);
    
    void
    scale(const Vector3D& s);
    
    void
    scale(const double a, const double b, const double c);
    
    virtual void
    rotate_x(const double r);
    
    virtual void
    rotate_y(const double r);
    
    virtual void
    rotate_z(const double r);
    
    void
    shear(const Matrix& m);
    
    virtual Normal
    getNormal(const Point3D& pt);
    
    GeometricObject*	object_ptr;				// object to be transformed
    Matrix				inv_matrix;		    	// inverse transformation matrix
    static 	Matrix		forward_matrix; 		// transformation matrix
    bool				transform_the_texture;	// do we transform the texture?
};

inline void
Instance::transform_texture(const bool transform) {
    transform_the_texture = transform;
}

#endif
// #419end