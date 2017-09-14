#ifndef INPUT__
#define INPUT__

#include <string>

#include "vec3.h"
#include "light.h"
#include "camera.h"
#include "object.h"
#include "package.h"

class Input {
	static bool checkFieldName(std::istringstream &reader, std::string field);	

	static bool readVec3(std::istringstream &reader, Vec3 &a);

	static bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o);

	static bool readObj(std::istringstream &reader, std::shared_ptr<Object> &o);
	
	static bool readLight(std::istringstream &reader, std::shared_ptr<Light> &light);

	static bool readCamera(std::istringstream &reader, Camera &cam);

	static bool readObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);

	static bool readLights(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights);

	//---------------------------------------------------------------------------
	// Parses
	static bool parseHeader(std::istringstream &reader, Package *p);

	static bool parseScene(std::istringstream &reader, Package *p);

	static bool parseShader(std::istringstream &reader, Package *p);

public:
	// Read an input and returns all settings that the render will use
	static Package* readInput(std::string filename);

};

#endif
