#include "parsers/objparser.h"

#define PI 3.14159265	

#include "parsers/matparser.h"
#include "sphere.h"
#include "triangle.h"
#include "transf.h"
#include "matrix.h"

#include <cmath>

bool ObjectParser::readSphere(std::istringstream &reader, std::shared_ptr<Object> &o) {
	if(!checkFieldName(reader, "CENTER")) return false;
	Vec3 c; readVec3(reader, c);

	if(!checkFieldName(reader, "RADIUS")) return false;
	double r; reader >> r;

	Material *mat = nullptr;
	MaterialParser matParser;
	if(!matParser.getMaterial(reader, &mat)) return false;

	o = std::shared_ptr<Sphere> (new Sphere(c, r, mat));
	return true;
}

bool ObjectParser::readTriangle(std::istringstream &reader, std::shared_ptr<Object> &o) {
	Point3 p1, p2, p3;
	if(!checkFieldName(reader, "P1")) return false;
	readVec3(reader, p1);

	if(!checkFieldName(reader, "P2")) return false;
	readVec3(reader, p2);
	
	if(!checkFieldName(reader, "P3")) return false;
	readVec3(reader, p3);

	Material *mat = nullptr;
	MaterialParser matParser;
	if(!matParser.getMaterial(reader, &mat)) return false;

	o = std::shared_ptr<Triangle> (new Triangle(p1, p2, p3, mat));
	return true;
}

bool ObjectParser::readTransf(std::istringstream &reader, Mat4 &m, std::string transfName) {
	if(transfName.compare("scale") == 0) {
		Vec3 t; readVec3(reader, t);
		m.m[0][0] = t.x; m.m[1][1] = t.y; m.m[2][2] = t.z; 
	} else if(transfName.compare("translate") == 0) {
		Vec3 t; readVec3(reader, t);
		m.m[0][3] = t.x; m.m[1][3] = t.y; m.m[2][3] = t.z;
	} else if(transfName.compare("rotate") == 0) {
		std::string axis; 
		double angle;
		reader >> axis;
		reader >> angle;
		double cos = std::cos(angle*PI/180.0);
		double sin = std::sin(angle*PI/180.0);
		
		if(axis.compare("x") == 0) {
			m.m[1][1] = cos;
			m.m[2][2] = cos;
			m.m[1][2] = -sin;
			m.m[2][1] = sin;
			std::cout << m;
		} else if(axis.compare("y") == 0) {
			m.m[0][0] = cos;
			m.m[0][2] = sin;
			m.m[2][0] = -sin;
			m.m[2][2] = cos;
		} else if(axis.compare("z") == 0) {
			m.m[0][0] = cos;
			m.m[0][1] = -sin;
			m.m[1][0] = sin;
			m.m[1][1] = cos;
		} else { return false; }
	} else if(transfName.compare("free") == 0) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				reader >> m.m[i][j];
			}
		}
	} else if(transfName.compare("null") == 0) {
		// nothing to do
	} else { return false; }
	return true;
}

bool ObjectParser::readTransformations(std::istringstream &reader, std::shared_ptr<Object> &o) {
	std::vector<Mat4> transf;
	std::string begin;
	reader >> begin;		
	if(begin.compare("begin_transf") != 0) return false;
	while(true) {
		reader >> begin;
		
		if(begin.compare("end_transf") == 0) break;
		Mat4 m; m.identity();
		if(readTransf(reader, m, begin)) {
			transf.push_back(m);
		} else return false;
	}

	Mat4 allTransf; 
	allTransf.identity();
	if(transf.size() > 0) {
		allTransf = transf.back();
		for(int i = transf.size() - 2; i >= 0; i--) {
			allTransf = allTransf*transf[i];
		}
	}

	Transformation finalT;
	finalT.mat = allTransf;
	finalT.inv = allTransf.inverse();
	o->transf = finalT;
	return true;
}


bool ObjectParser::readObj(std::istringstream &reader, std::shared_ptr<Object> &o) {
	std::string field; reader >> field >> field;
	if(field.compare("SPHERE") == 0) {
		if(!readSphere(reader, o)) return false;
	} else if(field.compare("TRIANGLE") == 0) {
		if(!readTriangle(reader, o)) return false;
	} 
	// TODO other objs
	return readTransformations(reader, o);
}

bool ObjectParser::getObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs) {
	std::string begin; reader >> begin;
	if(begin.compare("begin_objs") != 0) return false;
	while(true) {
		reader >> begin;

		if(begin.compare("end_objs") == 0) break;
		if(begin.compare("OBJ") != 0) break;

		std::shared_ptr<Object> obj;
		if(readObj(reader, obj)) {
			objs.push_back(obj);
		} else return false;
	}
	return true;
}
