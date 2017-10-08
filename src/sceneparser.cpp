#include "parsers/sceneparser.h"
#include "parsers/lightparser.h"
#include "parsers/objparser.h"
#include "parsers/camparser.h"

#include "lights/amblight.h"

bool SceneParser::getScene(std::istringstream &reader, Package *p) {
	// Background Colors
	std::string colorFields[] = {"TL", "TR", "BL", "BR"};
	Color colors[4];
	for(int i = 0; i < 4; i++) {
		if(!checkFieldName(reader, colorFields[i])) return false;
		readVec3(reader, colors[i]);
	}

	// Camera
	CameraParser camParser;
	Camera *cam;
	if(!camParser.getCamera(reader, &cam)) return false;

	// Obj list
	ObjectParser objParser;
	std::vector<std::shared_ptr<Object> > objs;
	if(!objParser.getObjList(reader, objs)) return false;

	LightParser lightParser;
	std::vector<std::shared_ptr<Light> > lights;
	if(!lightParser.getLightList(reader, lights)) return false;
	std::shared_ptr<AmbientLight> ambient = std::dynamic_pointer_cast<AmbientLight>(lights.back());
	lights.pop_back();

	p->scene = Scene(cam, objs, colors[0], colors[1], colors[2], colors[3], lights, ambient);
	return true;
}