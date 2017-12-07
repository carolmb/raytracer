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

				std::string idMat = record.m;
				std::shared_ptr<Material> mat = std::dynamic_pointer_cast<Material>(scene.mats[idMat]);

				Vec3 emitted = mat->emitted(record.u, record.v, record.p);	
				if(mat->scatter(ray, record, att, scattered)) {
					c = c + emitted + correctGama(getColorRec(scene, scattered, count - 1, 1)*att);
				} else {
					c = c + emitted;
				}
			}
			c = c/nRays;
		} else {
			c = scene.backgroundColor(ray);
		}
		return c;
	}

	Color getColor(Scene scene, Ray ray) {
		return getColorRec(scene, ray, countCalls, 10);
	}
};

#endif
