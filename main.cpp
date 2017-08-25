#include <iostream>
#include "inc/img.h"
#include "inc/render.h"

int main() {
	Scene scene;
	Color* pxls = Render::defaultRender(100, 200, scene);
	Img img(100, 200, "test.ppm", "ppm", pxls);
	img.saveBin(); 
	std::cout << "Completed" << std::endl;
	return 0;
}