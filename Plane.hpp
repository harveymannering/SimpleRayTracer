//
//  Plane.hpp
//  RayTracer
//
//  Created by Harvey Mannering on 22/08/2021.
//

#ifndef Plane_hpp
#define Plane_hpp

#include <stdio.h>
#include "Object3D.hpp"

class Plane : public Object3D
{
private:
    // Infinite plane is defined by point on the plane and the normal to the plane
    vec3 center;
    vec3 normal;
public:
    // Constructor
    Plane (vec3 cent, vec3 norm, vec3 rgb) : center {cent}, normal {norm}, Object3D(rgb)
    { }
    
    bool intersect(Ray ray, Ray &hit, double &t_min) override {
        // Equation for the intersection of a ray with a plane:
        //  ((c - R_o) * n) / (R_d * n)
        // where c = center, n = normal, R_o = ray origin and R_d = ray direction
        double denominator = ray.direction.dot(normal);
        if (denominator != 0){
            double t = (center - ray.origin).dot(normal) / denominator;
            if (t < t_min && t > 0)
            {
                t_min = t;
                // Ray object reused for hit : origin is hit location and direction is normal
                hit.origin = ray.origin + (ray.direction * t);
                hit.direction = normal;
                hit.direction.normalize();
                return true;
            }
        }
        return false;
    }
};

#endif /* Plane_hpp */
