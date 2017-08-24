#include <iostream>
#include "inc/img.h"
#include "inc/render.h"

int main() {
	Color* pxls = Render::gradient4(200, 400, 
		Color(1, 1, 1), Color(0, 0, 0), Color(0, 0, 0), Color(1, 1, 1));
	Img img(200, 400, "test.ppm", "ppm", pxls);
	img.saveBin(150); 
	std::cout << "Completed" << std::endl;
	return 0;
}