#include "parsers/lightparser.h"

#include "lights/dirlight.h"
#include "lights/amblight.h"
#include "lights/punclight.h"
#include "lights/spotlight.h"

#include <cmath>

bool LightParser::readLight(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights) {
	std::string field; reader >> field >> field;
	std::shared_ptr<Light> light;

	if(field.compare("DIRETIONAL") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "dir")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<DiretionalLight> (new DiretionalLight(d.norm(), i));
		lights.push_back(light);

		return true;
	} else if(field.compare("PUNCTUAL") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "origin")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<PunctualLight> (new PunctualLight(i, d));
		lights.push_back(light);

		return true;
	} else if(field.compare("SPOTLIGHT") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "origin")) return false;
		Vec3 o;
		if(!readVec3(reader, o)) return false;
		
		if(!checkFieldName(reader, "dir")) return false;
		Vec3 d; 		
		if(!readVec3(reader, d)) return false;

		if(!checkFieldName(reader, "angle")) return false;
		double a; reader >> a;

		light = std::shared_ptr<SpotLight> (new SpotLight(i, o, d, a));
		lights.push_back(light);

		return true;
	} else if(field.compare("AMBIENT") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;		
		if(!readVec3(reader, i)) return false;
		light = std::shared_ptr<AmbientLight> (new AmbientLight(i));
		lights.push_back(light);

		return true;
	} else if(field.compare("AREA") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 itensity;		
		if(!readVec3(reader, itensity)) return false;
		
		if(!checkFieldName(reader, "llc")) return false;
		Vec3 llc; 		
		if(!readVec3(reader, llc)) return false;
		
		if(!checkFieldName(reader, "h")) return false;
		Vec3 h;
		if(!readVec3(reader, h)) return false;
		
		if(!checkFieldName(reader, "v")) return false;
		Vec3 v;
		if(!readVec3(reader, v)) return false;
		
		if(!checkFieldName(reader, "nx")) return false;
		int nx;	reader >> nx;

		if(!checkFieldName(reader, "ny")) return false;
		int ny;	reader >> ny;	
		
		if(!checkFieldName(reader, "samples")) return false;
		int samples; reader >> samples;	
		

		double stepX = 1.0/nx;
		double stepY = 1.0/ny;
	
		itensity = itensity/(nx*ny*samples);
		for(float i = 0; i <= 1.03; i+=stepX) {
			for(float j = 0; j <= 1.03; j+=stepY) {
				for(float s = 0; s < samples; s++) {
					Vec3 origin = llc + h*i + v*j;
					std::cout << origin;
					std::shared_ptr<Light> light =
						std::shared_ptr<PunctualLight> (new PunctualLight(itensity, origin));
					lights.push_back(light);
				}
			}
		}

		return true;
	}
	// TODO other objs
	return false;
}

bool LightParser::getLightList(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights) {
	std::string begin; reader >> begin;
	if(begin.compare("begin_lights") != 0) return false;
	while(true) {
		reader >> begin;

		if(begin.compare("end_lights") == 0) break;
		if(begin.compare("LIGHT") != 0) break;

		if(!readLight(reader, lights)) return false;
	}
	return true;
}
