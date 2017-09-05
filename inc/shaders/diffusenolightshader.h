#ifndef __DNOLIGHT__
#define __DNOLIGHT__

#include "shader.h"

class DiffuseNoLightShader : public Shader {
	int countCalls; 

public:
	DiffuseNoLightShader(int countCalls) : countCalls(countCalls) {}

	Vec3 randomPoint() {
		Vec3 p;
		do {
			p = Vec3(drand48(), drand48(), drand48())*2.0 - Vec3(1, 1, 1);
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