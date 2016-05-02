#ifndef Matrix_hpp
#define Matrix_hpp

// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/ray-traced-images.zip

class Matrix{
    
public:
    
    double m[4][4];     //vertical, then horizontal
    
    Matrix();
    
    Matrix& 										// assignment operator
    operator= (const Matrix& rhs);
    
    Matrix 											// multiplication of two matrices
    operator* (const Matrix& mat) const;
    
    Matrix 											// divsion by a double
    operator/ (const double d);
    
    void											// set to the identity matrix
    set_identity(void);
    /*
    double
    det() const;*/
};

#endif

// #419end