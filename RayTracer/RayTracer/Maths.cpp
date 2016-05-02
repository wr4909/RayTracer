#include <math.h>
#include "Maths.hpp"
#include <stdlib.h>

const double Maths::PI = M_PI;
const double Maths::PI_ON_180 = M_PI / 180;
const double Maths::MAX_DOUBLE = std::numeric_limits<double>::max();

/*
 Parameters: abc - inputs of quadratic equation ax^2+bx+c=0. sol - solutions of quadratic equation x0 and x1.
 */
int Maths::solveQuadratic(double abc[3], double sol[2]){
    double a = abc[0];
    double b = abc[1];
    double c = abc[2];
    
    double under_sqrt = (b*b) - (4 * a*c);
    if (under_sqrt < 0){
        return 0;
    }
    if (under_sqrt == 0){
        sol[0] = (-b / (2 * a));
        return 1;
    }
    else{
        double sol1 = (-b + sqrt(under_sqrt)) / (2 * a);
        double sol2 = (-b - sqrt(under_sqrt)) / (2 * a);
        
        sol[0] = sol1;
        sol[1] = sol2;
        return 2;
    }
}

/*
 generates a random double between [0,1)
 */
double Maths::drand(){
    double f = (double)rand() / RAND_MAX;
    return f;
}

/*
 generates a random double between [min,max)
 */
double Maths::drand(double min, double max){
    double f = (double)rand() / RAND_MAX;
    return min + f*(max - min);
}

//generates an integer between min and max, inclusive
int Maths::irand(int min, int max){
    int range = max - min + 1;
    return (rand()%range)+min;
}

double Maths::min(double a, double b, double c){
    double min = a;
    if(b < min)
        min = b;
    if(c < min)
        min = c;
    return min;
}

double Maths::max(double a, double b, double c){
    double max = a;
    if(b > max)
        max = b;
    if(c > max)
        max = c;
    return max;
}

double Maths::min(double a, double b, double c, double d){
    double min = a;
    if(b < min)
        min = b;
    if(c < min)
        min = c;
    if(d < min)
        min = d;
    return min;
}
double Maths::max(double a, double b, double c, double d){
    double max = a;
    if(b > max)
        max = b;
    if(c > max)
        max = c;
    if(d > max)
        max = d;
    return max;
}