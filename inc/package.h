#ifndef PACKAGE__
#define PACKAGE__

#include "scene.h"
#include "render.h"

// Settings from file
struct Package {
	int cols;
	int rows;
	std::string outputfile;
	std::string type;
	Scene scene;
	Render *r;
	int samples;
	int rec;
};

#endif