#include "Def.h"
#include "Camera.h"
#include <iostream>
#include <fstream>

void Camera::captureImage() {
	std::ofstream img("bild.ppm");
	img << "P3" << std::endl;
	img << width << " " << height << std::endl;
	img << "255" << std::endl;

	//Render(theScene);

		for (int y = 0; y < width*height; ++y) {
			img << pixels[y] << std::endl;
		}
	
}
