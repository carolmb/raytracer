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
		return std::max(n.dot(l), 0.0);
	}

public:
	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);

		Color c;
		if(isHitting) {
			c = record.m.ka*scene.ambient.i;
			for(int i = 0; i < scene.lights.size(); i++) {
				Light light = scene.lights[i];
				Point3 newOrigin = record.p + record.n*0.01;
				Ray newRay(newOrigin, light.dir.norm());
				bool isShadow = false;
				HitRecord hr = scene.hitAnything(isShadow, newRay);
				if(isShadow) {
					return correctGama(c);
				}
				c += (record.m.kd*light.i*diff(record.n, light.dir) +
				record.m.ks*light.i*halfway(scene.cam.getOrigin() - record.p, light.dir, record.n, record.m.exps));
			}
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
