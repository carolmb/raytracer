#ifndef __CARTOONSHADER
#define __CARTOONSHADER

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
		std::cout << "aaaaaa";
		Color c;
		if(isHitting) {
			CartoonMaterial *mat = dynamic_cast<CartoonMaterial*>(record.m);
			double cos = record.n.dot(-ray.dir().norm());
			if (cos <= mat->outlineValue() && cos >= 0) { // outline
				return mat->getOutlineColor();
			}
			for(int i = 0; i < scene.lights.size(); i++) {
				std::shared_ptr<Light> light = scene.lights[i];
				cos = record.n.dot(-light->getDir(record.p));
				c += mat->getColor(cos);
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
