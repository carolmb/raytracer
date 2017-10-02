#include "parsers/camparser.h"

#include <string>

bool CameraParser::getCamera(std::istringstream &reader, Camera &cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;
	if(field.compare("PERSPECTIVE") == 0) {
		std::string camFields[] = {"ORIGIN", "LLC", "H", "V"};
		Vec3 camValues[4];
		for(int i = 0; i < 4; i++) {
			if(!checkFieldName(reader, camFields[i])) return false;
			readVec3(reader, camValues[i]);
		}
		cam = Camera(camValues[0], camValues[1], camValues[2], camValues[3]);
	} else {
		// TODO others cameras
		return false;
	}
	return true;
}