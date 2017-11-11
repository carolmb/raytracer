#ifndef RECSHADER__
#define RECSHADER__

#include "shaders/shader.h"
#include <limits>

class RecursiveShader : public Shader {
	int countCalls; 
		
public:
	RecursiveShader(int countCalls) : countCalls(countCalls) {}

	Color getColorRec(Scene scene, Ray ray, int count, int nRays) {
		if(count == 0) return Vec3(0, 0, 0);
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray, std::numeric_limits<float>::max());

		Color c;
		if(isHitting) {
			for(int i = 0; i < nRays; i++) {
				Ray scattered;
				Vec3 att;
				if(record.m->scatter(ray, record, att, scattered)) {
					c = c + correctGama(getColorRec(scene, scattered, count - 1, 1)*att);
				}
			}
			c = c/nRays;
		} else {
			c = correctGama(scene.backgroundColor(ray));
		}
		return c;
	}

	Color getColor(Scene scene, Ray ray) {
		return getColorRec(scene, ray, countCalls, 10);
	}
};

#endif
