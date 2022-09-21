#pragma once
#include "Def.h"
#include "Surface.h"
#include "Pixel.h"
#include <ofstream>

class Camera {
public:
    
     render();
    

private:

    //The camera position
    dvec3 eye;
    
    //resolution of side length in pixels
    int resolution = 800;
    
    Pixel** pixels = new Pixel*[resolution];
   
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
