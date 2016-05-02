#include "Sampler.hpp"


Sampler::Sampler(){
    double epsilon = 10.0;
    //generate sample points
    double x = -1.0;
    double y = -1.0;
    double increment = 0.5;
    
    //first, sample unit square [-1,-1] to [1,1]
    while(x <= 1){
        while(y <= 1){
            Point3D pt(x,y,0);
            samples.push_back(pt);
            y += increment;
        }
        y = -1.0;
        x += increment;
    }
    
    for(int i = 0; i < samples.size(); i++){
        double cos_phi = cos(2.0 * Maths::PI * samples[i].x);
        double sin_phi = sin(2.0 * Maths::PI * samples[i].x);
        double cos_theta = pow((1.0 - samples[i].y), 1.0 / (epsilon + 1.0));
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        double pu = sin_theta * cos_phi;
        double pv = sin_theta * sin_phi;
        double pw = cos_theta;
        hemisphereSamples.push_back(Point3D(pu,pv,pw));
    }
}

void Sampler::multijitter(vector<Point3D>& samplePts, ViewPlane& viewplane, int hindex, int vindex, int numSamples){
    int divisions = numSamples;
    
    //spans across one pixel
    Vector3D hDir = viewplane.hDir / viewplane.hres;
    Vector3D vDir = viewplane.vDir / viewplane.vres;
    
    //span across one subpixel
    Vector3D subPixelhDir = hDir / divisions;
    Vector3D subPixelvDir = vDir / divisions;
    
    Point3D pixelStartPt = viewplane.s + hDir*hindex + vDir*vindex; //start point of pixel
    
    vector<int> horiz_indices;    //0 ~ divisions
    vector<int> vert_indices;    //0 ~ divisions
    
    for(int k = 0; k < divisions; k++){
        horiz_indices.push_back(k);
        vert_indices.push_back(k);
    }
    
    for(int i = 0; i < divisions; i++){
        int cindex = Maths::irand(0,horiz_indices.size()-1);
        int rindex = Maths::irand(0,vert_indices.size()-1);
        int hindex = horiz_indices[cindex];
        int vindex = vert_indices[rindex];
        
        Point3D pt(pixelStartPt + (subPixelhDir*hindex+(0.5*subPixelhDir)) + (subPixelvDir*vindex+(0.5*subPixelvDir)));
        samplePts.push_back(pt);
        
        horiz_indices.erase(horiz_indices.begin()+cindex);
        vert_indices.erase(vert_indices.begin()+rindex);
    }
}