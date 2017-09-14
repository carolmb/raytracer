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
	std::vector<std::shared_ptr<Light> >  lights;
	std::shared_ptr<AmbientLight> ambient;

	Scene() {}
	Scene(Camera cam, 
		std::vector<std::shared_ptr<Object> > o, 
		Color bgtl, Color bgtr, Color bgbl, Color bgbr, 
		std::vector<std::shared_ptr<Light> > l, std::shared_ptr<AmbientLight> &a) : 
		cam(cam), objs(o), bgtl(bgtl), bgtr(bgtr), bgbl(bgbl), bgbr(bgbr), lights(l), ambient(a) {}
		

	Color backgroundColor(Ray r);

	HitRecord hitAnything(bool &isHitting, Ray ray);

};

#endif
