#include "input.h"

#include <sstream>
#include <fstream>
#include <iostream>

#include "preprocess.h"
#include "parsers/headerparser.h"
#include "parsers/sceneparser.h"
#include "parsers/shaderparser.h"

Package* Input::readInput(std::string filename) {
	std::ifstream reader(filename.c_str(), std::ifstream::in);
	std::string contentInput = Preprocess::readInput(reader);

	std::istringstream content(contentInput);
	Package *p = new Package();
	
	HeaderParser headerParser; 
	if(!headerParser.getHeader(content, p)) { 
		std::cout << "Header incorrect" << std::endl; 
		return NULL; 
	}
	
	SceneParser sceneParser;
	if(!sceneParser.getScene(content, p)) { 
		std::cout << "Scene incorrect" << std::endl; 
		return NULL;
	}
	
	ShaderParser shaderParser;
	if(!shaderParser.getShader(content, p)) { 
		std::cout << "Shader incorrect" << std::endl; 
		return NULL; 
	}

	return p;
}
