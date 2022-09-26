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
   

    for (int i = 0; i < width*height; i++) {
        int j = 0;
        if(i != 0 && width % i == 0){
            j++;
        }
        
        double pixelHeight = 2.0 / height;
        double pixelLength = 2.0 / width;
        //std::cout << "Working... (" << i*100.0 / width * height << "% done) " << std::endl;
        //Calculate the point on the pixel where the ray hits
        //We assume that the ray hits in the middle of the pixel
        //We begin in the verticePoint (0, 1, 1), i.e the upper left corner of the image
        dvec4 pixelPoint = dvec4(focalLength,cameraPlaneVertices[1][1].y - 2*pixelLength*i - pixelLength,cameraPlaneVertices[1][1].z - 2*pixelHeight*j - pixelHeight, 1.0);

        Ray theRay(eye, pixelPoint);
        
        //Check if the ray hit any of the surfaces
        for(int k = 0; k < _Scene.sceneTriangles.size(); k++){
            //If the ray intersects one of these triangles
            if (_Scene.sceneTriangles[k].intersection(theRay)) {
                //Set this pixels color to the triangles color
                pixels[i].setColor(_Scene.sceneTriangles[k].getColor());
                break;
            }
        }
        
    }
}
