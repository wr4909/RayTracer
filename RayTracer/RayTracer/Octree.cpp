#include "Octree.hpp"

/*
 Constructor an Ocnode. Returns reference to this node.
 */
Ocnode::Ocnode(const double x, const double y, const double z, const double length, const int h){
    this->center = new Point3D(x,y,z);
    this->length = length;
    double halfLength = length/2;
    this->maxSize = 4;
    this->height = h;
    
    this->box(x-halfLength,x+halfLength,y-halfLength,y+halfLength,z-halfLength,z+halfLength);
}

/*Creates eight children for this node and stores them inside children array
 */
void Ocnode::createChildren(){
    
    double halfLength = this->length/2;
    double quarterLength = this->length/4;
    double midX = this->center->x;
    double midY = this->center->y;
    double midZ = this->center->z;
    int h = this->height;
    
    children.push_back(new Ocnode(midX-quarterLength, midY-quarterLength, midZ+quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX+quarterLength, midY-quarterLength, midZ+quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX-quarterLength, midY+quarterLength, midZ+quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX+quarterLength, midY+quarterLength, midZ+quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX-quarterLength, midY-quarterLength, midZ-quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX+quarterLength, midY-quarterLength, midZ-quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX-quarterLength, midY+quarterLength, midZ-quarterLength, halfLength, h+1));
    children.push_back(new Ocnode(midX+quarterLength, midY+quarterLength, midZ-quarterLength, halfLength, h+1));
}

/*Recurses down the OcTree until it can find child node to insert shape into
 */
void Ocnode::add(GeometricObject* shape){
    
    if(children.size()==0){//no children
        shapes.push_back(shape);
        
        if(shapes.size() > maxSize && (height < 4)){
            createChildren();
            for(int count = 0; count < shapes.size(); count++){
                for(int i = 0; i < children.size(); i++){
                    if(children[i]->box.overlap(shapes[count]->getBBox())){
                        children[i]->add(shapes[count]);
                    }
                }
            }
            shapes.clear();
        }
    }
    else{   //has children
        for(int i = 0; i < children.size(); i++){
            if((children[i]->box).overlap(shape->getBBox())){
                children[i]->add(shape);
            }
        }
    }
}

/*inserts all shapes that are in bounding boxes hit by the viewRay
 */
void Ocnode::getGeomList(Ray& viewRay, vector<GeometricObject*>& list){
    if(!box.hitTime(viewRay))
        return;
    if(this->children.size()==0){
        for(int i = 0; i < shapes.size(); i++){
            list.push_back(shapes[i]);
        }
    }
    else{
        for(int i = 0; i < this->children.size(); i++){
            if(this->children[i]->box.hitTime(viewRay)){
                this->children[i]->getGeomList(viewRay, list);
            }
        }
    }
}

/*Default constructor for Octree. Creates one Ocnode with size 1024x1024x1024 and centered at )512,512,512)
 returns reference to this Octree.
 */
Octree::Octree(){
    this->root = new Ocnode(512,512,512,1024,0);
}

/*Adds a shape into the Octree.
 */
void Octree::add(GeometricObject* shape){
    if(root->box.overlap(shape->getBBox()))
        this->root->add(shape);
}

/*Assuming root is not null, calls recursive method for Ocnode to find shapes.
 */
void Octree::getGeomList(Ray& viewRay, vector<GeometricObject*>& array){
    if(root == NULL)
        return;
    root->getGeomList(viewRay,array);
}