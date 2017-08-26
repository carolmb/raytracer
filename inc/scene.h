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
	Color bgtl;
	Color bgtr;
	Color bgbl;
	Color bgbr;

	Scene() : cam(), 
		bgtl(Color(0.5, 0.7, 1)), 
		bgtr(Color(0.5, 0.7, 1)), 
		bgbl(Color(1, 1, 1)), 
		bgbr(Color(1, 1, 1)) {
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
		double tx = 0.5*(unitDir.x + 1.0);
		double ty = 0.5*(unitDir.y + 1.0);
		Color top = bgtl.interpole(bgtr, tx);
		Color bottom = bgbl.interpole(bgbr, tx);
		Color final = top.interpole(bottom, ty);
		return final;
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

	Color getPixelColorWithDepth(double u, double v, double maxDepth, Color fg, Color bg) {
		Ray r = cam.getRay(u, v);
		Color c;
		
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < obj.size(); k++) {
			HitRecord tempRecord;
			if(obj[k]->hit(r, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		double t = (record.p - cam.getOrigin()).len()/maxDepth;
		if(hitAnything && t < 1) {
			c = fg.interpole(bg, t);
		} else {
			c = backgroundColor(r);
		}
		return c;
	}


};

#endif