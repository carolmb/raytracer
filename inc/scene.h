#ifndef __SCENE__
#define __SCENE__

#include "camera.h"
#include "sphere.h"

class Scene {
public: 
	Camera cam;
	Sphere sphere;

	Scene() : cam(), sphere() {}
};

#endif