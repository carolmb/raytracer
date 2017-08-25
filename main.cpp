#include <iostream>
#include "inc/img.h"
#include "inc/render.h"
#include "inc/vec3.h"

int main() {
	Scene scene;
	Color* pxls = Render::defaultRender(600, 1200, scene, 4);
	Img img(600, 1200, "test.ppm", "ppm", pxls);
	img.saveBin(); 
	std::cout << "Completed" << std::endl;
	return 0;
}