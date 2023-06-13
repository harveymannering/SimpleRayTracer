//
//  Object3D.hpp
//  RayTracer
//
//  Created by Harvey Mannering on 21/08/2021.
//

#ifndef Object3D_hpp
#define Object3D_hpp

#include <stdio.h>
#include "Ray.hpp"

class Object3D {
public:
    vec3 color;
    
    // Constructor
    Object3D(vec3 rgb) : color { rgb } { }
    
    // Does the object intersect with a ray?
    virtual bool intersect(Ray ray, Ray &hit, double &t_min) = 0;
    
    // Color getters and setters
    vec3 getColor(){
        return color;
    }
    
    void setColor(vec3 rgb){
        color = rgb;
    }
};


#endif /* Object3D_hpp */
