#ifndef __BLINNPHONGSHADER__
#define __BLINNPHONGSHADER__

#include "shader.h"

class BlinnPhongShader : public Shader {

	double halfway(Vec3 v, Vec3 l, Vec3 n, double exp) {
		v = v.norm();
		Vec3 h = (v + l).norm();
		return std::pow(std::max(h.dot(n), 0.0), exp);
	}

	double diff(Vec3 n, Vec3 l) {
		n = n.norm();
		return std::max(n.dot(l), 0.0);
	}

public:
	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		Color c;
		if(isHitting) {
			c = record.m.kd*scene.light.i*diff(record.n, scene.light.dir) + 
				record.m.ka*scene.ambient.i + 
				record.m.ks*scene.light.i*halfway(scene.cam.getOrigin() - record.p, scene.light.dir, record.n, record.m.exps);
			c.x = std::min(1.0, c.x);
			c.y = std::min(1.0, c.y);
			c.z = std::min(1.0, c.z);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}

};

#endif