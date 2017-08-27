#include <iostream>
#include "inc/img.h"
#include "inc/render.h"
#include "inc/input.h"

int main(int argc, char* argv[]) {
	if(argc > 1) {
		std::string inputFile = argv[1];
		Package* package = Input::readInput(inputFile);
		if(package != NULL) {
			std::cout << "Valid values." << std::endl;
			Color* pxls = package->r->render(package->scene, 4);
			Img img(package->cols, package->rows, package->outputfile, package->type, pxls);
			img.save();
		}
	} else {
		std::cout << "There is no input." << std::endl;
	}
	std::cout << "Main function finished." << std::endl;
	return 0;
}