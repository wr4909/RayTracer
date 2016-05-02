#include "TriangleMesh.hpp"


/*
 Creates triangles from obj file and inserts them into the world's shapes
 */
void TriangleMesh::loadMesh(World& world){
    string line;
    ifstream myfile ("bunny.obj");
    if(myfile.is_open()){
        while(!myfile.eof()){
            getline(myfile,line);
            vector<string> tokens;
            Tokenize(line, tokens);
            if(tokens[0].compare("v") == 0){
                double v1 = 2*(stod(tokens[1].c_str())*1000+256);
                double v2 = 2*((512-stod(tokens[2].c_str())*1000))-306;
                double v3 = 2*((stod(tokens[3].c_str())*1000));

                vertices.push_back(v1);
                vertices.push_back(v2);
                vertices.push_back(v3);
            }
            else if(tokens[0].compare("f") == 0){
                int f1 = atoi(tokens[1].c_str())-1;
                int f2 = atoi(tokens[2].c_str())-1;
                int f3 = atoi(tokens[3].c_str())-1;
                
                Point3D p1(vertices[f1*3], vertices[f1*3+1], vertices[f1*3+2]);
                Point3D p2(vertices[f2*3], vertices[f2*3+1], vertices[f2*3+2]);
                Point3D p3(vertices[f3*3], vertices[f3*3+1], vertices[f3*3+2]);
                Triangle *t1 = new Triangle(p1,p3, p2);
                world.shapes.push_back(t1);
            }
            else{continue;}
        }
        myfile.close();

    }
    else cout << "Unable to open file";
}

/*
 splits a string into an array of smaller strings separated by delimiters
 */
// #419begin #type=1 #src=http://www.sbin.org/doc/HOWTO/C++Programming-HOWTO-7.html
void TriangleMesh::Tokenize(const string& str,
              vector<string>& tokens,
              const string& delimiters)
{
    // Skip delimiters at beginning.
    string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    string::size_type pos     = str.find_first_of(delimiters, lastPos);
    
    while (string::npos != pos || string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
}
// #419end

