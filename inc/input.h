#ifndef __INPUT__
#define __INPUT__

#include <string>
#include <fstream>
#include <iostream>

#include "scene.h"
#include "render.h"

struct Package {
	int cols;
	int rows;
	std::string outputfile;
	std::string type;
	Scene scene;
	Render *render;
};

class Input {

	static void readVec3(std::istringstream &file, Vec3 &a) {
	 	double r, g, b;
	 	file >> r >> g >> b;
		a.x = r; a.y = g; a.z = b;	
	}

	static bool readSphere(std::istringstream &reader, Object *o) {
		std::string field;
		reader >> field;
		if(field.compare("C") != 0) return false;
		reader >> field;
		if(field.compare("=") != 0) return false;
		Vec3 c;
		readVec3(reader, c);
		
		if(field.compare("R") != 0) return false;
		reader >> field;
		if(field.compare("=") != 0) return false;
		double r;
		reader >> r;
		o = new Sphere(c, r);
	}

	static bool readObj(std::istringstream &file, Object *o) {
		std::string field;
		file >> field;
		if(field.compare("SPHERE") == 0) {
			return readSphere(file, o);
		}
		return false;
	}


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

	static bool parseHeader(std::istringstream &reader, Package *p) {
		std::string field;

		reader >> field;
		if(field.compare("FILENAME") != 0) return false; 
		reader >> field;
		if(field.compare("=") != 0) return false; 
		reader >> p->outputfile;

		reader >> field;
		if(field.compare("FILETYPE") != 0) return false;
		reader >> field;
		if(field.compare("=") != 0) return false; 
		reader >> p->type;

		reader >> field;
		if(field.compare("WIDTH") != 0) return false;
		reader >> field;
		if(field.compare("=") != 0) return false; 
		reader >> p->cols;

		reader >> field;
		if(field.compare("HEIGHT") != 0) return false;
		reader >> field;
		if(field.compare("=") != 0) return false; 
		reader >> p->rows;
		return true;
	}

	static bool parseScene(std::istringstream &reader, Package *p) {
		std::string field;

		// Background Colors
		std::string colorFields[] = {"TL", "TR", "BL", "BR"};
		Color colors[4];
		for(int i = 0; i < 4; i++) {
			reader >> field;
			if(field.compare(colorFields[i]) != 0) return false; 
			reader >> field;
			if(field.compare("=") != 0) return false; 
			readVec3(reader, colors[i]);
		}		

		// Camera
		Camera cam;
		{
			reader >> field;
			if(field.compare("CAMERA") != 0) return false;
			reader >> field;
			if(field.compare("=") != 0) return false; 
			reader >> field;
			if(field.compare("PERSPECTIVE") == 0) {
				std::string camFields[] = {"LLC", "H", "V"};
				Vec3 camValues[3];
				for(int i = 0; i < 3; i++) {
					reader >> field;
					if(field.compare(camFields[i]) != 0) return false;
					reader >> field;
					if(field.compare("=") != 0) return false; 
					readVec3(reader, camValues[i]);
				}
				cam = Camera(camValues[0], camValues[1], camValues[2]);
			} else {
				std::cout << "bla" << std::endl;
				return false;
			}
		}

		std::vector<Object*> objs; 
		reader >> field;
		while(field.compare("OBJ") == 0) {
			reader >> field;
			if(field.compare("=") != 0) return false;
			Object *obj;
			readObj(reader, obj);
			objs.push_back(obj);
		}

		p->scene = Scene(cam, objs, colors[0], colors[1], colors[2], colors[3]);
		return true;
	}

public:
	static Package* readInput(std::string filename) {
		std::cout << filename << std::endl;
		std::ifstream reader(filename.c_str(), std::ifstream::in);
		std::string contentInput = readInput(reader);
		
		std::istringstream content(contentInput);
		Package *p = new Package();
		if(!parseHeader(content, p)) return NULL;
		if(!parseScene(content, p)) return NULL;

		p->scene = Scene();
		std::cout << p->rows << " " << p->cols << std::endl;
		p->render = new DepthRender(p->cols, p->rows, Color(0, 0, 0), Color(1, 1, 1), 4.0);
		
		return p;
	}

};

#endif