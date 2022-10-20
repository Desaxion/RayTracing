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

	time_t current_time = time(NULL);
	rayGun(_Scene);
	time_t passed_time = time(NULL);

	//Render(theScene);

	time_t elapsed = passed_time - current_time;

	int mins = 0;
	int hrs = 0;

	while (elapsed > 59) {
		elapsed -= 60;
		mins++;
	}
	while (mins > 59) {
		mins -= 60;
		hrs++;
	}

	for (int y = 0; y < width * height; ++y) {
		//if (y == 320387 || y == 320388 || y == 320389) {
		//	pixels[y].setColor(ColorDBL(1.0, 1.0, 1.0));
		//}


		img << pixels[y] << std::endl;
	}
    img.close();
	std::cout << "Image captured." << std::endl;
	std::cout << "Rendering took ";
	if (hrs > 0) {
		std::cout << hrs << " hours, ";
	}
	if (mins > 0) {
		std::cout << mins << " minutes and ";
	}
	std::cout << elapsed << " seconds." << std::endl;

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
			ColorDBL tempColor(dvec3(0.0));
			ColorDBL pixelColor = (dvec3(0.0));
			double pixelHeight = 2.0 / height;
			double pixelLength = 2.0 / width;
			//std::cout << "Working... (" << i*100.0 / width * height << "% done) " << std::endl;
			//Calculate the point on the pixel where the ray hits
			//We assume that the ray hits in the middle of the pixel
			//We begin in the verticePoint (0, 1, 1), i.e the upper left corner of the image
			dvec4 pixelPoint;
			//dvec4 endPoint;

			pixelPoint = dvec4(focalLength, cameraPlaneVertices[1][1].y - pixelLength * column - pixelLength / 2.0, cameraPlaneVertices[1][1].z - pixelHeight * row - pixelHeight / 2.0, 1.0);
				//endPoint = dvec4(5 * pixelPoint.x, 5 * pixelPoint.y, 5 * pixelPoint.z, 1.0);
		
			for(int i = 0; i < RAYS_PER_PIXEL; i++){

				Ray* theRay =  new Ray(eye, pixelPoint);
				//This function will be called recursively for each ray that bounces.
				int intersectedSurface = -1;
				int numberOfBounces = 0;
				int splitted = 0;

				tempColor = shootRay(_Scene, *theRay, intersectedSurface, numberOfBounces, splitted);
				//theColor += tempColor;
				theColor = ColorDBL((theColor.getColor().r + tempColor.getColor().r), (theColor.getColor().g + tempColor.getColor().g), (theColor.getColor().b + tempColor.getColor().b));
				//Generate a new pixelPoint, which is a random point on the pixel
				pixelPoint = dvec4(focalLength, cameraPlaneVertices[1][1].y - pixelLength * column - (((double)rand()/(double)RAND_MAX)*pixelLength), cameraPlaneVertices[1][1].z - pixelHeight * row - (((double)rand() / (double)RAND_MAX)*pixelHeight), 1.0);

			}

			theColor = ColorDBL(theColor.getColor().r / RAYS_PER_PIXEL, theColor.getColor().g / RAYS_PER_PIXEL, theColor.getColor().b / RAYS_PER_PIXEL);

			pixels[pixelIndex].setColor(theColor);

			pixelIndex++;
            

			
		}
	}
}

ColorDBL Camera::shootRay(const Scene& _Scene, Ray _ray, int intersectedSurface, int numberOfBounces, int splitted) {
	//Put the first intersectionpoint far away so that it is possible to find which intersectionpoint which is closer to camera.
    dvec4 intersectionPoint = dvec4(50.0,50.0,50.0,1.0);
    dvec4 newIntersectionPoint  = dvec4(50.0,50.0,50.0,1.0);

	ColorDBL result = ColorDBL(dvec3(0.0));

	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		//If the ray intersects one of these shapes, and the shape is closer than previous intersectionpoint        
		if (_Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint)) {
			if (n == 3) {
				std::cout << "";
		   }
			
            if(intersectedSurface == n){
                continue;
            }   else{
                intersectedSurface = n;
            }
            //Calculate vectors that go from the beginning of the ray and the other intersection point (for this pixel) to make sure that the thing that the ray intersected first is the one to be chosen.
            dvec3 newIntersectionVector = dvec3(_ray.getStart().x-newIntersectionPoint.x,_ray.getStart().y-newIntersectionPoint.y,_ray.getStart().z-newIntersectionPoint.z);
            
            dvec3 intersectionVector = dvec3(_ray.getStart().x-intersectionPoint.x,_ray.getStart().y-intersectionPoint.y,_ray.getStart().z-intersectionPoint.z);

            double newIntersectionVectorLength = sqrt(newIntersectionVector.x*newIntersectionVector.x + newIntersectionVector.y*newIntersectionVector.y + newIntersectionVector.z*newIntersectionVector.z);
            
            double intersectionVectorLength = sqrt(intersectionVector.x*intersectionVector.x + intersectionVector.y*intersectionVector.y + intersectionVector.z*intersectionVector.z);

            
			if (newIntersectionVectorLength < intersectionVectorLength) {
				intersectionPoint = newIntersectionPoint;
                
				if (_Scene.sceneShapes[n]->getReflModel() == DIFFUSE) {
									double BRDF = 0.00000033;
					ColorDBL theColor(_Scene.sceneShapes[n]->getColor());
					double radiance = calculateLight(intersectionPoint, _Scene, _Scene.sceneShapes[n]->getNormDirection(intersectionPoint),BRDF,intersectedSurface); //Make this a vec3 instead, one component for each color
	
					
					theColor = theColor.getColor() * radiance;

					result = ColorDBL((theColor.getColor().r + result.getColor().r), (theColor.getColor().g + result.getColor().g), (theColor.getColor().b + result.getColor().b));

				
					if (!russianRoulette(splitted)) {
					//splitta rayen och bouncea vidare. 
						//Find how many rays the new ray shall be splitted in to
						ColorDBL splittedColor = ColorDBL(dvec3(0.0));

						int splits = rand() % 5;
						//Split the ray in a random number of smaller rays that bounce away 
						splitted++;
						for (int m = 0; m < splits; m++) {
						//Generate a random point to reflect the ray in (So that it doesn't reflect like a mirror) MAKE SURE IT Dont generate outside of scene
						double u = (double)rand() / (double)RAND_MAX * 2.0 * PI;
						double v = (double)rand() / (double)RAND_MAX * 2.0 * PI;

						double x =  sin(v) * cos(u);
						double y =  sin(v) * sin(u);
						double z =  cos(v);
						dvec3 randomDirection;
						//Check that the new direction is acutally inside the scene
						do {
						randomDirection = glm::normalize(dvec3(x - newIntersectionPoint.x, y - newIntersectionPoint.y, z - newIntersectionPoint.z));
						} while ((glm::dot(randomDirection, _Scene.sceneShapes[n]->getNormDirection())) < 0);

						_ray.bounce(randomDirection, newIntersectionPoint);
						numberOfBounces++;
						ColorDBL temp = shootRay(_Scene, _ray.getNext(), intersectedSurface, numberOfBounces, splitted);
						splittedColor = ColorDBL((splittedColor.getColor().r + temp.getColor().r/splits), (splittedColor.getColor().g + temp.getColor().g/splits), (splittedColor.getColor().b + temp.getColor().b/splits));
						}
						
						
						result = ColorDBL((splittedColor.getColor().r + result.getColor().r), (splittedColor.getColor().g + result.getColor().g), (splittedColor.getColor().b + result.getColor().b));
					}
		
				}
				else if (_Scene.sceneShapes[n]->getReflModel() == MIRROR) {
                   // _Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint);
					//bounce the ray on the surface
					//Ray newRay = _Scene.sceneShapes[n]->bounce(_ray,newIntersectionPoint);
					//Shoot the reflected ray
                    
                    _ray.bounce(_Scene.sceneShapes[n]->getNormDirection(newIntersectionPoint),newIntersectionPoint);
					
                    result = shootRay(_Scene, _ray.getNext(), intersectedSurface, numberOfBounces, splitted);
				}
                else if(_Scene.sceneShapes[n]->getReflModel() == LIGHTSOURCE){
                  result = ColorDBL(dvec3(1.0));
                }
			}
		}
	}


	result = ColorDBL(result.getColor().r/(numberOfBounces + 1),result.getColor().g/(numberOfBounces + 1), result.getColor().b/(numberOfBounces + 1));


	return result;

}

double euclideanDistance(dvec4 _p1, dvec4 _p2){
    double x = _p1.x - _p2.x;
    double y = _p1.y - _p2.y;
    double z = _p1.z - _p2.z;
    return sqrt(x*x + y*y + z*z);
}

double Camera::calculateLight(dvec4 intersectionPoint, const Scene& _Scene, dvec3 _normal, double BRDF, int intersectedSurface){
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
			//dvec4 pointOnLightsource = dvec4(8.0, 1.0, 4.8, 1.0);
			if (!inShade(pointOnLightsource, intersectionPoint, _Scene, intersectedSurface)) {
            dvec3 di(intersectionPoint.x - pointOnLightsource.x,intersectionPoint.y - pointOnLightsource.y,intersectionPoint.z - pointOnLightsource.z);
            
            double diLength = euclideanDistance(intersectionPoint, pointOnLightsource);
            
            double cosineOmegaX = (glm::dot(_normal,di))/diLength;
            double cosineOmegaY = (glm::dot(-_Scene.lightSources[n]->getNormDirection(intersectionPoint),di))/diLength;

            numerator += BRDF*(cosineOmegaX*cosineOmegaY)/(diLength*diLength);
			}
        }
        estimation += numerator;
		estimation = ((_Scene.lightSources[n]->getArea() * L_e) / NUMBER_OF_LIGHTSAMPLES*1.0) * estimation;
    }
	estimation = estimation / 1.0 * _Scene.lightSources.size();

    return estimation;
}


bool Camera::inShade(dvec4 pointOnLightsource, dvec4 pointOnSurface,const Scene& _Scene, int intersectedSurface) {
	bool res = false;
	Ray lightRay(pointOnSurface, pointOnLightsource);
	
	dvec4 newIntersectionPoint = dvec4(50.0, 50.0, 50.0, 1.0);
	dvec4 actualIntersection = dvec4(50.0, 50.0, 50.0, 1.0);


	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		if (_Scene.sceneShapes[n]->getReflModel() != LIGHTSOURCE && _Scene.sceneShapes[n]->intersection(lightRay, newIntersectionPoint)) {

			if (intersectedSurface == n) {
				continue;
			}
			else {
				intersectedSurface = n;
			}


			dvec3 newIntersectionVector = dvec3(pointOnSurface.x - newIntersectionPoint.x, pointOnSurface.y - newIntersectionPoint.y, pointOnSurface.z - newIntersectionPoint.z);

			dvec3 intersectionVector = dvec3(pointOnSurface.x - actualIntersection.x, pointOnSurface.y - actualIntersection.y, pointOnSurface.z - actualIntersection.z);

			double newIntersectionVectorLength = sqrt(newIntersectionVector.x * newIntersectionVector.x + newIntersectionVector.y * newIntersectionVector.y + newIntersectionVector.z * newIntersectionVector.z);

			double intersectionVectorLength = sqrt(intersectionVector.x * intersectionVector.x + intersectionVector.y * intersectionVector.y + intersectionVector.z * intersectionVector.z);


			if (newIntersectionVectorLength < intersectionVectorLength) {
				actualIntersection = newIntersectionPoint;
			}

		}
	}
	Ray shadowRay(pointOnSurface, actualIntersection);

	if (shadowRay.getLength() < lightRay.getLength()) {
		res = true;
	}

	return res;
}

bool Camera::russianRoulette(int splits) {
	//The more splits, the higher is the chance that this is killed
	//Now, at most 10 splits can occur
	int den = splits + 1;

	return (rand() % (10/den) == 0); //The chance
}