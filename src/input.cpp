#include "input.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "preprocess.h"
#include "scene.h"
#include "render.h"
#include "sphere.h"

#include "shader.h"
#include "shaders/normalrgbshader.h"
#include "shaders/depthshader.h"
#include "shaders/diffuseshader.h"
#include "shaders/recursiveshader.h"
#include "shaders/blinnphongshader.h"
#include "shaders/cartoonshader.h"

#include "materials/blinnphongmat.h"
#include "materials/metalmat.h"
#include "materials/lambertianmat.h"
#include "materials/cartoonmat.h"

bool Input::checkFieldName(std::istringstream &reader, std::string field) {
	std::string f;
	reader >> f;
	if(field.compare(f) != 0) return false;
	reader >> f;
	if(f.compare("=") != 0) return false;
	return true;
}

bool Input::readVec3(std::istringstream &reader, Vec3 &a) {
 	std::string r, g, b;
 	reader >> r >> g >> b;
 	a.x = std::stod (r);
 	a.y = std::stod (g);
 	a.z = std::stod (b);
	return true;
}

bool Input::readSphere(std::istringstream &reader, std::shared_ptr<Object> &o) {
	if(!checkFieldName(reader, "CENTER")) return false;
	Vec3 c; readVec3(reader, c);

	if(!checkFieldName(reader, "RADIUS")) return false;
	double r; reader >> r;

	if(!checkFieldName(reader, "MATERIAL")) return false;
	std::string type; reader >> type;

	Material *mat;
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
			reader >> angle;
			i.push_back(angle);
		}
		mat = new CartoonMaterial(g, i);
	} else if (type.compare("null") == 0) {
		mat = NULL;
	} else { return false; }

	o = std::shared_ptr<Sphere> (new Sphere(c, r, mat));
	return true;
}

bool Input::readObj(std::istringstream &reader, std::shared_ptr<Object> &o) {
	std::string field; reader >> field >> field;
	if(field.compare("SPHERE") == 0) {
		return readSphere(reader, o);
	}
	// TODO other objs
	return false;
}

bool Input::readLight(std::istringstream &reader, std::shared_ptr<Light> &light) {
	std::string field; reader >> field >> field;
	if(field.compare("DIRETIONAL") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "dir")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<DiretionalLight> (new DiretionalLight(d.norm(), i));

		return true;
	} else if(field.compare("SPOT") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;
		if(!readVec3(reader, i)) return false;

		if(!checkFieldName(reader, "origin")) return false;
		Vec3 d;
		if(!readVec3(reader, d)) return false;

		light = std::shared_ptr<PointLight> (new PointLight(i, d));

		return true;
	} else if(field.compare("AMBIENT") == 0) {
		if(!checkFieldName(reader, "i")) return false;
		Vec3 i;		
		if(!readVec3(reader, i)) return false;
		light = std::shared_ptr<AmbientLight> (new AmbientLight(i));
		return true;
	}
	// TODO other objs
	return false;
}

bool Input::readCamera(std::istringstream &reader, Camera &cam) {
	if(!checkFieldName(reader, "CAMERA")) return false;
	std::string field; reader >> field;
	if(field.compare("PERSPECTIVE") == 0) {
		std::string camFields[] = {"ORIGIN", "LLC", "H", "V"};
		Vec3 camValues[4];
		for(int i = 0; i < 4; i++) {
			if(!checkFieldName(reader, camFields[i])) return false;
			readVec3(reader, camValues[i]);
		}
		cam = Camera(camValues[0], camValues[1], camValues[2], camValues[3]);
	} else {
		// TODO others cameras
		return false;
	}
	return true;
}

bool Input::readObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs) {
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

bool Input::readLights(std::istringstream &reader, std::vector<std::shared_ptr<Light> > &lights) {
	std::string begin; reader >> begin;
	if(begin.compare("begin_lights") != 0) return false;
	while(true) {
		reader >> begin;

		if(begin.compare("end_lights") == 0) break;
		if(begin.compare("LIGHT") != 0) break;

		std::shared_ptr<Light> light;
		if(readLight(reader, light)) {
			lights.push_back(light);
		} else return false;
	}
	return true;
}

//---------------------------------------------------------------------------
// parses
bool Input::parseHeader(std::istringstream &reader, Package *p) {
	std::string field;

	if(!checkFieldName(reader, "FILENAME")) return false;
	reader >> p->outputfile;

	if(!checkFieldName(reader, "FILETYPE")) return false;
	reader >> p->type;

	if(!checkFieldName(reader, "WIDTH")) return false;
	reader >> p->cols;

	if(!checkFieldName(reader, "HEIGHT")) return false;
	reader >> p->rows;

	if(!checkFieldName(reader, "SAMPLES")) return false;
	reader >> p->samples;

	if(!checkFieldName(reader, "REC_DEPTH")) return false;
	reader >> p->rec;

	return true;
}

bool Input::parseScene(std::istringstream &reader, Package *p) {
	// Background Colors
	std::string colorFields[] = {"TL", "TR", "BL", "BR"};
	Color colors[4];
	for(int i = 0; i < 4; i++) {
		if(!checkFieldName(reader, colorFields[i])) return false;
		readVec3(reader, colors[i]);
	}

	// Camera
	Camera cam;
	if(!readCamera(reader, cam)) return false;

	// Obj list
	std::vector<std::shared_ptr<Object> > objs;
	if(!readObjList(reader, objs)) return false;

	std::vector<std::shared_ptr<Light> > lights;
	if(!readLights(reader, lights)) return false;
	std::shared_ptr<AmbientLight> ambient = std::dynamic_pointer_cast<AmbientLight>(lights.back());
	
	lights.pop_back();

	p->scene = Scene(cam, objs, colors[0], colors[1], colors[2], colors[3], lights, ambient);
	return true;
}

bool Input::parseShader(std::istringstream &reader, Package *p) {
	if(!checkFieldName(reader, "SHADER")) return false;

	std::string shaderName;
	reader >> shaderName;

	Shader *shader;
	if(shaderName.compare("BLINN_PHONG") == 0) {
		shader = new BlinnPhongShader();
	//} else if(shaderName.compare("DIFFUSE") == 0) {
	//	shader = new DiffuseShader();
	} else if(shaderName.compare("DEPTH") == 0) {
		shader = new DepthShader(4.0, Color(0, 0, 0), Color(1, 1, 1));
		// TODO
	} else if(shaderName.compare("NORMAL_RGB") == 0) {
		shader = new NormalRGBShader();
	} else if(shaderName.compare("RECURSIVE") == 0) {
		shader = new RecursiveShader(p->rec);
	} else if(shaderName.compare("CARTOON") == 0) {
		shader = new CartoonShader();
	} else {
		return false;
	}
	p->r = new Render(p->cols, p->rows, p->samples, shader);
	return true;
}

Package* Input::readInput(std::string filename) {
	std::ifstream reader(filename.c_str(), std::ifstream::in);
	std::string contentInput = Preprocess::readInput(reader);

	std::istringstream content(contentInput);
	Package *p = new Package();
	std::cout << "bbbb";
	if(!parseHeader(content, p)) { std::cout << "Header incorrect" << std::endl; return NULL; }
	if(!parseScene(content, p)) { std::cout << "Scene incorrect" << std::endl; return NULL; }
	if(!parseShader(content, p)) { std::cout << "Shader incorrect" << std::endl; return NULL; }
	std::cout << "aaaa";
	return p;
}
