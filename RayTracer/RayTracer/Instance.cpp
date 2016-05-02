#include "Instance.hpp"

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/

Matrix
Instance::forward_matrix;

Instance::Instance()
:   GeometricObject(),
    object_ptr(NULL),
    inv_matrix(),
    transform_the_texture(true)
{
    forward_matrix.set_identity();
}

Instance::Instance(GeometricObject* obj_ptr)
:   GeometricObject(),
    object_ptr(obj_ptr),
    inv_matrix(),
    transform_the_texture(true)
{
    calculateBBox();
    forward_matrix.set_identity();
}

Instance::Instance (const Instance& instance)
:   GeometricObject(instance),
    inv_matrix(instance.inv_matrix),
    transform_the_texture(instance.transform_the_texture)
{
    if(instance.object_ptr)
        object_ptr = instance.object_ptr->clone();
    else  object_ptr = NULL;
}

Instance*
Instance::clone(void) const {
    return (new Instance(*this));
}

Instance::~Instance(void) {
    if (object_ptr) {
        delete object_ptr;
        object_ptr = NULL;
    }
}

Instance&
Instance::operator= (const Instance& rhs) {
    if (this == &rhs)
        return (*this);
    
    GeometricObject::operator=(rhs);
    
    if(object_ptr) {
        delete object_ptr;
        object_ptr = NULL;
    }
    
    if (rhs.object_ptr)
        object_ptr = rhs.object_ptr->clone();
    else
        object_ptr = NULL;
    
    inv_matrix				= rhs.inv_matrix;
    box                     = rhs.box;
    transform_the_texture 	= rhs.transform_the_texture;
    
    return (*this);
}

void
Instance::set_object(GeometricObject* obj_ptr) {
    object_ptr = obj_ptr;
}

void
Instance::calculateBBox() {
    
    // First get the object's untransformed BBox
    
    BBox object_bbox = object_ptr->getBBox();
    
    
    // Now apply the affine transformations to the box.
    // We must apply the transformations to all 8 vertices of the orginal box
    // and then work out the new minimum and maximum values
    
    // Construct the eight vertices as 3D points:
    
    Point3D v[8];
    
    v[0].x = object_bbox.x0; v[0].y = object_bbox.y0; v[0].z = object_bbox.z0;
    v[1].x = object_bbox.x1; v[1].y = object_bbox.y0; v[1].z = object_bbox.z0;
    v[2].x = object_bbox.x1; v[2].y = object_bbox.y1; v[2].z = object_bbox.z0;
    v[3].x = object_bbox.x0; v[3].y = object_bbox.y1; v[3].z = object_bbox.z0;
    
    v[4].x = object_bbox.x0; v[4].y = object_bbox.y0; v[4].z = object_bbox.z1;
    v[5].x = object_bbox.x1; v[5].y = object_bbox.y0; v[5].z = object_bbox.z1;
    v[6].x = object_bbox.x1; v[6].y = object_bbox.y1; v[6].z = object_bbox.z1;
    v[7].x = object_bbox.x0; v[7].y = object_bbox.y1; v[7].z = object_bbox.z1;
    
    
    // Transform these using the forward matrix
    
    v[0] = forward_matrix * v[0];
    v[1] = forward_matrix * v[1];
    v[2] = forward_matrix * v[2];
    v[3] = forward_matrix * v[3];
    v[4] = forward_matrix * v[4];
    v[5] = forward_matrix * v[5];
    v[6] = forward_matrix * v[6];
    v[7] = forward_matrix * v[7];
    
    
    // Since forward_matrix is a static variable, we must now set it to the unit matrix
    // This sets it up correctly for the next instance object
    
    forward_matrix.set_identity();
    
    
    // Compute the minimum values
    
    float x0 = 10000;
    float y0 = 10000;
    float z0 = 10000;
    
    for (int j = 0; j <= 7; j++)  {
        if (v[j].x < x0)
            x0 = v[j].x;
    }
    
    for (int j = 0; j <= 7; j++) {
        if (v[j].y < y0)
            y0 = v[j].y;
    }
    
    for (int j = 0; j <= 7; j++) {
        if (v[j].z < z0)
            z0 = v[j].z;
    }
    
    // Compute the minimum values
    
    float x1 = -10000;
    float y1 = -10000;
    float z1 = -10000;
    
    for (int j = 0; j <= 7; j++) {
        if (v[j].x > x1)
            x1 = v[j].x;
    }
    
    for (int j = 0; j <= 7; j++) {
        if (v[j].y > y1)
            y1 = v[j].y;
    }
    
    for (int j = 0; j <= 7; j++) {
        if (v[j].z > z1)
            z1 = v[j].z;
    }
    
    // Assign values to the bounding box
    
    box.x0 = x0;
    box.y0 = y0;
    box.z0 = z0;
    box.x1 = x1;
    box.y1 = y1;
    box.z1 = z1;
}

BBox&
Instance::getBBox(){
    return box;
}

double
Instance::hit(Ray& ray, Point3D& pt) {
    Ray inv_ray(ray);
    inv_ray.o = inv_matrix * inv_ray.o;
    //inv_ray.d = inv_matrix * inv_ray.d;
    
    double t = object_ptr->hit(inv_ray,pt);
    return t;
}

Normal
Instance::getNormal(const Point3D& pt){
    Normal n;// = object_ptr->getNormal(pt);   //normal of original shape
    //n.w = 0.0;
    
    Normal nPrime = forward_matrix * n;
    return n;
}

/*
RGBAPixel
Instance::rayTrace(AreaLight& lightSrc, Point3D& pt, Ray& viewRay, vector<GeometricObject*>& shapes){
    Ray inv_ray(viewRay);
    inv_ray.o = inv_matrix * inv_ray.o;
    inv_ray.d = inv_matrix * inv_ray.d;
    
    RGBAPixel pixelColor(0,0,0);
    double t = object_ptr->hit(inv_ray,pt); //pt is inverse-transformed ray intersect with original shape
    if(t <= 0)
        return pixelColor;
    Normal n = object_ptr->getNormal(pt);   //normal of original shape
    
    Normal nPrime = forward_matrix * n;

    RGBAPixel pixel(object_ptr->rayTrace(lightSrc,pt,inv_ray,shapes));
    return pixel;
}*/


void
Instance::translate(const Vector3D& trans){
    Matrix inv_translation_matrix;				// temporary inverse translation matrix
    
    inv_translation_matrix.m[0][3] = -trans.x;
    inv_translation_matrix.m[1][3] = -trans.y;
    inv_translation_matrix.m[2][3] = -trans.z;
    
    inv_matrix = inv_matrix * inv_translation_matrix;
    
    Matrix translation_matrix;					// temporary translation matrix
    
    translation_matrix.m[0][3] = trans.x;
    translation_matrix.m[1][3] = trans.y;
    translation_matrix.m[2][3] = trans.z;
    
    Instance::forward_matrix = translation_matrix * Instance::forward_matrix;
}

void
Instance::translate(const double dx, const double dy, const double dz){
    Matrix inv_translation_matrix;				// temporary inverse translation matrix
    
    inv_translation_matrix.m[0][3] = -dx;
    inv_translation_matrix.m[1][3] = -dy;
    inv_translation_matrix.m[2][3] = -dz;
    
    inv_matrix = inv_matrix * inv_translation_matrix;
    
    Matrix translation_matrix;					// temporary translation matrix
    
    translation_matrix.m[0][3] = dx;
    translation_matrix.m[1][3] = dy;
    translation_matrix.m[2][3] = dz;
    
    Instance::forward_matrix = translation_matrix * Instance::forward_matrix;
}

void
Instance::scale(const Vector3D& s){
    Matrix	inv_scaling_matrix;			// temporary inverse scaling matrix
    
    inv_scaling_matrix.m[0][0] = 1.0 / s.x;
    inv_scaling_matrix.m[1][1] = 1.0 / s.y;
    inv_scaling_matrix.m[2][2] = 1.0 / s.z;
    
    inv_matrix = inv_matrix * inv_scaling_matrix;
    
    Matrix	scaling_matrix;				// temporary scaling matrix
    
    scaling_matrix.m[0][0] = s.x;
    scaling_matrix.m[1][1] = s.y;
    scaling_matrix.m[2][2] = s.z;
    
    Instance::forward_matrix = scaling_matrix * Instance::forward_matrix;
}

void
Instance::scale(const double a, const double b, const double c){
    Matrix inv_scaling_matrix;					// temporary inverse scaling matrix
    
    inv_scaling_matrix.m[0][0] = 1.0 / a;
    inv_scaling_matrix.m[1][1] = 1.0 / b;
    inv_scaling_matrix.m[2][2] = 1.0 / c;
    
    inv_matrix = inv_matrix * inv_scaling_matrix;
    
    Matrix scaling_matrix;						// temporary scaling matrix
    
    scaling_matrix.m[0][0] = a;
    scaling_matrix.m[1][1] = b;
    scaling_matrix.m[2][2] = c;
    
    Instance::forward_matrix = scaling_matrix * Instance::forward_matrix;
}

void
Instance::rotate_x(const double theta){
    double sin_theta = sin(theta * Maths::PI_ON_180);
    double cos_theta = cos(theta * Maths::PI_ON_180);
    
    Matrix inv_x_rotation_matrix;					// temporary inverse rotation matrix about x axis
    
    inv_x_rotation_matrix.m[1][1] = cos_theta;
    inv_x_rotation_matrix.m[1][2] = sin_theta;
    inv_x_rotation_matrix.m[2][1] = -sin_theta;
    inv_x_rotation_matrix.m[2][2] = cos_theta;
    
    inv_matrix = inv_matrix * inv_x_rotation_matrix;
    
    Matrix x_rotation_matrix;						// temporary rotation matrix about x axis
    
    x_rotation_matrix.m[1][1] = cos_theta;
    x_rotation_matrix.m[1][2] = -sin_theta;
    x_rotation_matrix.m[2][1] = sin_theta;
    x_rotation_matrix.m[2][2] = cos_theta;
				
    Instance::forward_matrix = x_rotation_matrix * Instance::forward_matrix;
}

void
Instance::rotate_y(const double theta){
    double sin_theta = sin(theta * Maths::PI_ON_180);
    double cos_theta = cos(theta * Maths::PI_ON_180);
    
    Matrix inv_y_rotation_matrix;					// temporary inverse rotation matrix about y axis
    
    inv_y_rotation_matrix.m[0][0] = cos_theta;
    inv_y_rotation_matrix.m[0][2] = -sin_theta;
    inv_y_rotation_matrix.m[2][0] = sin_theta;
    inv_y_rotation_matrix.m[2][2] = cos_theta;
    
    inv_matrix = inv_matrix * inv_y_rotation_matrix;
    
    Matrix y_rotation_matrix;						// temporary rotation matrix about x axis
    
    y_rotation_matrix.m[0][0] = cos_theta;
    y_rotation_matrix.m[0][2] = sin_theta;
    y_rotation_matrix.m[2][0] = -sin_theta;
    y_rotation_matrix.m[2][2] = cos_theta;
				
    Instance::forward_matrix = y_rotation_matrix * Instance::forward_matrix;
}

void
Instance::rotate_z(const double theta){
    double sin_theta = sin(theta * Maths::PI_ON_180);
    double cos_theta = cos(theta * Maths::PI_ON_180);
    
    Matrix inv_z_rotation_matrix;					// temporary inverse rotation matrix about y axis
    
    inv_z_rotation_matrix.m[0][0] = cos_theta;
    inv_z_rotation_matrix.m[0][1] = sin_theta;
    inv_z_rotation_matrix.m[1][0] = -sin_theta;
    inv_z_rotation_matrix.m[1][1] = cos_theta;
    
    inv_matrix = inv_matrix * inv_z_rotation_matrix;
    
    Matrix z_rotation_matrix;						// temporary rotation matrix about y axis
    
    z_rotation_matrix.m[0][0] = cos_theta;
    z_rotation_matrix.m[0][1] = -sin_theta;
    z_rotation_matrix.m[1][0] = sin_theta;
    z_rotation_matrix.m[1][1] = cos_theta;
				
    Instance::forward_matrix = z_rotation_matrix * Instance::forward_matrix;
}

void
Instance::shear(const Matrix& s){
    Matrix inverse_shearing_matrix;    // inverse shear matrix
    
    // discriminant
    
    double d = 1.0 	- s.m[1][0] * s.m[0][1] - s.m[2][0] * s.m[0][2]  - s.m[2][1] * s.m[1][2]
    + s.m[1][0] * s.m[2][1] * s.m[0][2] + s.m[2][0] * s.m[0][1] * s.m[2][1];
    
    // diagonals
    
    inverse_shearing_matrix.m[0][0] = 1.0 - s.m[2][1] * s.m[1][2];
    inverse_shearing_matrix.m[1][1] = 1.0 - s.m[2][0] * s.m[0][2];
    inverse_shearing_matrix.m[2][2] = 1.0 - s.m[1][0] * s.m[0][1];
    inverse_shearing_matrix.m[3][3] = d;
    
    // first row
    
    inverse_shearing_matrix.m[0][1] = -s.m[1][0] + s.m[2][0] * s.m[1][2];
    inverse_shearing_matrix.m[0][2] = -s.m[2][0] + s.m[1][0] * s.m[2][1];
    
    // second row
    
    inverse_shearing_matrix.m[1][0] = -s.m[0][1] + s.m[2][1] * s.m[0][2];
    inverse_shearing_matrix.m[1][2] = -s.m[2][1] + s.m[2][0] * s.m[0][1];
    
    // third row
    
    inverse_shearing_matrix.m[2][0] = -s.m[0][2] + s.m[0][1] * s.m[1][2];
    inverse_shearing_matrix.m[2][1] = -s.m[1][2] + s.m[1][0] * s.m[0][2] ;
    
    // divide by discriminant
    
    inverse_shearing_matrix = inverse_shearing_matrix / d;
    
    inv_matrix = inv_matrix * inverse_shearing_matrix;
    
    Instance::forward_matrix = s * Instance::forward_matrix;
}
// #419end