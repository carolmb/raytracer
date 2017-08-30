#ifndef __SCENE__
#define __SCENE__

#include "camera.h"
#include "sphere.h"
#include "ray.h"
#include "vec3.h"

#include <vector>
#include <cfloat>
#include <memory>

class Scene {
public: 
	Camera cam;
	std::vector<std::shared_ptr<Object> > objs;
	Color bgtl;
	Color bgtr;
	Color bgbl;
	Color bgbr;

	Scene() {}
	Scene(Camera cam, std::vector<std::shared_ptr<Object> > o, Color bgtl, Color bgtr, Color bgbl, Color bgbr) : 
		cam(cam), objs(o), bgtl(bgtl), bgtr(bgtr), bgbl(bgbl), bgbr(bgbr) {}

	Color backgroundColor(Ray r) {
		Vec3 unitDir = r.dir().norm();
		double tx = 0.5*(unitDir.x + 1.0);
		double ty = 0.5*(unitDir.y + 1.0);
		Color top = bgtl.interpole(bgtr, tx);
		Color bottom = bgbl.interpole(bgbr, tx);
		Color final = top.interpole(bottom, ty);
		return final;
	}

/*
	Color getPixelColor(double u, double v, int count) {
		Ray r = cam.getRay(u, v);
		Color c;
		
		double mint = DBL_MAX;
		bool hitAnything = false;
		HitRecord record;
		for(int k = 0; k < objs.size(); k++) {
			HitRecord tempRecord;
			if(objs[k]->hit(r, tempRecord, mint)) { hitAnything = true; record = tempRecord; }
		}
		if(hitAnything) {
			c = 
		} else {
			c = backgroundColor(r);
		}
		return c;
	}
*/
};

#endif