#include "Def.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include "Scene.h"
#include <stdlib.h>     /* srand, rand */
#include <ctime>
//#include "Functions.h"




void Camera::captureImage(const Scene& _Scene) {
	std::cout << "Capturing image... " << std::endl;



	std::ofstream img("bild.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;
	russianRoulette();
		russianRoulette();
		russianRoulette();
		russianRoulette();
		russianRoulette();
		russianRoulette();
		russianRoulette();
	
	rayGun(_Scene);
	//Render(theScene);



	for (int y = 0; y < width * height; ++y) {
		//if (y == 320387 || y == 320388 || y == 320389) {
		//	pixels[y].setColor(ColorDBL(1.0, 1.0, 1.0));
		//}


		img << pixels[y] << std::endl;
	}
    img.close();
	std::cout << "Image captured." << std::endl;
    

}
//Pew pew
void Camera::rayGun(const Scene& _Scene) {

	const int RAYS_PER_PIXEL = 1;

	//Shoot rays through all of the pixels (At this moment stopping in the pixels)
	//iterate through each pixel, assign a color.
	unsigned long int pixelIndex = 0;
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
			ColorDBL theColor(dvec3(0.0));
			ColorDBL tempColor;
			double pixelHeight = 2.0 / height;
			double pixelLength = 2.0 / width;
			//std::cout << "Working... (" << i*100.0 / width * height << "% done) " << std::endl;
			//Calculate the point on the pixel where the ray hits
			//We assume that the ray hits in the middle of the pixel
			//We begin in the verticePoint (0, 1, 1), i.e the upper left corner of the image
			dvec4 pixelPoint = dvec4(focalLength, cameraPlaneVertices[1][1].y - pixelLength * column - pixelLength / 2.0, cameraPlaneVertices[1][1].z - pixelHeight * row - pixelHeight / 2.0, 1.0);
			dvec4 endPoint = dvec4(5 * pixelPoint.x, 5 * pixelPoint.y, 5 * pixelPoint.z, 1.0);
			Ray* theRay =  new Ray(eye, pixelPoint);
			//This function will be called recursively for each ray that bounces.
            int intersectedSurface = -1;

			if (pixelIndex == 638888) { //DEBUG
				std::cout << "";
			}

			//for (int k = 0; k < RAYS_PER_PIXEL; k++) {
				tempColor = shootRay(_Scene, *theRay, intersectedSurface);
				//theColor += tempColor;
				theColor = ColorDBL((theColor.getColor().r + tempColor.getColor().r)/RAYS_PER_PIXEL, (theColor.getColor().g + tempColor.getColor().g) / RAYS_PER_PIXEL, (theColor.getColor().b + tempColor.getColor().b) / RAYS_PER_PIXEL);
			//}

			pixels[pixelIndex].setColor(theColor);
			pixelIndex++;
            
            
			//Check if the ray hit any of the surfaces
            
            
		 /*  for (int k = 0; k < _Scene.sceneTriangles.size(); k++) {
				//If the ray intersects one of these triangles

				if (_Scene.sceneTriangles[k].intersection(theRay)) {
					//Set this pixels color to the triangles color
					if (_Scene.sceneTriangles[k].getReflModel() == DIFFUSE) {
						pixels[pix].setColor(_Scene.sceneTriangles[k].getColor());
						k = _Scene.sceneTriangles.size() + 1;
					}
				}
			}

			//Check if the ray hit any of the spheres
			for (int n = 0; n < _Scene.sceneSpheres.size(); n++) {
				//If the ray intersects one of these triangles
				if (_Scene.sceneSpheres[n].intersection(theRay)) {
					//Set this pixels color to the triangles color
					if (_Scene.sceneSpheres[n].getReflModel() == DIFFUSE) {

						pixels[pix].setColor(_Scene.sceneSpheres[n].getColor());
						n = _Scene.sceneSpheres.size() + 1;
					}
					else if (_Scene.sceneSpheres[n].getReflModel() == MIRROR) {
					//Create new ray, call this function recursively
					}
				}
			}
			*/
			
		}
	}
}

ColorDBL Camera::shootRay(const Scene& _Scene, Ray _ray, int intersectedSurface) {
	//Put the first intersectionpoint far away so that it is possible to find which intersectionpoint which is closer to camera.
    dvec4 intersectionPoint = dvec4(50.0,50.0,50.0,1.0);
    dvec4 newIntersectionPoint  = dvec4(50.0,50.0,50.0,1.0);

	ColorDBL result = ColorDBL(dvec3(0.0));

	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		//If the ray intersects one of these shapes, and the shape is closer than previous intersectionpoint        
		if (_Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint)) {
           
			
            if(intersectedSurface == n){
                continue;
            }   else{
                intersectedSurface = n;
            }
            //Calculate vectors that go from the beginning of the ray and the other intersection point (for this pixel) to make sure that the thing that the ray intersected first is the one to be chosen.
            dvec3 newIntersectionVector = dvec3(_ray.getStart().x-newIntersectionPoint.x,_ray.getStart().y-newIntersectionPoint.y,_ray.getStart().z-newIntersectionPoint.z);
            
            dvec3 intersectionVector = dvec3(_ray.getStart().x-intersectionPoint.x,_ray.getStart().y-intersectionPoint.y,_ray.getStart().z-intersectionPoint.z);
            
            //test
           
			//Set this pixels color to the shapes color'
			// 
			// 
			// WORK THIS OUT NEXT
			// 
			//
            //CALCULATE THE NORM SINCE LENGTH ISNT RETURNING THE CORRECT VALUE
            //Find if glm has fucntion for the euclidean norm of a vec3
            double newIntersectionVectorLength = sqrt(newIntersectionVector.x*newIntersectionVector.x + newIntersectionVector.y*newIntersectionVector.y + newIntersectionVector.z*newIntersectionVector.z);
            
            double intersectionVectorLength = sqrt(intersectionVector.x*intersectionVector.x + intersectionVector.y*intersectionVector.y + intersectionVector.z*intersectionVector.z);
            
            //std::cout << intersectionVectorLength<<std::endl;
            //std::cout << newIntersectionVectorLength<<std::endl;
            
            
			if (newIntersectionVectorLength < intersectionVectorLength) {
				intersectionPoint = newIntersectionPoint;
                
				if (_Scene.sceneShapes[n]->getReflModel() == DIFFUSE) {
					
					ColorDBL theColor(_Scene.sceneShapes[n]->getColor());
					double radiance = calculateLight(intersectionPoint, _Scene, _Scene.sceneShapes[n]->getNormDirection(intersectionPoint)); //Make this a vec3 instead, one component for each color
					double BRDF = 0.001;
					
					theColor = theColor.getColor() * radiance * BRDF;

					result = ColorDBL((theColor.getColor().r + result.getColor().r), (theColor.getColor().g + result.getColor().g), (theColor.getColor().b + result.getColor().b));

					
					if (russianRoulette()) {
					//splitta rayen och bouncea vidare.

						//Testa bounce med mirror bounce
						_ray.bounce(_Scene.sceneShapes[n]->getNormDirection(newIntersectionPoint), newIntersectionPoint);

						ColorDBL splittedColor;

						splittedColor = shootRay(_Scene, _ray.getNext(), intersectedSurface);

						ColorDBL((splittedColor.getColor().r + result.getColor().r), (splittedColor.getColor().g + result.getColor().g), (splittedColor.getColor().b + result.getColor().b));


					}
		
				}
				else if (_Scene.sceneShapes[n]->getReflModel() == MIRROR) {
                   // _Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint);
					//bounce the ray on the surface
					//Ray newRay = _Scene.sceneShapes[n]->bounce(_ray,newIntersectionPoint);
					//Shoot the reflected ray
                    
                    _ray.bounce(_Scene.sceneShapes[n]->getNormDirection(newIntersectionPoint),newIntersectionPoint);
					
                    shootRay(_Scene, _ray.getNext(), intersectedSurface);
				}
                else if(_Scene.sceneShapes[n]->getReflModel() == LIGHTSOURCE){
                  result = ColorDBL(dvec3(1.0));
                }
			}
		}
	}
	return result;

}

double euclideanDistance(dvec4 _p1, dvec4 _p2){
    double x = _p1.x - _p2.x;
    double y = _p1.y - _p2.y;
    double z = _p1.z - _p2.z;
    return sqrt(x*x + y*y + z*z);
}

double Camera::calculateLight(dvec4 intersectionPoint, const Scene& _Scene, dvec3 _normal){
    //Sample random points on the lightsource
    const double L_e = 3200.0; //W/m2
    //Go over all lightsources
    double numerator = 0.0;
    double estimation = 0.0;
    for(int n = 0; n < _Scene.lightSources.size();n++){
        for(int i = 0; i < NUMBER_OF_LIGHTSAMPLES; i++){
        //calculate light, add in shade or not and so on
        // if !inShade :
		
            dvec4 pointOnLightsource = _Scene.lightSources[n]->getRandomPoint();
			if (!inShade(pointOnLightsource, intersectionPoint, _Scene)) {
            dvec3 di(intersectionPoint.x - pointOnLightsource.x,intersectionPoint.y - pointOnLightsource.y,intersectionPoint.z - pointOnLightsource.z);
            
            double diLength = euclideanDistance(intersectionPoint, pointOnLightsource);
            
            double cosineOmegaX = (glm::dot(_normal,di))/diLength;
            double cosineOmegaY = (glm::dot(-_Scene.lightSources[n]->getNormDirection(intersectionPoint),di))/diLength;

            numerator += (cosineOmegaX*cosineOmegaY)/(diLength*diLength);
			}
        }
        estimation += ((_Scene.lightSources[n]->getArea()*L_e)/NUMBER_OF_LIGHTSAMPLES)*numerator;
    }
    
    return estimation;
}


bool Camera::inShade(dvec4 pointOnLightsource, dvec4 pointOnSurface,const Scene& _Scene) {
	bool res = false;
	Ray lightRay(pointOnSurface, pointOnLightsource);
	
	dvec4 newIntersectionPoint = dvec4(50.0, 50.0, 50.0, 1.0);
	dvec4 actualIntersection = dvec4(50.0, 50.0, 50.0, 1.0);


	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		if (_Scene.sceneShapes[n]->getReflModel() != LIGHTSOURCE && _Scene.sceneShapes[n]->intersection(lightRay, newIntersectionPoint)) {
			actualIntersection = newIntersectionPoint;
		}
	}
	Ray shadowRay(pointOnSurface, actualIntersection);

	if (shadowRay.getLength() < lightRay.getLength()) {
		res = true;
	}

	return res;
}

bool Camera::russianRoulette() {
	srand(std::time(NULL));
	return (rand() % 1000 == 0); //The chance is now 1/6
}