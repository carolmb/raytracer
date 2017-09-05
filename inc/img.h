#ifndef IMG__
#define IMG__

#include <string>
#include "vec3.h"

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
