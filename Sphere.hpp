//
//  Sphere.hpp
//  RayTracer
//
//  Created by Harvey Mannering on 21/08/2021.
//

#ifndef Sphere_hpp
#define Sphere_hpp

#include <stdio.h>
#include <vector>
#include <math.h>
#include <algorithm>
#include "Object3D.hpp"

// Sphere object
class Sphere : public Object3D {
private:
    vec3 cent;
    double rad;
    
    // Ray object reused for hit : origin is hit location and direction is normal
    Ray calculateHit(const Ray &ray, const double &t){
        Ray hit(vec3(0,0,0), vec3(0,0,0));
        hit.origin = ray.origin + (ray.direction * t);
        hit.direction = hit.origin - cent;
        hit.direction.normalize();
        return hit;
    }
    
public:
    Sphere(vec3 center, double radius, vec3 rgb) : cent {center}, rad {radius}, Object3D(rgb)
    { }

    // intersection involves solving a quadratic
    bool intersect(Ray ray, Ray &hit, double &t_min) override{
        // R_d * R_d
        // where R_d = direction
        double a {ray.direction.dot(ray.direction)};
        
        // 2 * R_d * (R_o * c)
        // where c = center, R_o = origin, R_d = direction
        double b {2 * ray.direction.dot(ray.origin - cent)};
        
        // (c * c) + (R_o * R_o) - (2 * c * R_o)  - r^2
        // where c = center, R_o = origin, r = radius
        double c {cent.dot(cent) + ray.origin.dot(ray.origin) - (2 * cent.dot(ray.origin)) - (rad * rad)};
        
        //Solve for t in R_o + t * R_d
        double discriminant = b * b - 4 * a * c;
        // 2 roots
        if (discriminant > 0){
            double t1 = (-b + sqrt(discriminant)) / (2 * a);
            double t2 = (-b - sqrt(discriminant)) / (2 * a);
            double smallest_t = std::min(t1, t2);
            if (smallest_t < t_min && smallest_t > 0){
                t_min = smallest_t;
                hit = calculateHit(ray, smallest_t);
                return true;
            }
        }
        // 1 root
        else if (discriminant == 0){
            double t = -b / (2 * a);
            if (t < t_min && t > 0){
                t_min = t;
                hit = calculateHit(ray, t);
                return true;
            }
        }
        
        return false;
    }
};

#endif /* Sphere_hpp */
