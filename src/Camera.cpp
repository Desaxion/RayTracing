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
		img << pixels[y] << std::endl;
	}
	std::cout << "Image captured." << std::endl;
}
//Pew pew
void Camera::rayGun(const Scene& _Scene) {
	//Shoot rays through all of the pixels (At this moment stopping in the pixels)
	//iterate through each pixel, assign a color.
	int pixelIndex = 0;
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
			Ray theRay(eye, pixelPoint);
			//This function will be called recursively for each ray that bounces.
			shootRay(_Scene, theRay, pixelIndex);
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

void Camera::shootRay(const Scene& _Scene, Ray &_ray, int index) {
	//Put the first intersectionpoint far away so that it is possible to find which intersectionpoint which is closer to camera.
	dvec4 intersectionPoint;
	dvec4 newIntersectionPoint;


	for (int n = 0; n < _Scene.sceneShapes.size(); n++) {
		//If the ray intersects one of these shapes, and the shape is closer than previous intersectionpoint
		if (_Scene.sceneShapes[n]->intersection(_ray, newIntersectionPoint)) {
			//Set this pixels color to the shapes color'
			// 
			// 
			// WORK THIS OUT NEXT
			// 
			// 
			//if ((_rayStart - newIntersectionPoint).length > (_rayStart - intersectionPoint).length) {
			//	intersectionPoint = newIntersectionPoint;
			//if (index == 550000) {std::cout << "Nu är vi framme vid debug" << std::endl;
			//}

				if (_Scene.sceneShapes[n]->getReflModel() == DIFFUSE) {
					pixels[index].setColor(_Scene.sceneShapes[n]->getColor());
					//return _Scene.sceneShapes[n]->getColor();
				}
				else if (_Scene.sceneShapes[n]->getReflModel() == MIRROR) {
					//bounce the ray on the surface
					Ray* newRay = _Scene.sceneShapes[n]->bounce(_ray,newIntersectionPoint);
					//Shoot the reflected ray
					shootRay(_Scene, *newRay,index);
				}
			//}
		}
	}

}