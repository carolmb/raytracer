#include "render.h"

#include <stdlib.h>
#include <random>
#include <iostream>
#include <ctime>

Color* Render::render(Scene scene) {
	std::knuth_b randomGenerator(3);
	Color* pxls = new Color[rows*cols];

	std::clock_t begin = std::clock();

	for(int i = rows - 1; i >= 0; i--) {
		for(int j = 0; j < cols; j++) {
			Color c;
			for(int k = 0; k < samples; k++) {
				double deltaU = std::generate_canonical<double, 6>(randomGenerator);
				double deltaV = std::generate_canonical<double, 6>(randomGenerator);
				double v = 1 - ((double)i + deltaV)/(double)rows;
				double u = ((double)j + deltaU)/(double)cols;

				c = c + shader->getColor(scene, scene.cam->getRay(u, v));
			}

			std::cout << 100 - (i*cols + j)*100/(cols*rows) << " %\r ";
			
			pxls[i*cols + j] = c/(double)samples;
		}
	}
	std::clock_t end = std::clock();
  	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
  	std::cout << "Total time: " << elapsed_secs << " seconds" << std::endl;
	return pxls;		

return NULL;}