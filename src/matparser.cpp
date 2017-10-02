#include "parsers/matparser.h"

#include "materials/blinnphongmat.h"
#include "materials/metalmat.h"
#include "materials/lambertianmat.h"
#include "materials/cartoonmat.h"

bool MaterialParser::getMaterial(std::istringstream &reader, Material *mat) {

	if(!checkFieldName(reader, "MATERIAL")) return false;
	std::string type; reader >> type;

	if(type.compare("lambertian") == 0) {
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);

		mat = new LambertianMaterial(kd);
	} else if (type.compare("metal") == 0) {
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		if(!checkFieldName(reader, "fuzz")) return false;
		double fuzz; reader >> fuzz;

		mat = new MetalMaterial(kd, fuzz);
	} else if (type.compare("blinnphong") == 0) {
		if(!checkFieldName(reader, "ka")) return false;
		Vec3 ka; readVec3(reader, ka);
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		if(!checkFieldName(reader, "ks")) return false;
		Vec3 ks; readVec3(reader, ks);
		if(!checkFieldName(reader, "exps")) return false;
		double exps; reader >> exps;

		mat = new BlinnPhongMaterial(ka, kd, ks, exps);
	} else if (type.compare("cartoon") == 0) {
		std::vector<Vec3> g;
		std::string begin;
		reader >> begin;
		if(begin.compare("begin_gradient") != 0) return false;
		while(true) {
			reader >> begin;
			if(begin.compare("end_gradient") == 0) break;
			if(begin.compare("color") != 0) return false;
			Vec3 color;
			readVec3(reader, color);
			g.push_back(color);
		}
		std::vector<double> i;
		reader >> begin;
		if(begin.compare("begin_intervals") != 0) return false;
		while(true) {
			reader >> begin;
			if(begin.compare("end_intervals") == 0) break;
			double angle;
			angle = std::stod (begin);
			i.push_back(angle);
		}
		mat = new CartoonMaterial(g, i);
	} else if (type.compare("null") == 0) {
		mat = NULL;
	} else { return false; }
	return true;
}