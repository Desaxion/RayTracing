#include "Def.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include "Scene.h"

void Camera::captureImage(const Scene& _Scene) {
	std::cout << "Capturing image... " << std::endl;



	std::ofstream img("bild.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;

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
	//Shoot rays through all of the pixels (At this moment stopping in the pixels)
	//iterate through each pixel, assign a color.
	unsigned long int pixelIndex = 0;
	for (int row = 0; row < height; row++) {
		for (int column = 0; column < width; column++) {
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
		
			shootRay(_Scene, *theRay, pixelIndex);
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

void Camera::shootRay(const Scene& _Scene, Ray _ray,unsigned long int index) {
	//Put the first intersectionpoint far away so that it is possible to find which intersectionpoint which is closer to camera.
    dvec4 intersectionPoint = dvec4(50.0,50.0,50.0,1.0);
    dvec4 newIntersectionPoint  = dvec4(50.0,50.0,50.0,1.0);


	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		//If the ray intersects one of these shapes, and the shape is closer than previous intersectionpoint
		if (_Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint)) {
            
            //Calculate vectors that go from the beginning of the ray and the other intersection point (for this pixel) to make sure that the thing that the ray intersected first is the one to be chosen.
            dvec3 newIntersectionVector = dvec3(_ray.getStart().x-newIntersectionPoint.x,_ray.getStart().y-newIntersectionPoint.y,_ray.getStart().z-newIntersectionPoint.z);
            
            dvec3 intersectionVector = dvec3(_ray.getStart().x-intersectionPoint.x,_ray.getStart().y-intersectionPoint.y,_ray.getStart().z-intersectionPoint.z);
            
            
           
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
					pixels[index].setColor(_Scene.sceneShapes[n]->getColor());
					//return _Scene.sceneShapes[n]->getColor();
				}
				else if (_Scene.sceneShapes[n]->getReflModel() == MIRROR) {
                   // _Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint);
					//bounce the ray on the surface
					//Ray newRay = _Scene.sceneShapes[n]->bounce(_ray,newIntersectionPoint);
					//Shoot the reflected ray
                    
                    _ray.bounce(_Scene.sceneShapes[n]->getNormDirection(newIntersectionPoint),newIntersectionPoint);
					
                    shootRay(_Scene, _ray.getNext(),index);
				}
			}
		}
	}

}
