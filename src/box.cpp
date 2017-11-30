#include "objs/box.h"

#include <cmath>
#include <iostream>

Box::Box(Point3 e0, Point3 e7, std::string idMat, Transformation *t) : 
	Object(idMat, t) {
	Point3 e1(e7.x, e0.y, e0.z);
	Point3 e2(e7.x, e7.y, e0.z);
	Point3 e3(e0.x, e7.y, e0.z); 
	Point3 e4(e0.x, e0.y, e7.z); 
	Point3 e5(e7.x, e0.y, e7.z); 
	Point3 e6(e0.x, e7.y, e7.z);
	triangles.push_back(Triangle(e0, e1, e3, idMat, true, t));
	triangles.push_back(Triangle(e3, e1, e2, idMat, true, t));
	triangles.push_back(Triangle(e1, e7, e2, idMat, true, t));
	triangles.push_back(Triangle(e1, e5, e7, idMat, true, t));
	triangles.push_back(Triangle(e3, e7, e6, idMat, true, t));
	triangles.push_back(Triangle(e3, e2, e7, idMat, true, t));
	triangles.push_back(Triangle(e4, e3, e6, idMat, true, t));
	triangles.push_back(Triangle(e4, e0, e3, idMat, true, t));
	triangles.push_back(Triangle(e7, e4, e6, idMat, true, t));
	triangles.push_back(Triangle(e7, e5, e4, idMat, true, t));
	triangles.push_back(Triangle(e1, e4, e5, idMat, true, t));
	triangles.push_back(Triangle(e1, e0, e4, idMat, true, t));
}

void Box::setTransf(Transformation *t) {
	for(int i = 0; i < triangles.size(); i ++){
		triangles[i].setTransf(t);
	}
}

bool Box::hit(Ray ray, HitRecord &hit, double &mint, double maxt) {
	for(int i = 0; i < triangles.size(); i++) {
		if(triangles[i].hit(ray, hit, mint, maxt)) {
			return true;
		}
	}
	return false;
}
