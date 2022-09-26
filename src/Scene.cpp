#include "Scene.h"

Scene::Scene() {

	buildScene();

}




void Scene::buildScene() {

	// View from above:
// ^ = camera 1 and viewing direction (origo)
// v = camera 2 and viewing direction
//           a
//          / \   <-- front
// LEFT    b   f     RIGHT
//         |   |  <-- center
//         c   e
//          \ /   <-- back
//           d
//
//    ^ z
//    |
//    |----> x


	//Creating a whole bunch of vertices
	 
	vec4 aLow(13.0, 0.0, -5.0, 1.0), aHigh(13.0, 0.0, 5.0, 1.0);
	vec4 bLow(10.0, 6.0, -5.0, 1.0), bHigh(10.0, 6.0, 5.0, 1.0);
	vec4 cLow(0.0, 6.0, -5.0, 1.0), cHigh(0.0, 6.0, 5.0, 1.0);
	vec4 dLow(-3.0, 0.0, -5.0, 1.0), dHigh(-3.0, 0.0, 5.0, 1.0);
	vec4 eLow(0.0, -6.0, -5.0, 1.0), eHigh(0.0, -6.0, 5.0, 1.0);
	vec4 fLow(10.0, -6.0, -5.0, 1.0), fHigh(10.0, -6.0, 5.0, 1.0);

	//We need eight colored surfaces to assign to the triangels/walls in the scene

	Surface red(ColorDBL(1.0, 0.0, 0.0));
	Surface green(ColorDBL(0.0, 1.0, 0.0));
	Surface blue(ColorDBL(0.0, 0.0, 1.0));
	Surface black(ColorDBL(0.0, 0.0, 0.0));
	Surface white(ColorDBL(1.0, 1.0, 1.0));
	Surface gray(ColorDBL(0.5, 0.5, 0.5));
	Surface yellow(ColorDBL(1.0, 1.0, 0.0));
	Surface magenta(ColorDBL(1.0, 0.0, 1.0));

	//Create all the triangles next
	
	/*
	Begin with wall limited by a and b, see below

			bHigh o------------------o aHigh
				  |                 /|
				  |                / |
				  |              /   |
				  |            /     |
				  |        /         |
				  |    /             |
	        bLow  o------------------o aLow
	
	*/
    //Wall between a and b
    sceneTriangles.push_back(Triangle(aLow, aHigh, bLow, red));
    sceneTriangles.push_back(Triangle(bLow, aHigh, bHigh, red));

    //Wall between b and c
    sceneTriangles.push_back(Triangle(bLow, bHigh, cLow, green));
    sceneTriangles.push_back(Triangle(cLow, bHigh, cHigh, green));
    
    //Wall between c and d
    sceneTriangles.push_back(Triangle(cLow, cHigh, dLow, blue));
    sceneTriangles.push_back(Triangle(dLow, cHigh, dHigh, blue));
	
	//Wall between d and e
	sceneTriangles.push_back(Triangle(dLow, dHigh, eLow, black));
	sceneTriangles.push_back(Triangle(eLow, dHigh, eHigh, black));

	//Wall between e and f
	sceneTriangles.push_back(Triangle(eLow, eHigh, fLow, white));
	sceneTriangles.push_back(Triangle(fLow, eHigh, fHigh, white));

	//Wall between f and a
	sceneTriangles.push_back(Triangle(fLow, fHigh, aLow, gray));
	sceneTriangles.push_back(Triangle(aLow, fHigh, aHigh, gray));


	//Floor
	sceneTriangles.push_back(Triangle(aLow, bLow, fLow, yellow));
	sceneTriangles.push_back(Triangle(bLow, cLow, fLow, yellow));
	sceneTriangles.push_back(Triangle(fLow, cLow, eLow, yellow));
	sceneTriangles.push_back(Triangle(cLow, dLow, eLow, yellow));

	//Ceiling
	sceneTriangles.push_back(Triangle(bHigh, aHigh, fHigh, magenta));
	sceneTriangles.push_back(Triangle(cHigh, bHigh, fHigh, magenta));
	sceneTriangles.push_back(Triangle(cHigh, fHigh, eHigh, magenta));
	sceneTriangles.push_back(Triangle(dHigh, cHigh, eHigh, magenta));
    
    

    
}														
