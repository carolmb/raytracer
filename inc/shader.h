#ifndef __SHADER__
#define __SHADER__

#include <cmath>
#include "vec3.h"
#include "ray.h"

class Shader {
public:	
	double gama = 2.2;
	virtual Color getColor(Scene scene, Ray ray) = 0;
	Color correctGama(Color c) {
		c.x = std::pow(c.x, 1/gama);
		c.y = std::pow(c.y, 1/gama);
		c.z = std::pow(c.z, 1/gama);
		return c;
	}
};

class BlinnPhongShader : public Shader {
	double halfway(Vec3 v, Vec3 n) {
		v = v.norm();
		n = n.norm();
		Vec3 h = (v + n)/((v + n).len());
		return std::pow(h.dot(n), 4);
	}

	double diff(Vec3 n, Vec3 l) {
		n = n.norm();
		return n.dot(l);
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
				record.m.ks*halfway((record.p - scene.cam.getOrigin()), record.n);
			c.x = std::max(0.0, c.x);
			c.y = std::max(0.0, c.y);
			c.z = std::max(0.0, c.z);
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
