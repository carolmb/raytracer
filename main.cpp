#include <iostream>
#include "inc/img.h"
#include "inc/render.h"

int main() {
	Scene scene;
	Color* pxls = Render::defaultRender(200, 400, scene);
	Img img(200, 400, "test.ppm", "ppm", pxls);
	img.saveBin(); 
	std::cout << "Completed" << std::endl;
	return 0;
}