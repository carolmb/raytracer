#ifndef IMG__
#define IMG__

#include <string>
#include "util/vec3.h"

// Uses an array of colors to save an image in a file
class Img {
	int rows;
	int cols;
	std::string filename;
	std::string type;
	Color* pxls;

public:
	Img(int c, int r, std::string f, std::string t, Color* p) 
		: cols(c), rows(r), filename(f), type(t), pxls(p) {}

	void save();
	void saveBin();

};

#endif
