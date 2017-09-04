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
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < scene.objs.size(); k++) {
			HitRecord tempRecord;
			if(scene.objs[k]->hit(ray, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		Color c;
		if(hitAnything) {
			c = record.m.kd*diff(record.n, scene.light) + 
				record.m.ka + 
				record.m.ks*halfway(scene.cam.getOrigin() - record.p, scene.light, record.n, record.m.exps);
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