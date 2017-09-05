#include "img.h"

#include <fstream>

void Img::save() {
	std::ofstream img ((filename + "." + type).c_str());

	img << "P3\n";
	img << cols << " " << rows << '\n';
	img << 255 << '\n';

	int r, b, g;
	int c = 0;
	int k = 0;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++, c++) {
			r = pxls[c].x * 255.99;
			g = pxls[c].y * 255.99;
			b = pxls[c].z * 255.99;
			img << r << " " << g << " " << b << " ";
		}
	}
	img.close();
}

void Img::saveBin() {
	std::ofstream img ((filename + "." + type).c_str(), std::ios::binary);

	img << "P6\n";
	img << cols << " " << rows << '\n';
	img << 255 << '\n';

	char buffer[cols*rows*3];
	int r, b, g;
	int c = 0;
	int k = 0;

	for(int i = 0; i < rows; i++) {
		for(int j = 0; j < cols; j++, c++) {
			r = pxls[c].x * 255.99;
			g = pxls[c].y * 255.99;
			b = pxls[c].z * 255.99;
			buffer[k++] = r;
			buffer[k++] = g;
			buffer[k++] = b;	
		}
	}

	img.write(buffer, cols*rows*3);
	img.close();
}
