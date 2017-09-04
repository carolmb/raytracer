#ifndef __PACKAGE__
#define __PACKAGE__

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