#ifndef Maths_hpp
#define Maths_hpp

#include <cmath>
#include <limits>
// #419begin #type=3 #src=http://www.raytracegroundup.com/downloads/
class Maths{
    
public:
    static const double PI;
    static const double PI_ON_180;
    static const double MAX_DOUBLE;
    
    static int solveQuadratic(double abc[3], double sols[2]);
    static double drand();
    static double drand(double min, double max);
    static int irand(int min, int max);
    static double min(double a, double b, double c);
    static double max(double a, double b, double c);
    static double min(double a, double b, double c, double d);
    static double max(double a, double b, double c, double d);
};
// #419end

#endif /* Maths_hpp */
