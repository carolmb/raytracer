#include "parsers/objparser.h"
#include "parsers/matparser.h"
#include "objs/sphere.h"
#include "objs/triangle.h"
#include "objs/plane.h"
#include "objs/box.h"
#include "objs/mesh.h"
#include "util/transf.h"
#include "util/mat4.h"

bool ObjectParser::readMesh(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &meshList) {
	if(!checkFieldName(reader, "SOURCE")) return false;
	std::string fileSource;
	reader >> fileSource;

	if(!checkFieldName(reader, "MATERIAL")) return false;
	std::string idMat;
	reader >> idMat;
	std::cout << "aaaaaaaaaaaaaaaaa " << idMat;

	objl::Loader Loader;
	bool loadout = Loader.LoadFile(fileSource);
	if(loadout) {
		for(int i = 0; i < Loader.LoadedMeshes.size(); i++) {
			objl::Mesh curMesh = Loader.LoadedMeshes[i];
			std::shared_ptr<Mesh> newMesh =
				std::shared_ptr<Mesh>(new Mesh(curMesh, idMat, new Transformation()));
			meshList.push_back(newMesh);
		}
	} else {
		return false;
	}

	Transformation *t = readTransformations(reader);
	if(t == NULL) return false;

	for(int i = 0; i < meshList.size(); i++) {
		meshList[i]->setTransf(t);
	}
	// TODO set transformation
	return true;
}

bool ObjectParser::readSphere(std::istringstream &reader, std::shared_ptr<Object> &o) {
	if(!checkFieldName(reader, "CENTER")) return false;
	Vec3 c; readVec3(reader, c);

	if(!checkFieldName(reader, "RADIUS")) return false;
	double r; reader >> r;

	if(!checkFieldName(reader, "MATERIAL")) return false; // mat id
	std::string idMat; reader >> idMat;

	Transformation *t = readTransformations(reader);

	o = std::shared_ptr<Sphere> (new Sphere(c, r, idMat, t));
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

	if(!checkFieldName(reader, "culling")) return false;
	bool culling;
	reader >> culling;

	if(!checkFieldName(reader, "MATERIAL")) return false; // mat id
	std::string idMat; reader >> idMat;

	Transformation *t = readTransformations(reader);

	o = std::shared_ptr<Triangle> (new Triangle(p1, p2, p3, idMat, culling, t));
	return true;
}

bool ObjectParser::readBox(std::istringstream &reader, std::shared_ptr<Object> &o) {
	Point3 p1, p2;
	if(!checkFieldName(reader, "P1")) return false;
	readVec3(reader, p1);

	if(!checkFieldName(reader, "P8")) return false;
	readVec3(reader, p2);

	if(!checkFieldName(reader, "MATERIAL")) return false; // mat id
	std::string idMat; reader >> idMat;

	Transformation *t = readTransformations(reader);

	o = std::shared_ptr<Box> (new Box(p1, p2, idMat, t));
	return true;
}

bool ObjectParser::readPlane(std::istringstream &reader, std::shared_ptr<Object> &o) {
	if(!checkFieldName(reader, "ORIGIN")) return false;
	Vec3 origin; readVec3(reader, origin);

	if(!checkFieldName(reader, "NORMAL")) return false;
	Vec3 normal; readVec3(reader, normal);

	if(!checkFieldName(reader, "MATERIAL")) return false; // mat id
	std::string idMat; reader >> idMat;

	Transformation *t = readTransformations(reader);

	o = std::shared_ptr<Plane> (new Plane(origin, normal, idMat, t));
	return true;
}

bool ObjectParser::readTransf(std::istringstream &reader, Mat4 &m, std::string transfName) {
	if(transfName.compare("scale") == 0) {
		Vec3 t; readVec3(reader, t);
		m = Mat4::scaling(t);
	} else if(transfName.compare("translate") == 0) {
		Vec3 t; readVec3(reader, t);
		m = Mat4::translation(t);
	} else if(transfName.compare("rotate") == 0) {
		Vec3 t; readVec3(reader, t);
		m = Mat4::rotation(t);
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

Transformation* ObjectParser::readTransformations(std::istringstream &reader) {
	std::vector<Mat4> transf;
	std::string begin;
	reader >> begin;
	if(begin.compare("begin_transf") != 0) return NULL;
	while(true) {
		reader >> begin;

		if(begin.compare("end_transf") == 0) break;
		Mat4 m = Mat4::identity();
		if(readTransf(reader, m, begin)) {
			transf.push_back(m);
		} else return NULL;
	}

	Mat4 allTransf = Mat4::identity();
	for(int i = 0; i < transf.size(); i++) {
		allTransf = transf[i]*allTransf;
	}

	Transformation *finalT = new Transformation();
	finalT->mat = allTransf;
	finalT->inv = allTransf.inverse();
	return finalT;
}

bool ObjectParser::readObj(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs) {
	std::string field; reader >> field >> field;
	if(field.compare("SPHERE") == 0) {
		std::shared_ptr<Object> o;
		if(!readSphere(reader, o)) return false;
		objs.push_back(o);
		return true;
	} else if(field.compare("TRIANGLE") == 0) {
		std::shared_ptr<Object> o;
		if(!readTriangle(reader, o)) return false;
		objs.push_back(o);
		return true;
	} else if(field.compare("PLANE") == 0) {
		std::shared_ptr<Object> o;
		if(!readPlane(reader, o)) return false;
		objs.push_back(o);
		return true;
	} else if(field.compare("BOX") == 0) {
		std::shared_ptr<Object> o;
		if(!readBox(reader, o)) return false;
		objs.push_back(o);
		return true;
	} else if(field.compare("MESH") == 0) {
		std::vector<std::shared_ptr<Object> > os;
		if(!readMesh(reader, os)) return false;
		for(int i = 0; i < os.size(); i++) {
			objs.push_back(os[i]);
		}
		return true;
	}
	return false;
	// TODO other objs
}

bool ObjectParser::getObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs) {
	std::string begin; reader >> begin;
	if(begin.compare("begin_objs") != 0) return false;
	while(true) {
		reader >> begin;

		if(begin.compare("end_objs") == 0) break;
		if(begin.compare("OBJ") != 0) break;

		if(!readObj(reader, objs)) return false;
	}
	return true;
}
