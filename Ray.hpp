//
//  Ray.hpp
//  RayTracer
//
//  Created by Harvey Mannering on 21/08/2021.
//

#ifndef Ray_hpp
#define Ray_hpp

#include <stdio.h>
#include "vec3.hpp"

// Geometric object
struct Ray {
public:
    vec3 origin;
    vec3 direction;
    Ray (vec3 o, vec3 d) : origin {o}, direction {d} { }
};

#endif /* Ray_hpp */
