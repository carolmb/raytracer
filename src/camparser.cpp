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

		double vfov, aspectRatio, dist;

		if(!checkFieldName(reader, "vfov")) return false;
		reader >> vfov;

		if(!checkFieldName(reader, "aspectratio")) return false;
		reader >> aspectRatio;

		if(!checkFieldName(reader, "camdist")) return false;
		reader >> dist;

		/*
		look from (viewpoint), look at (viewdir), up
		*/
		
		// camera frame
		Vec3 gaze = (viewpoint - viewdir).norm(); 
		Vec3 u = viewup.cross(gaze).norm();
		Vec3 v = gaze.cross(u).norm();		

		/*
		vertical field of view (angle), aspect ratio (double), distance to focus (double), view plane normal
		*/

		double theta = vfov * pi / 180;
		double halfHeight = std::tan(theta/2);
		double haldWidth = aspectRatio * halfHeight;
		//double d = (viewpoint - viewdir).len();

		Vec3 origin = viewpoint;
		Vec3 horizontal = u * (2*haldWidth);
		Vec3 vertical = v * (2*halfHeight);
		Vec3 w = -viewdir.norm();

		*cam = new PerspectiveCamera(origin, dist, horizontal, vertical, w);

	} else if(field.compare("ORTHOGRAPHIC_PARALLEL") == 0) {
		double bottom, top, left, right;

		if(!checkFieldName(reader, "bottom")) return false;
		reader >> bottom;

		if(!checkFieldName(reader, "top")) return false;
		reader >> top;

		if(!checkFieldName(reader, "left")) return false;
		reader >> left;

		if(!checkFieldName(reader, "right")) return false;
		reader >> right;

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
		reader >> top;

		if(!checkFieldName(reader, "left")) return false;
		reader >> left;

		if(!checkFieldName(reader, "right")) return false;
		reader >> right;

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
