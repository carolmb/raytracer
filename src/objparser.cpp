#include "parsers/objparser.h"

#include "parsers/matparser.h"
#include "sphere.h"
#include "triangle.h"
#include "transf.h"
#include "matrix.h"

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
		
	} else if(transfName.compare("translation") == 0) {
		Vec3 t; readVec3(reader, t);
		m.m[0][3] = t.x; m.m[1][3] = t.y; m.m[2][3] = t.z; m.m[3][3] = 1;
	} else if(transfName.compare("rotation") == 0) {
		Vec3 t; readVec3(reader, t);
		
	} else if(transfName.compare("free") == 0) {
		for(int i = 0; i < 4; i++) {
			for(int j = 0; j < 4; j++) {
				reader >> m.m[i][j];
			}
		}
	} else if(transfName.compare("null") == 0) {
		// nothing to do
	} else {
		return false;
	}
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
		for(int i = transf.size() - 2; i > 0; i--) {
			allTransf = allTransf*transf[i];
		}
	}

	// multiplica ao contrário (pilha)
	Transformation finalT;
	finalT.mat = allTransf;
	std::cout << finalT.mat;
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
