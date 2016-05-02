#include <UnixImageIO/png.h>
#include "png.h"
#include <vector>
#include "Rectangle.hpp"
#include "Sphere.hpp"
#include "Camera.hpp"
#include "Ray.hpp"
#include "Point3D.hpp"
#include "Vector3D.hpp"
#include "Maths.hpp"
#include "World.hpp"
#include "PointLight.hpp"
#include "Octree.hpp"
#include "AreaLight.hpp"
#include "Sampler.hpp"
#include "ViewPlane.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    std::clock_t start;
    double duration;
    
    start = std::clock();
    
    World world;
    world.ka = 0.08;
    int img_width = 1024;
    int img_height = 1024;
    
    PNG image(img_width, img_height);
    
    Point3D eyePt(512,512,1600);
    
    Camera camera;
    camera.set_up_vector(0, -1, 0);
    camera.set_eye(eyePt);
    
    camera.render_scene(world,image);
    image.writeToFile("./output/image1.png");
    
    eyePt(512,0,512);
    camera.set_eye(eyePt);
    camera.viewPlane(Point3D(0,1024,0),Vector3D(1024,0,0),Vector3D(0,0,1024),1024,1024);
    camera.render_scene(world,image);
    image.writeToFile("./output/image2.png");
    
    duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
    
    std::cout<<"Running Time: "<< duration <<'\n';
    std::cout<<"Rays Shot" << world.rayCount << endl;
    return 0;
}
