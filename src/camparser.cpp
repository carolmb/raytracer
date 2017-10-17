#include "parsers/camparser.h"

#include <string>
#include <cmath>
#define pi 3.1415

bool CameraParser::getCamera(std::istringstream &reader, Camera **cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;

	if(field.compare("PERSPECTIVE") == 0) {
		Vec3 viewpoint, viewdir, viewplanenormal, viewup;
		int oblique;

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

		if(!checkFieldName(reader, "isoblique")) return false;
		reader >> oblique;

		/*
		look from (viewpoint), look at (viewdir), up
		*/
		
		// camera frame
		Vec3 gaze = (viewdir - viewpoint).norm(); 
		Vec3 u = -viewup.cross(gaze).norm();
		Vec3 v = -gaze.cross(u).norm();		

		/*
		vertical field of view (angle), aspect ratio (double), distance to focus (double), 
		view plane normal
		*/

		double theta = vfov * pi / 180;
		double d = (viewpoint - viewdir).len();
		double halfHeight = d/std::tan(theta/2);
		double halfWidth = halfHeight/aspectRatio;
		std::cout << halfHeight << " " << halfWidth;
		
		Vec3 origin = viewpoint;
		Vec3 w = u.cross(v).norm();

		if(oblique) {
			w = -(viewpoint - viewdir).norm();
		}

		*cam = new PerspectiveCamera(origin, d, u, v, w, halfWidth, halfHeight);

	} else if(field.compare("ORTHOGRAPHIC") == 0) {
		double b, t, l, r;
		int oblique;

		if(!checkFieldName(reader, "bottom")) return false;
		reader >> b;

		if(!checkFieldName(reader, "top")) return false;
		reader >> t;

		if(!checkFieldName(reader, "left")) return false;
		reader >> l;

		if(!checkFieldName(reader, "right")) return false;
		reader >> r;

		Vec3 viewpoint, viewdir, viewplanenormal, viewup;

		if(!checkFieldName(reader, "viewpoint")) return false;
		readVec3(reader, viewpoint);

		if(!checkFieldName(reader, "viewdir")) return false;
		readVec3(reader, viewdir);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		if(!checkFieldName(reader, "isoblique")) return false;
		reader >> oblique;

		Vec3 w = -viewdir.norm();
		Vec3 u = -w.cross(viewup.norm()).norm();
		Vec3 v = w.cross(u).norm();
		
		*cam = new ParallelCamera(u, v, w, viewpoint, b, t, l, r);
	
	} else {
		return false;
	}
	return true;
}
