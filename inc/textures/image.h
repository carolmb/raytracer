#ifndef IMG_TEXTURE__
#define IMG_TEXTURE__

#include <cmath>
#include <memory.h>

#include "texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "util/stb_image.h"

class ImageTexture : public Texture {
	int nx, ny, n;
	std::string source;
	unsigned char *img;
public:
	ImageTexture() {}
	//ImageTexture(unsigned char* pixels, int x, int y) : img(pixels), nx(x), ny(y) {}
	ImageTexture(std::string source) : source(source) {
		FILE *f = fopen(source.c_str(), "rb");
		unsigned char *temp = stbi_load_from_file(f, &nx, &ny, &n, 3);
		img = temp;
	}
	
	virtual Vec3 value(float u, float v, Vec3 vec) {
		int i = u*nx;
		int j = (1 - v)*ny - 0.001;
		i = std::max(i, 0);
		j = std::max(j, 0);
		i = std::min(i, nx - 1);
		j = std::min(j, ny - 1);
		float r, g, b;

		r = int(img[3*i + 3*nx*j])/255.0;
		g = int(img[3*i + 3*nx*j + 1])/255.0;
		b = int(img[3*i + 3*nx*j + 2])/255.0;
		return Vec3(r, g, b);
	}

};


#endif