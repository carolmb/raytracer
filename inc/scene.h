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
};

#endif