#include "parsers/objparser.h"

#include "parsers/matparser.h"
#include "sphere.h"
#include "triangle.h"

#include <string>

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


bool ObjectParser::readObj(std::istringstream &reader, std::shared_ptr<Object> &o) {
	std::string field; reader >> field >> field;
	if(field.compare("SPHERE") == 0) {
		return readSphere(reader, o);
	} else if(field.compare("TRIANGLE") == 0) {
		return readTriangle(reader, o);
	} 
	// TODO other objs
	return false;
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
