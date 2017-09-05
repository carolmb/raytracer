#ifndef __DNOLIGHT__
#define __DNOLIGHT__

#include "shader.h"

class DiffuseNoLightShader : public Shader {
	int countCalls; 

public:
	DiffuseNoLightShader(int countCalls) : countCalls(countCalls) {}

	Vec3 randomPoint() {
		std::knuth_b randomGenerator(3);
		Vec3 p;
		do {
			double r = std::generate_canonical<double, 6>(randomGenerator);
			double g = std::generate_canonical<double, 6>(randomGenerator);
			double b = std::generate_canonical<double, 6>(randomGenerator);
			
			p = Vec3(r, g, b)*2.0 - Vec3(1, 1, 1);
		} while(p.len2() >= 1.0);
		return p;
	}

	Color getColorRec(Scene scene, Ray ray, int count, int nRays) {
		if(count == 0) return Vec3(0, 0, 0);
		
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		Color c;
		if(isHitting) {
			for(int i = 0; i < nRays; i++) {
				Vec3 target = record.n + randomPoint();
				Ray newRay(record.p, target);
				c = c + correctGama(getColorRec(scene, newRay, count - 1, 1)*record.m.kd);
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