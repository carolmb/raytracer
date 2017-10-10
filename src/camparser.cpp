#include "parsers/camparser.h"

#include <string>
#include <cmath>
#define pi 3.1415

bool CameraParser::getCamera(std::istringstream &reader, Camera **cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;

	if(field.compare("PERSPECTIVE") == 0) {
		Vec3 viewpoint, viewdir, viewplanenormal, viewup;
	
		if(!checkFieldName(reader, "viewpoint")) return false;
		readVec3(reader, viewpoint);

		if(!checkFieldName(reader, "viewdir")) return false;
		readVec3(reader, viewdir);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		double vfov, aspectRatio;

		if(!checkFieldName(reader, "vfov")) return false;
		reader >> vfov;

		if(!checkFieldName(reader, "aspectratio")) return false;
		render >> aspectRatio;

		/*
		look from (viewpoint), look at (viewdir), up
		*/
		
		// camera frame
		Vector3 gaze = (viewpoint - viewdir).norm(); 
		Vec3 u = viewup.cross(gaze).norm();
		Vec3 v = gaze.cross(u).norm();		

		/*
		vertical field of view (angle), aspect ratio (double), distance to focus (double), view plane normal
		*/

		double theta = vfov * pi / 180;
		double halfHeight = std::tan(theta/2);
		double haldWidth = aspectRatio * halfHeight;

		Vec3 origin = viewpoint;
		Vec3 h = u * (2*haldWidth);
		Vec3 v = v * (2*halfHeight);
		Point3 llc = Vec3();

		*cam = new PerspectiveCamera(origin, llc, h, v);

	} else if(field.compare("ORTHOGRAPHIC_PARALLEL") == 0) {
		double bottom, top, left, right;

		if(!checkFieldName(reader, "bottom")) return false;
		reader >> bottom;

		if(!checkFieldName(reader, "top")) return false;
		render >> top;

		if(!checkFieldName(reader, "left")) return false;
		render >> left;

		if(!checkFieldName(reader, "right")) return false;
		render >> right;

		Vec3 viewpoint, viewdir, viewplanenormal, viewup;

		if(!checkFieldName(reader, "viewpoint")) return false;
		readVec3(reader, viewpoint);

		if(!checkFieldName(reader, "viewdir")) return false;
		readVec3(reader, viewdir);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		double horizontal = right - left;
		double vertical = top - bottom;
		Vec3 w = -viewdir.norm();
		Vec3 u = w.cross(viewup).norm() * horizontal;
		Vec3 v = w.cross(u).norm() * vertical;
		
		*cam = new OrthographicParallelCamera(u, v, w, viewpoint);
	
	} else if(field.compare("OBLIQUE_PARALLEL") == 0) {
		double bottom, top, left, right;

		if(!checkFieldName(reader, "bottom")) return false;
		reader >> bottom;

		if(!checkFieldName(reader, "top")) return false;
		render >> top;

		if(!checkFieldName(reader, "left")) return false;
		render >> left;

		if(!checkFieldName(reader, "right")) return false;
		render >> right;

		Vec3 viewpoint, viewdir, viewplanenormal, viewup;

		if(!checkFieldName(reader, "viewpoint")) return false;
		readVec3(reader, viewpoint);

		if(!checkFieldName(reader, "viewdir")) return false;
		readVec3(reader, viewdir);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		double horizontal = right - left;
		double vertical = top - bottom;
		Vec3 w = -viewdir.norm();
		Vec3 u = w.cross(viewup).norm() * horizontal;
		Vec3 v = w.cross(u).norm() * vertical;

		*cam = new ObliqueParallelCamera(u, v, w, viewpoint, viewdir);
	
	} else {
		return false;
	}
	return true;
}
