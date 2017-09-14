#ifndef __DIFFUSESHADER__
#define __DIFFUSESHADER__

#include "shader.h"
/*
// using just diffuse component from blinn phong
class DiffuseShader : public Shader {
public:
	double diff(Vec3 n, Vec3 l) {
		return std::max(n.dot(l), 0.0);
	}

	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		Color c;
		if(isHitting) {
			for(int i = 0; i < scene.lights.size(); i++) {			
				Vec3 kd = record.m.kd;
				c += kd*diff(record.n, scene.lights[i].dir);
			}
			c.x = std::min(1.0, c.x); c.y = std::min(1.0, c.y); c.z = std::min(1.0, c.z);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}
};
*/
#endif
