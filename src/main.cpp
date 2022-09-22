#include <iostream>
#include "Camera.h"
#include "ColorDBL.h"

int main()	{
	Camera myCamera;
	myCamera.captureImage();
    
    std::cout << "Image captured." << std::endl;
return 0; 
}
