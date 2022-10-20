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
//    ^ x
//    |
//    |----> z


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
	Surface cyan(ColorDBL(0.0, 1.0, 1.0));

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

    
    //Pushing shapes


	//Creating pyramid
	//position, height, width, angle
	Polygon pyramid(dvec4(8.0, 4.0, -5.0, 1.0), 4.0, 3.0, 3.3*PI/2, white);
	
	for (Triangle* k : pyramid.sides) {
		sceneShapes.push_back(k);
	}

	sceneShapes.push_back(new Sphere(dvec4(7.0, -1.0, 1.0, 1.0), 2, MIRROR));

    sceneShapes.push_back(new Triangle(aLow, aHigh, bLow, red));
	sceneShapes.push_back(new Triangle(bLow, aHigh, bHigh,red));

	//Wall between b and c
	sceneShapes.push_back(new Triangle(bLow, bHigh, cLow, green));
	sceneShapes.push_back(new Triangle(cLow, bHigh, cHigh, green));

	//Wall between c and d
	sceneShapes.push_back(new Triangle(cLow, cHigh, dLow, blue));
	sceneShapes.push_back(new Triangle(dLow, cHigh, dHigh, blue));

	//Wall between d and e
	sceneShapes.push_back(new Triangle(dLow, dHigh, eLow, magenta));
	sceneShapes.push_back(new Triangle(eLow, dHigh, eHigh,magenta));

	//Wall between e and f
	sceneShapes.push_back(new Triangle(eLow, eHigh, fLow, white));
	sceneShapes.push_back(new Triangle(fLow, eHigh, fHigh, white));

	//Wall between f and a
	sceneShapes.push_back(new Triangle(fLow, fHigh, aLow, cyan));
	sceneShapes.push_back(new Triangle(aLow, fHigh, aHigh,cyan));


	//Floor
	sceneShapes.push_back(new Triangle(aLow, bLow, fLow, yellow));
	sceneShapes.push_back(new Triangle(bLow, cLow, fLow, yellow));
	sceneShapes.push_back(new Triangle(fLow, cLow, eLow, yellow));
	sceneShapes.push_back(new Triangle(cLow, dLow, eLow, yellow));

	//Ceiling
	sceneShapes.push_back(new Triangle(bHigh, aHigh, fHigh, magenta));
	sceneShapes.push_back(new Triangle(cHigh, bHigh, fHigh, magenta));
	sceneShapes.push_back(new Triangle(cHigh, fHigh, eHigh, magenta));
	sceneShapes.push_back(new Triangle(dHigh, cHigh, eHigh, magenta));


	//for (int k = 0; k < pyramid.sides.size(); k++) {
	//	sceneShapes.push_back(pyramid.sides[k]);
	//}

	



    //Creating the lightsource
    vec4 L1Low(10.0, 2.0, 4.8, 1.0), L1High(4.0, 2.0, 4.8, 1.0);
    vec4 L2Low(10.0, -2.0, 4.8, 1.0), L2High(4.0, -2.0, 4.8, 1.0);
    /*
     Normal is supposed to point inwards, this is placed in the cieling
    L1High o------------------o L2High
          |                 /|
          |                / |
          |              /   |
          |            /     |
          |        /         |
          |    /             |
    L1Low  o------------------o L2Low
*/
    
    
    
    sceneShapes.push_back(new Triangle(L1Low, L2High, L1High,  LIGHTSOURCE));
    sceneShapes.push_back(new Triangle(L2High, L1Low, L2Low, LIGHTSOURCE));
    
    //Creating a new vector with just the lightsources, so that the information can be kept
    for(Shape* i : sceneShapes){
        if(i->getReflModel() == LIGHTSOURCE){
            lightSources.push_back(i);
        }
    }

}
