#include "parsers/camparser.h"

#include <string>
#include <cmath>
#define pi 3.1415

bool CameraParser::getCamera(std::istringstream &reader, Camera **cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;

	if(field.compare("PERSPECTIVE") == 0) {
		Vec3 lookfrom, lookat, viewplanenormal, viewup;
		int oblique;
		double aperture, fdist;

		if(!checkFieldName(reader, "lookfrom")) return false;
		readVec3(reader, lookfrom);

		if(!checkFieldName(reader, "lookat")) return false;
		readVec3(reader, lookat);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		double vfov, aspectRatio, dist;

		if(!checkFieldName(reader, "vfov")) return false;
		reader >> vfov;

		if(!checkFieldName(reader, "aspectratio")) return false;
		reader >> aspectRatio;

		if(!checkFieldName(reader, "aperture")) return false;
		reader >> aperture;

		if(!checkFieldName(reader, "fdist")) return false;
		reader >> fdist;

		if(!checkFieldName(reader, "isoblique")) return false;
		reader >> oblique;
		
		//camera frame
		Vec3 gaze = (lookat - lookfrom).norm(); 
		Vec3 u = -viewup.cross(gaze).norm();
		Vec3 v = -gaze.cross(u).norm();		
		Vec3 w = u.cross(v).norm();

		double theta = vfov * pi / 180;
		double d = (lookat - lookfrom).len();
		double halfHeight = d/std::tan(theta/2);
		double halfWidth = halfHeight/aspectRatio;
		
		Vec3 origin = lookfrom;

		if(oblique) {
			w = (lookat - lookfrom).norm();
		}

		*cam = new PerspectiveCamera(origin, d, u, v, w, halfWidth, halfHeight, aperture, fdist);

	} else if(field.compare("PARALLEL") == 0) {
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

		Vec3 lookfrom, viewplanenormal, viewup, aspectRatio;

		if(!checkFieldName(reader, "lookfrom")) return false;
		readVec3(reader, lookfrom);

		if(!checkFieldName(reader, "viewplanenormal")) return false;
		readVec3(reader, viewplanenormal);

		if(!checkFieldName(reader, "viewup")) return false;
		readVec3(reader, viewup);

		if(!checkFieldName(reader, "isoblique")) return false;
		reader >> oblique;
		
		Vec3 w = -viewplanenormal.norm();
		Vec3 u = -w.cross(viewup.norm()).norm();
		Vec3 v = w.cross(u);

		if(oblique) { // read viewdir
			if(!checkFieldName(reader, "viewdir")) return false;
			readVec3(reader, w);
			w = -w.norm();
		}
		*cam = new ParallelCamera(u, v, w, lookfrom, b, t, l, r);
	
	} else {
		return false;
	}
	return true;
}
