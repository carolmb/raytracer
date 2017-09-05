#ifndef SCENE__
#define SCENE__

#include "camera.h"
#include "object.h"
#include "ray.h"
#include "vec3.h"
#include "light.h"

#include <vector>
#include <memory>

class Scene {
public: 
	Camera cam;
	std::vector<std::shared_ptr<Object> > objs;
	Color bgtl;
	Color bgtr;
	Color bgbl;
	Color bgbr;
	Light light;
	Light ambient;

	Scene() {}
	Scene(Camera cam, 
		std::vector<std::shared_ptr<Object> > o, 
		Color bgtl, Color bgtr, Color bgbl, Color bgbr, 
		Light l, Light a) : 
		cam(cam), objs(o), bgtl(bgtl), bgtr(bgtr), bgbl(bgbl), bgbr(bgbr), light(l), ambient(a) { light.dir = light.dir.norm(); }

	Color backgroundColor(Ray r);

	HitRecord hitAnything(bool &isHitting, Ray ray);

};

#endif
