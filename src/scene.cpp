#include "scene.h"

#include <cfloat>

Color Scene::backgroundColor(Ray r) {
	Vec3 unitDir = r.dir().norm();
	double tx = 0.5*(unitDir.x + 1.0);
	double ty = 0.5*(unitDir.y + 1.0);
	Color top = bgtl.interpole(bgtr, tx);
	Color bottom = bgbl.interpole(bgbr, tx);
	Color final = bottom.interpole(top, ty);
	return final;
}

HitRecord Scene::hitAnything(bool &isHitting, Ray ray, double maxt) {
	double mint = DBL_MAX;
	HitRecord record;
	for(int k = 0; k < objs.size(); k++) {
		HitRecord tempRecord;
		if(objs[k]->hit(ray, tempRecord, mint, maxt)) { 
			isHitting = true; 
			record = tempRecord; 
		}
	}
	return record;
}
