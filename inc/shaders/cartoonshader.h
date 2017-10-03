#ifndef CARTOONSHADER__
#define CARTOONSHADER__

#include "shader.h"
#include <exception>
#include "../materials/cartoonmat.h"
#include "../hitrecord.h"
#include "../material.h"

class CartoonShader : public Shader {

public:
	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);
		Color c;
		if(isHitting) {
			CartoonMaterial *mat = dynamic_cast<CartoonMaterial*>(record.m);
			double cos = record.n.dot(-ray.dir().norm());
			if (cos <= 0.16 && cos >= 0) { // outline
				return mat->getOutline();
			}
			double currentCos = -100;
			for(int i = 0; i < scene.lights.size(); i++) {
				std::shared_ptr<Light> light = scene.lights[i];
				cos = record.n.dot(light->getDir(record.p).norm());
				if(currentCos < cos) {
					c = mat->getColor(cos);
					currentCos = cos;
				}
			}
			c.x = std::min(1.0, c.x);
			c.y = std::min(1.0, c.y);
			c.z = std::min(1.0, c.z);
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}

};

#endif
