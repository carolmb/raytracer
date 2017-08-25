#ifndef __SCENE__
#define __SCENE__

#include "camera.h"
#include "sphere.h"
#include "ray.h"
#include "vec3.h"

#include <vector>
#include <cfloat>

class Scene {
public: 
	Camera cam;
	std::vector<Object*> obj;
	Color bgColor;
	Color fgColor;

	Scene() : cam(), bgColor(Color(0.5, 0.7, 1)), fgColor(Color(1, 1, 1)) {
		Object *s1 = new Sphere(Point3(0.3, 0, -1), 0.4);
		Object *s2 = new Sphere(Point3(0, -100.5, -3), 99.f);
		Object *s3 = new Sphere(Point3(0, 1, -2), 0.6);
		Object *s4 = new Sphere(Point3(-0.4, 0, -3), 0.7);
		
		obj.push_back(s1);
		obj.push_back(s2);
		obj.push_back(s3);
		obj.push_back(s4);
	}

	Color backgroundColor(Ray r) {
		Vec3 unitDir = r.dir().norm();
		double t = 0.5*(unitDir.y + 1.0);
		return fgColor.interpole(bgColor, t);
	}

	Color getPixelColor(double u, double v) {
		Ray r = cam.getRay(u, v);
		Color c;
		
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < obj.size(); k++) {
			HitRecord tempRecord;
			if(obj[k]->hit(r, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		if(hitAnything) {
			c = record.c;
		} else {
			c = backgroundColor(r);
		}
		return c;
	}

};

#endif