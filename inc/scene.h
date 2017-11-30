#ifndef SCENE__
#define SCENE__

#include "camera.h"
#include "objs/object.h"
#include "ray.h"
#include "util/vec3.h"
#include "lights/light.h"
#include "lights/amblight.h"

#include <vector>
#include <memory>
#include <map>

class Scene {
public: 
	Camera *cam;
	std::vector<std::shared_ptr<Object> > objs;
	Color bgtl;
	Color bgtr;
	Color bgbl;
	Color bgbr;
	std::vector<std::shared_ptr<Light> >  lights;
	std::shared_ptr<AmbientLight> ambient;
	std::map<std::string, std::shared_ptr<Material> > mats;

	Scene() {}
	Scene(Camera *cam, 
		std::vector<std::shared_ptr<Object> > o, 
		Color bgtl, Color bgtr, Color bgbl, Color bgbr, 
		std::vector<std::shared_ptr<Light> > l, std::shared_ptr<AmbientLight> &a,
		std::map<std::string, std::shared_ptr<Material> > mats) : 
		cam(cam), objs(o), bgtl(bgtl), bgtr(bgtr), bgbl(bgbl), bgbr(bgbr), lights(l), ambient(a), mats(mats) {}
		

	Color backgroundColor(Ray r);

	HitRecord hitAnything(bool &isHitting, Ray ray, double maxt);

};

#endif
