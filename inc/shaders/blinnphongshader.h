#ifndef __BLINNPHONGSHADER__
#define __BLINNPHONGSHADER__

#include "shader.h"
#include <exception>
#include "../materials/blinnphongmat.h"
#include "../hitrecord.h"
#include "../material.h"

class BlinnPhongShader : public Shader {

public:
	Color getColor(Scene scene, Ray ray) {
		bool isHitting = false;
		HitRecord record = scene.hitAnything(isHitting, ray);
	
		Color c;
		if(isHitting) {
			BlinnPhongMaterial *mat = dynamic_cast<BlinnPhongMaterial*>(record.m);
			
			c = mat->ka*scene.ambient->i;
			for(int i = 0; i < scene.lights.size(); i++) {
				std::shared_ptr<Light> light = scene.lights[i];
		
				// shadow
				Point3 newOrigin = record.p + record.n*0.01;
				Ray newRay(newOrigin, light->getDir(record.p).norm());
				bool isShadow = false;
				HitRecord hr = scene.hitAnything(isShadow, newRay);
				if(isShadow) {
					continue;
				}
	
				// diffuse
				double diffuseComponent = std::max(record.n.dot(light->getDir(record.p)), 0.0);
				c += mat->kd*light->i*diffuseComponent;
	
				// specular
				Vec3 v = (scene.cam.getOrigin() - record.p).norm();
				Vec3 h = (v + light->getDir(record.p)).norm();
				double specularComponent = std::pow(std::max(h.dot(record.n), 0.0), mat->exps);
				c += mat->ks*light->i*specularComponent;
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
