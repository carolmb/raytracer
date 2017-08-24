#ifndef __IMG__
#define __IMG__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "vec3.h"

class Img {
	int rows;
	int cols;
	std::string filename;
	std::string type;
	Color* pxls;

public:
	Img(int r, int c, std::string f, std::string t, Color* p) 
		: rows(r), cols(c), filename(f), type(t), pxls(p) {}

	void saveBin(int maxColor) {
		std::ofstream img (filename.c_str(), std::ios::binary);
	
		img << "P6\n";
		img << cols << " " << rows << '\n';
		img << maxColor << '\n';

		char buffer[cols*rows*3];
		int r, b, g;
		int c = 0;
		int k;

		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++, c++) {
				r = pxls[c].x * 255;
				g = pxls[c].y * 255;
				b = pxls[c].z * 255;
				k = 3 * (i * cols + j);
				buffer[k] = r;
				buffer[k + 1] = g;
				buffer[k + 2] = b;	
			}
		}

		img.write(buffer, cols*rows*3);
		img.close();
	}

};

#endif
