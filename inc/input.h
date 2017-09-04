#ifndef __INPUT__
#define __INPUT__

#include <string>
#include <fstream>
#include <iostream>

#include "package.h"
#include "preprocess.h"
#include "scene.h"
#include "render.h"
#include "shaders/shader.h"
#include "shaders/normalrgbshader.h"
#include "shaders/depthshader.h"
#include "shaders/diffuseshader.h"
#include "shaders/diffusenolightshader.h"
#include "shaders/blinnphongshader.h"

class Input {
	static bool checkFieldName(std::istringstream &reader, std::string field) {
		std::string f;
		reader >> f;
		if(field.compare(f) != 0) return false;
		reader >> f;
		if(f.compare("=") != 0) return false;
		return true;
	}	

	static bool readVec3(std::istringstream &reader, Vec3 &a) {
	 	std::string r, g, b;
	 	reader >> r >> g >> b;
	 	a.x = std::stod (r);
	 	a.y = std::stod (g);
	 	a.z = std::stod (b);
	 	std::cout << a.x << " " << a.y << " " << a.z << std::endl;
 	 	return true;
	}

	static bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o) {
		if(!checkFieldName(reader, "CENTER")) return false;
		Vec3 c; readVec3(reader, c);

		if(!checkFieldName(reader, "RADIUS")) return false;
		double r; reader >> r;
		
		if(!checkFieldName(reader, "ka")) return false;
		Vec3 ka; readVec3(reader, ka);

		if(!checkFieldName(reader, "kd")) return false;
		Vec3 kd; readVec3(reader, kd);

		if(!checkFieldName(reader, "ks")) return false;
		Vec3 ks; readVec3(reader, ks);

		if(!checkFieldName(reader, "exps")) return false;
		double exps; reader >> exps;
		
		Material mat(ka, kd, ks, exps);
		o = std::shared_ptr<Sphere> (new Sphere(c, r, mat));
		return true;
	}

	static bool readObj(std::istringstream &reader, std::shared_ptr<Object> &o) {
		std::string field; reader >> field >> field;
		if(field.compare("SPHERE") == 0) {
			return readSphere(reader, o);
		}
		// TODO other objs
		return false;
	}
	
	static bool readLight(std::istringstream &reader, Vec3 &light) {
		std::string field; reader >> field >> field;
		if(field.compare("DIRETIONAL") == 0) {
			if(!checkFieldName(reader, "i")) return false;
			if(!readVec3(reader, light)) return false;

			if(!checkFieldName(reader, "dir")) return false;
			if(!readVec3(reader, light)) return false;
			
			return true;
		} else if(field.compare("AMBIENT") == 0) {
			if(!checkFieldName(reader, "i")) return false;
			return readVec3(reader, light);
		}
		// TODO other objs
		return false;
	}

	static bool readCamera(std::istringstream &reader, Camera &cam) {
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

	static bool readObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs) {
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

	static bool readLights(std::istringstream &reader, std::vector<Vec3> &lights) {
		std::string begin; reader >> begin;
		if(begin.compare("begin_lights") != 0) return false;
		while(true) {
			reader >> begin;
			
			if(begin.compare("end_lights") == 0) break;
			if(begin.compare("LIGHT") != 0) break;

			Vec3 light;
			if(readLight(reader, light)) {
				lights.push_back(light);
			} else return false;
		}
		return true;
	}

	//---------------------------------------------------------------------------
	// parses
	static bool parseHeader(std::istringstream &reader, Package *p) {
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

	static bool parseScene(std::istringstream &reader, Package *p) {
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

		std::vector<Vec3> lights;
		if(!readLights(reader, lights)) return false;

		p->scene = Scene(cam, objs, colors[0], colors[1], colors[2], colors[3], lights[0]);
		return true;
	}

	static bool parseShader(std::istringstream &reader, Package *p) {
		if(!checkFieldName(reader, "SHADER")) return false;
		
		std::string shaderName; 
		reader >> shaderName;

		Shader *shader;
		if(shaderName.compare("BLINN_PHONG") == 0) {
			shader = new BlinnPhongShader();
		} else if(shaderName.compare("DIFFUSE") == 0) {
			shader = new DiffuseShader();
		} else if(shaderName.compare("DEPTH") == 0) {
			shader = new DepthShader(4.0, Color(0, 0, 0), Color(1, 1, 1));
			// TODO
		} else if(shaderName.compare("NORMAL_RBG") == 0) {
			shader = new NormalRGBShader();
		} else if(shaderName.compare("DIFFUSE_NOLIGHT") == 0) {
			shader = new DiffuseNoLightShader(p->rec);
		} else {
			return false;
		}
		p->r = new Render(p->cols, p->rows, p->samples, shader);
		return true;
	}

public:
	static Package* readInput(std::string filename) {
		std::ifstream reader(filename.c_str(), std::ifstream::in);
		std::string contentInput = Preprocess::readInput(reader);
		
		std::istringstream content(contentInput);
		Package *p = new Package();
		if(!parseHeader(content, p)) return NULL;
		if(!parseScene(content, p)) return NULL;
		
		if(!parseShader(content, p)) return NULL;
		
		return p;
	}

};

#endif
