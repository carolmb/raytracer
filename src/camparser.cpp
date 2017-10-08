#include "parsers/camparser.h"

#include <string>

bool CameraParser::getCamera(std::istringstream &reader, Camera **cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;
	
	Point3 bottom, top, left, right;

	if(!checkFieldName(reader, "bottom")) return false;
	readVec3(reader, bottom);

	if(!checkFieldName(reader, "top")) return false;
	readVec3(reader, top);

	if(!checkFieldName(reader, "left")) return false;
	readVec3(reader, left);

	if(!checkFieldName(reader, "right")) return false;
	readVec3(reader, right);

	Vec3 viewpoint, viewdir, viewplanenormal, viewup;
	
	if(!checkFieldName(reader, "viewpoint")) return false;
	readVec3(reader, viewpoint);

	if(!checkFieldName(reader, "viewdir")) return false;
	readVec3(reader, viewdir);

	if(!checkFieldName(reader, "viewplanenormal")) return false;
	readVec3(reader, viewplanenormal);

	if(!checkFieldName(reader, "viewup")) return false;
	readVec3(reader, viewup);


	if(field.compare("PERSPECTIVE") == 0) {

		Vec3 origin = viewpoint;
		Vec3 h = right - left;
		Vec3 v = top - bottom;
		Point3 llc = left + bottom;

		*cam = new PerspectiveCamera(origin, llc, h, v);

	} else if(field.compare("ORTHOGRAPHIC_PARALLEL") == 0) {

		Vec3 w = -viewdir;
		Vec3 u = w.cross(viewup);
		Vec3 v = w.cross(u);
		Vec3 horizontal = right - left;
		Vec3 vertical = top - bottom;
		

		*cam = new OrthographicParallelCamera(u, v, w, viewpoint, bottom, top, left, right);
	
	} else if(field.compare("OBLIQUE_PARALLEL") == 0) {

		Vec3 w = -viewdir;
		Vec3 u = w.cross(viewup);
		Vec3 v = w.cross(u);
		Vec3 horizontal = right - left;
		Vec3 vertical = top - bottom;

		*cam = new ObliqueParallelCamera(u, v, w, viewpoint, viewdir, bottom, top, left, right);
	
	} else {
		return false;
	}
	return true;
}