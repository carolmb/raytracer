#ifndef __SCENE__
#define __SCENE__

#include "camera.h"
#include "sphere.h"
#include "ray.h"

class Scene {
public: 
	Camera cam;
	Object *obj;
	Color bgTop;
	Color bgBottom;

	Scene() : cam(), obj(new Sphere()), bgTop(Color(0.5, 0.7, 1)), bgBottom(Color(1, 1, 1)) {}

	Color backgroundColor(Ray r) {
		Vec3 unitDir = r.dir().norm();
		double t = 0.5*(unitDir.y + 1);
		return bgTop.interpole(bgBottom, t);
	}
};

#endif