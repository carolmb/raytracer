#ifndef __DIFFUSESHADER__
#define __DIFFUSESHADER__

#include "shader.h"

class DiffuseShader : public Shader {
public:
	Vec3 light;
	DiffuseShader(Vec3 l) : light(l) { light = light.norm(); }

	double reflect(Vec3 normal) {
		normal = normal.norm();
		return normal.dot(light);
	}

	Color getColor(Scene scene, Ray ray) {
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < scene.objs.size(); k++) {
			HitRecord tempRecord;
			if(scene.objs[k]->hit(ray, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		Color c;
		if(hitAnything) {
			c = record.m.kd*reflect(record.n);
			c.x = std::max(0.0, c.x);
			c.y = std::max(0.0, c.y);
			c.z = std::max(0.0, c.z);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}
};

#endif