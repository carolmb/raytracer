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
	std::vector<Light> lights;
	Light ambient;

	Scene() {}
	Scene(Camera cam, 
		std::vector<std::shared_ptr<Object> > o, 
		Color bgtl, Color bgtr, Color bgbl, Color bgbr, 
		std::vector<Light> l, Light a) : 
		cam(cam), objs(o), bgtl(bgtl), bgtr(bgtr), bgbl(bgbl), bgbr(bgbr), lights(l), ambient(a) { 
			for(int i = 0; i < lights.size(); i++) {
				lights[i].dir = lights[i].dir.norm(); 
			}
		}
		

	Color backgroundColor(Ray r);

	HitRecord hitAnything(bool &isHitting, Ray ray);

};

#endif
