#include "Material.hpp"

Material::Material(){
    color(0,0,0);
    kd = 1;
    ks = 1;
    directScale = 1.0;
}

Material::Material(const RGBAPixel& c, double d, double s){
    color(c);
    kd = d;
    ks = s;
    directScale = 1.0;
}

Material::Material(const RGBAPixel& c, double d, double s, std::string& property){
    color(c);
    kd = d;
    ks = s;
    directScale = 1.0;
    reflectProperty = property;
}

void Material::operator()(){
    color(0,0,0);
    kd = 1;
    ks = 1;
    directScale = 1.0;
}

void Material::operator()(const RGBAPixel& c, double d, double s){
    color(c);
    kd = d;
    ks = s;
    directScale = 1.0;
}

void Material::operator()(const Material& material){
    color(material.color);
    kd = material.kd;
    ks = material.ks;
    directScale = 1.0;
}