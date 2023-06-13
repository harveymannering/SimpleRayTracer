//
//  vec3.hpp
//  RayTracer
//
//  Created by Harvey Mannering on 21/08/2021.
//

#ifndef vec3_hpp
#define vec3_hpp

#include <stdio.h>
#include <math.h>

// Vector class
class vec3 { // 3D
public:
    double x, y, z;
    vec3(double v1, double v2, double v3) : x {v1}, y {v2}, z {v3} { }
    
    double dot(const vec3 &v2){
        return x * v2.x + y * v2.y + z * v2.z;
    }
    
    double length(){
        return sqrt(x * x + y * y + z * z);
    }
    
    void normalize(){
        double length = sqrt(x * x + y * y + z * z);
        x /= length;
        y /= length;
        z /= length;
    }
    
    friend vec3 operator-(const vec3 &v1, const vec3 &v2){
        return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }
    
    friend vec3 operator+(const vec3 &v1, const vec3 &v2){
        return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }
    
    friend vec3 operator*(const vec3 &v1, const double &v2){
        return vec3(v1.x * v2, v1.y * v2, v1.z * v2);
    }
};

#endif /* vec3_hpp */
