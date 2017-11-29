#include "parsers/matparser.h"

#include "materials/blinnphongmat.h"
#include "materials/metalmat.h"
#include "materials/lambertianmat.h"
#include "materials/cartoonmat.h"

#include <cmath>

bool MaterialParser::getMaterial(std::istringstream &reader, std::shared_ptr<Material> &mat) {

	if(!checkFieldName(reader, "MATERIAL")) return false;
	std::string type; reader >> type;

	if(type.compare("lambertian") == 0) {
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		mat = std::shared_ptr<LambertianMaterial>(new LambertianMaterial(kd));

	} else if (type.compare("metal") == 0) {
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		if(!checkFieldName(reader, "fuzz")) return false;
		double fuzz; reader >> fuzz;
		mat = std::shared_ptr<MetalMaterial>(new MetalMaterial(kd, fuzz));
	
	} else if (type.compare("blinnphong") == 0) {
		if(!checkFieldName(reader, "ka")) return false;
		Vec3 ka; readVec3(reader, ka);
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		if(!checkFieldName(reader, "ks")) return false;
		Vec3 ks; readVec3(reader, ks);
		if(!checkFieldName(reader, "exps")) return false;
		double exps; reader >> exps;
		mat = std::shared_ptr<BlinnPhongMaterial>(new BlinnPhongMaterial(ka, kd, ks, exps));
	
	} else if (type.compare("cartoon") == 0) {
		std::string fieldName;
		if(!checkFieldName(reader, "outline")) return false;
		Color ol; readVec3(reader, ol);

		// list of colors
		std::vector<Color> g;
		reader >> fieldName;
		if(fieldName.compare("begin_gradient") != 0) return false;
		int n = 0;
		while(true) {
			reader >> fieldName;
			if(fieldName.compare("end_gradient") == 0) break;
			if(fieldName.compare("color" + std::to_string(n)) != 0) return false;
			Color color;
			readVec3(reader, color);
			g.push_back(color);
			n++;
		}
		
		// list of intervals
		std::vector<double> i;
		reader >> fieldName;
		if(fieldName.compare("begin_intervals") != 0) return false;
		while(true) {
			reader >> fieldName;
			if(fieldName.compare("end_intervals") == 0) break;
			double angle = std::stod (fieldName);
			i.push_back(angle);
		}
		mat = std::shared_ptr<CartoonMaterial>(new CartoonMaterial(ol, g, i));
	
	} else if (type.compare("null") == 0) {
		
	} else { 
		return false; 
	}
	return true;
}
