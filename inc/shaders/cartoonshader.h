#ifndef CARTOONSHADER__
#define CARTOONSHADER__

#include "shaders/shader.h"
#include <exception>
#include <limits>
#include "../materials/cartoonmat.h"
#include "../hitrecord.h"
#include "../materials/material.h"

class CartoonShader : public Shader {

public:
	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray, std::numeric_limits<float>::max());
		Color c;
		if(isHitting) {
			std::string idMat = record.m;
			std::shared_ptr<CartoonMaterial> mat = std::dynamic_pointer_cast<CartoonMaterial>(scene.mats[idMat]);

			double cos = record.n.dot(-ray.dir().norm());
			if (cos <= 0.16) { // outline
				return mat->getOutline();
			} else {
				double currentCos = -100;
				for(int i = 0; i < scene.lights.size(); i++) {
					std::shared_ptr<Light> light = scene.lights[i];
					
					Point3 newOrigin = record.p + record.n*0.01;
					Ray newRay(newOrigin, -light->getDir(record.p).norm());
					bool isShadow = false;
					double maxt = newRay.getT(light->getOrigin());
					HitRecord hr = scene.hitAnything(isShadow, newRay, maxt);
					if(isShadow) {
						continue;
					}

					cos = record.n.dot(-light->getDir(record.p).norm());
					if(currentCos < cos) {
						c = mat->getColor(cos)*light->i;
						currentCos = cos;
					}
					//currentCos = -1;
				}
				c.x = std::min(1.0, c.x);
				c.y = std::min(1.0, c.y);
				c.z = std::min(1.0, c.z);
			}
		} else {
			c = scene.backgroundColor(ray);
		}
		return correctGama(c);
	}

};

#endif
