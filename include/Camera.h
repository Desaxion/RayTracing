#pragma once
#include "Def.h"
#include "Surface.h"
#include "Pixel.h"
#include "Ray.h"
#include <iostream>
#include "Scene.h"
//#include <ofstream>

class Camera {
public:
    
    Camera() {
            cameraPlaneVertices[0][0] = dvec4(focalLength, -1.0, -1.0, 1.0);
            cameraPlaneVertices[1][0] = dvec4(focalLength, 1.0, -1.0, 1.0);
            cameraPlaneVertices[0][1] = dvec4(focalLength, -1.0, 1.0, 1.0);
            cameraPlaneVertices[1][1] = dvec4(focalLength, 1.0, 1.0, 1.0);
    };
     //render();
    void captureImage(const Scene &_Scene);
    
    void rayGun(const Scene &_Scene);

    ColorDBL Camera::shootRay(const Scene& _Scene, Ray _ray, int intersectedSurface);

    double calculateLight(dvec4 intersectionPoint, const Scene& _Scene, dvec3 _normal);

    bool inShade(dvec4 lightPoint, dvec4 shadowPoint,const Scene& _Scene);
    
    //void setColor(ColorDBL _color) { color = color; }

    bool russianRoulette();

private:

    //The camera position
    dvec4 eye = vec4(-1.0,0.0,0.0,0.0);
    double focalLength = 0.0;
    //resolution of side length in pixels
    int width = 800;
    int height = 800;
    
    dvec3 cameraPlaneVertices[2][2];
    
    Pixel* pixels = new Pixel[width*height];
   
    int NUMBER_OF_LIGHTSAMPLES = 10;
    
};

//The camera plane should be as follows:
/*
                       Z
                       ^
                       |
  (0, -1,1) o----------|----------o (0,1,1)
            |          |          |          Z
            |          |          |          ^
            |          |          |          |
   Z = 0 ___|__________|__________|__>  Y    |
            |          |          |          O-----> Y
            |          |          |
            |          |          |
            |          |          |
  (0,-1,-1) o----------|----------o (0,1,-1)
                     Y = 0
 
 This means that the side of the camera plane is 2 units long. This means that the
 pixel side length is 2 / resolution units long.
 
 
 The field of view depends on the cameraplanes position in relation to the eye point:
 
                              /
                             /|
                            / |
                           /  |
                  eye ->  O   | <- Camera plane
                           \  |
                            \ |
                             \|
                              \

                          \___/
                            |_____ Focal Length
 

 */
