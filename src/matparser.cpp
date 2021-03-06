#include "parsers/matparser.h"

#include "materials/blinnphongmat.h"
#include "materials/metalmat.h"
#include "materials/lambertianmat.h"
#include "materials/cartoonmat.h"
#include "materials/dielectricmat.h"
#include "materials/diffuselightmat.h"
#include "textures/texture.h"
#include "textures/constant.h"
#include "textures/checker.h"
#include "textures/image.h"
#include "textures/perlinnoise.h"

#include <cmath>

bool MaterialParser::getMaterialList(std::istringstream &reader, std::map<std::string, std::shared_ptr<Material> > &materials) {
	std::string begin; reader >> begin;
	if(begin.compare("begin_mat") != 0) return false;
	while(true) {
		reader >> begin;

		if(begin.compare("end_mat") == 0) break;
		if(begin.compare("MATERIAL") != 0) break;

		if(!getMaterial(reader, materials)) return false;
	}
	return true;
}

bool MaterialParser::getMaterial(std::istringstream &reader, std::map<std::string, std::shared_ptr<Material> > &materials) {
	std::string type; reader >> type; reader >> type;

	if(!checkFieldName(reader, "id")) return false;
	std::string id; reader >> id;
	std::shared_ptr<Material> mat;

	if(type.compare("lambertian") == 0) {
		if(!checkFieldName(reader, "texture")) return false;
		std::string type;
		reader >> type;
		Texture *texture;
		if(type.compare("const") == 0) {
			if(!checkFieldName(reader, "color")) return false;
			Vec3 kd; readVec3(reader, kd);
			texture = new ConstantTexture(kd);
		} else if(type.compare("checker") == 0) {
			if(!checkFieldName(reader, "even")) return false;
			Vec3 color1; readVec3(reader, color1);
			Texture *t1 = new ConstantTexture(color1);
			if(!checkFieldName(reader, "odd")) return false;
			Vec3 color2; readVec3(reader, color2);
			Texture *t2 = new ConstantTexture(color2);
			texture = new CheckerTexture(t1, t2);
		} else if(type.compare("image") == 0) {
			if(!checkFieldName(reader, "source")) return false;
			std::string source;
			reader >> source;
			texture = new ImageTexture(source);
		} else if(type.compare("perlin") == 0) {
			if(!checkFieldName(reader, "scale")) return false;
			double scale; reader >> scale;
			texture = new PerlinNoise(scale);
		}

		mat = std::shared_ptr<LambertianMaterial>(new LambertianMaterial(texture));
		materials.emplace(id, mat);
	} else if (type.compare("metal") == 0) {
		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);
		if(!checkFieldName(reader, "fuzz")) return false;
		double fuzz; reader >> fuzz;
		mat = std::shared_ptr<MetalMaterial>(new MetalMaterial(kd, fuzz));
		materials.emplace(id, mat);
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
		materials.emplace(id, mat);
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
		materials.emplace(id, mat);
	} else if (type.compare("dieletric") == 0) {
		if(!checkFieldName(reader, "ref")) return false;
		double n; reader >> n;

		mat = std::shared_ptr<DielectricMaterial>(new DielectricMaterial(n));
		materials.emplace(id, mat);
	} else if (type.compare("diffuselight") == 0) {
		if(!checkFieldName(reader, "emit")) return false;
		Vec3 emit; readVec3(reader, emit);
		Texture *texture = new ConstantTexture(emit);
		mat = std::shared_ptr<DiffuseLightMaterial>(new DiffuseLightMaterial(texture));
		materials.emplace(id, mat);
	} else if (type.compare("null") == 0) {
		
	} else { 
		return false; 
	}
	return true;
}
