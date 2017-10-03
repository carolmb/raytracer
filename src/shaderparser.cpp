#include "parsers/shaderparser.h"

#include <string>
#include "shaders/normalrgbshader.h"
#include "shaders/depthshader.h"
#include "shaders/recursiveshader.h"
#include "shaders/blinnphongshader.h"
#include "shaders/cartoonshader.h"

bool ShaderParser::getShader(std::istringstream &reader, Package *p) {
	if(!checkFieldName(reader, "SHADER")) return false;

	std::string shaderName;
	reader >> shaderName;

	Shader *shader;
	if(shaderName.compare("BLINN_PHONG") == 0) {
		shader = new BlinnPhongShader();
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