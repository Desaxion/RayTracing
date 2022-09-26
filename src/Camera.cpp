#include "Def.h"
#include "Camera.h"
#include <iostream>
#include <fstream>
#include "Scene.h"

void Camera::captureImage(const Scene &_Scene) {
    std::cout << "Capturing image... " << std::endl;

	std::ofstream img("bild.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;

    rayGun(_Scene);
	//Render(theScene);

		for (int y = 0; y < width*height; ++y) {
			img << pixels[y] << std::endl;
		}
    std::cout << "Image captured." << std::endl;
}
//Pew pew
void Camera::rayGun(const Scene &_Scene) {
    //Shoot rays through all of the pixels (At this moment stopping in the pixels)
    //iterate through each pixel, assign a color.
   
    for (int row = 0; row < height; row++){
    for (int column = 0; column < width; column++) {
        int pix = row*width + column;
        
        double pixelHeight = 2.0 / height;
        double pixelLength = 2.0 / width;
        //std::cout << "Working... (" << i*100.0 / width * height << "% done) " << std::endl;
        //Calculate the point on the pixel where the ray hits
        //We assume that the ray hits in the middle of the pixel
        //We begin in the verticePoint (0, 1, 1), i.e the upper left corner of the image
        dvec4 pixelPoint = dvec4(focalLength,cameraPlaneVertices[1][1].y - pixelLength*column - pixelLength/2.0,cameraPlaneVertices[1][1].z - pixelHeight*row - pixelHeight/2.0, 1.0);
        dvec4 endPoint = dvec4(5*pixelPoint.x, 5*pixelPoint.y,5*pixelPoint.z,1.0);
        Ray theRay(eye, pixelPoint);
        //Check if the ray hit any of the surfaces
        for(int k = 0; k < _Scene.sceneTriangles.size(); k++){
            //If the ray intersects one of these triangles
            if (_Scene.sceneTriangles[k].intersection(theRay)) {
                //Set this pixels color to the triangles color
                pixels[pix].setColor(_Scene.sceneTriangles[k].getColor());
                k = _Scene.sceneTriangles.size() + 1;
            }
        }
    }
    }
}
