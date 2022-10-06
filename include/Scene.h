#pragma once
#include "Def.h"
#include "Triangle.h"
#include "Sphere.h"
#include <vector>
// View from above:
// ^ = camera 1 and viewing direction (origo)
// v = camera 2 and viewing direction
//           a
//          / \   <-- front
// LEFT    b   c     RIGHT
//         |   |  <-- center
//         d   e
//          \ /   <-- back
//           f
//
//    ^ z
//    |
//    |----> x
class Scene {
public:

	Scene();
    //size_t numberOfSurfaces() const { return sceneTriangles.size() }
    
    void buildScene();

   std::vector<Triangle> sceneTriangles;
    std::vector<Sphere> sceneSpheres;

    //Must use pointers since abstract classes cant be instantiated
    std::vector<Shape*> sceneShapes;
    std::vector<Shape*> lightSources;

private:
     
    
};
