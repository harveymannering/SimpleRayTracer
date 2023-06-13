//
//  main.cpp
//  RayTracer
//
//  Created by Harvey Mannering on 21/08/2021.
//

#include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include "Sphere.hpp"
#include "Plane.hpp"

int main(int argc, const char * argv[]) {
    using namespace cv;
    
    // image dimensions
    int width = 1200;
    int height = 800;
    
    // create image matrix
    Mat image(Size(width, height), CV_8UC3);
    
    // Feild of vision
    double frustum_width = 1.5;
    double frustum_height = 1; //(height / width) * frustum_width;
    double frustum_distance = -1; // distance from camera to drawing plane
    
    // Scene
    std::vector<Object3D*> scene;
    Sphere sphere1(vec3(2,0,0), 1, vec3(200, 100, 30));
    Sphere sphere2(vec3(-1, 0, 0), 0.5, vec3(20, 180, 140));
    Sphere sphere3(vec3(5,0,0), 1, vec3(70, 190, 140));
    Sphere sphere4(vec3(-4,0,0), 1.5, vec3(20, 10, 190));
    Plane plane(vec3(-5, 4, -10), vec3(0, -1, 0), vec3(230, 170, 20));
    scene.push_back(&sphere1);
    scene.push_back(&sphere2);
    scene.push_back(&sphere3);
    scene.push_back(&sphere4);
    scene.push_back(&plane);
    
    // Point Lights
    std::vector<vec3> lights;
    lights.push_back(vec3(-5, -5, 3));
    double ambient_light  = 0.2;

    // Camera position
    vec3 origin(0, 0, 5);
    
    // Loop over every pixel
    for (int x = 0; x < width; x++){
        for (int y = 0; y < height; y++){
            double t_min = 1000000; // max render distance
            vec3 color = vec3(0,0,0);
            double x_dir = (((double) x / (double) width) * (frustum_width * 2.0)) - frustum_width;
            double y_dir = (((double) y / (double) height) * (frustum_height * 2.0)) - frustum_height;
            vec3 direction(x_dir, y_dir, frustum_distance);
            Ray r(origin, direction);
            Ray hit(vec3(0,0,0), vec3(0,0,0)); // Ray object reused to represent a hit
            
            // Calculate intersections for every object in scene
            for (Object3D* obj : scene){
                if (obj->intersect(r, hit, t_min)){
                    color = obj->getColor();
                    // Check if there is line of sight to every light in the scene
                    for (vec3 light : lights){
                        // Calculate general shading
                        Ray secondaryRay(hit.origin, light - hit.origin);
                        secondaryRay.direction.normalize();
                        double lighting = secondaryRay.direction.dot(hit.direction); // 2nd ray direction * normal
                        if (lighting < ambient_light)
                            lighting = ambient_light;
                        
                        // Check if in the shadow of another object
                        Ray secondaryHit(vec3(0,0,0), vec3(0,0,0));
                        vec3 secondaryDir = light - hit.origin;
                        double secondary_t_min = secondaryDir.length();
                        for (Object3D* obj : scene){
                            if (obj->intersect(secondaryRay, secondaryHit, secondary_t_min)){
                                lighting  = ambient_light;
                                break;
                            }
                        }
                        
                        color = color * lighting;

                    }
                }
            }
            image.at<Vec3b>(y, x) = Vec3b(color.x, color.y, color.z);
        }
    }
    
    imshow("Output", image);
    imwrite("expected_output.jpg", image);
    int k = waitKey(0); // Wait for a keystroke in the window

    return 0;
}
