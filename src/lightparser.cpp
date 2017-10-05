#include "parsers/lightparser.h"

#include "lights/dirlight.h"
#include "lights/amblight.h"
#include "lights/punclight.h"
#include "lights/spotlight.h"

#include <cmath>

bool LightParser::readLight(std::istringstream &reader, std::shared_ptr<Light> &light) {
	std::string field; reader >> field >> field;
	if(field.compare("DIRETIONAL") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "dir")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<DiretionalLight> (new DiretionalLight(d.norm(), i));

		return true;
	} else if(field.compare("PUNCTUAL") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "origin")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<PunctualLight> (new PunctualLight(i, d));

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

		return true;
	} else if(field.compare("AMBIENT") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;		
		if(!readVec3(reader, i)) return false;
		light = std::shared_ptr<AmbientLight> (new AmbientLight(i));
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

		std::shared_ptr<Light> light;
		if(readLight(reader, light)) {
			lights.push_back(light);
		} else return false;
	}
	return true;
}
