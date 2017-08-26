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

	static bool readColor(std::istringstream &file, Color &a) {
	 	double r, g, b;
	 	file >> r >> g >> b;
		bool valid = r >= 0 && r <= 1 && g >= 0 && g <= 1 && b >= 0 && b <= 1;
		if (valid) {
			a.x = r; a.y = g; a.z = b;
		}
		return valid;
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

public:
	static Package* readInput(std::string filename) {
		std::cout << filename << std::endl;
		std::ifstream reader(filename.c_str(), std::ifstream::in);
		std::string contentInput = readInput(reader);
		
		std::istringstream content(contentInput);
		Package *p = new Package();
		if(!parseHeader(content, p)) return NULL;
		
		p->scene = Scene();
		std::cout << p->rows << " " << p->cols << std::endl;
		p->render = new DepthRender(p->cols, p->rows, Color(0, 0, 0), Color(1, 1, 1), 4.0);
		
		return p;
	}

};

#endif