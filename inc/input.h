#ifndef __INPUT__
#define __INPUT__

#include <string>
#include <fstream>
#include <iostream>

#include "scene.h"
#include "render.h"
#include "shader.h"
#include "diffusenolightshader.h"


struct Package {
	int cols;
	int rows;
	std::string outputfile;
	std::string type;
	Scene scene;
	Render *r;
};

class Input {
	// preprocess input
	static std::string clearComments(std::string &input) {
		int found = input.find_first_of("#");
		if (found != std::string::npos) {
			input = input.substr(0, found);
		}
		return input;
	}

	static bool isEmpty(std::string input) {
		for(int i = 0; i < input.size(); i++) {
			if (input[i] != ' ')
				return false;
		}
		return true;
	}

	static std::string readInput(std::ifstream &file) {
		std::string input;
		std::string cleanInput = "";
		while(!file.eof()) {
			getline(file, input);
			clearComments(input);
			if (!isEmpty(input)) {
				cleanInput += input + "\n";
			}
		}
		return cleanInput;
	}
	//---------------------------------------------------------------------------
	// auxiliar functions
	static bool checkFieldName(std::istringstream &reader, std::string field) {
		std::string f;
		reader >> f;
		if(field.compare(f) != 0) return false;
		reader >> f;
		if(f.compare("=") != 0) return false;
		return true;
	}	

	static void readVec3(std::istringstream &reader, Vec3 &a) {
	 	double r, g, b;
	 	reader >> r >> g >> b;
		a.x = r; a.y = g; a.z = b;	
	}

	static bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o) {
		if(!checkFieldName(reader, "CENTER")) return false;
		Vec3 c; readVec3(reader, c);

		if(!checkFieldName(reader, "RADIUS")) return false;
		double r; reader >> r;
		
		if(!checkFieldName(reader, "MATTE")) return false;
		Vec3 matt; readVec3(reader, matt);

		//std::cout << matt.x << " " << matt.y << " " << matt.z << std::endl;
		o = std::shared_ptr<Sphere> (new Sphere(c, r, matt));
		return true;
	}

	static bool readObj(std::istringstream &reader, std::shared_ptr<Object> &o) {
		std::string field; reader >> field;
		if(field.compare("SPHERE") == 0) {
			return readSphere(reader, o);
		}
		// TODO other objs
		return false;
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
		{
			if(!checkFieldName(reader, "CAMERA")) return false;
			std::string field; reader >> field;
			if(field.compare("PERSPECTIVE") == 0) {
				std::string camFields[] = {"LLC", "H", "V"};
				Vec3 camValues[3];
				for(int i = 0; i < 3; i++) {
					if(!checkFieldName(reader, camFields[i])) return false; 
					readVec3(reader, camValues[i]);
				}
				cam = Camera(camValues[0], camValues[1], camValues[2]);
			} else { return false; }
		}
		
		// objs in scene
		std::vector<std::shared_ptr<Object> > objs; 
		while(checkFieldName(reader, "OBJ")) {
			std::shared_ptr<Object> obj;
			if(readObj(reader, obj)) {
				objs.push_back(obj);
			} else return false;
		}
		p->scene = Scene(cam, objs, colors[0], colors[1], colors[2], colors[3]);
		return true;
	}

	static bool parseRender(std::istringstream &reader, Package *p) {
		return true;
	}

public:
	static Package* readInput(std::string filename) {
		std::ifstream reader(filename.c_str(), std::ifstream::in);
		std::string contentInput = readInput(reader);
		
		std::istringstream content(contentInput);
		Package *p = new Package();
		if(!parseHeader(content, p)) return NULL;
		if(!parseScene(content, p)) return NULL;

		//Shader *shader = new DepthShader(4.0, Color(0, 0, 0), Color(1, 1, 1));
		Shader *shader = new DiffuseShader(Vec3(2, 10, -0.5));

		p->r = new Render(p->cols, p->rows, 4, shader);
		return p;
	}

};

#endif