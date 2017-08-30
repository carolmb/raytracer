#ifndef __SHADER__
#define __SHADER__

#include <cmath>
#include "vec3.h"
#include "ray.h"

class Shader {
public:	
	virtual Color getColor(Scene scene, Ray ray) = 0;
};

class DiffuseShader : public Shader {
public:
	Vec3 light;
	DiffuseShader(Vec3 l) : light(l) { light = light.norm(); }

	double reflect(Vec3 normal) {
		normal = normal.norm();
		return (light - normal*(2*light.dot(normal))).dot(normal);
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
			c = record.c*reflect(record.n) + Vec3(0.1, 0, 0); // TODO
			c.x = std::max(0.0, c.x);
			c.y = std::max(0.0, c.y);
			c.z = std::max(0.0, c.z);
		} else {
			c = scene.backgroundColor(ray);
		}
		return c;
	}
};

#endif