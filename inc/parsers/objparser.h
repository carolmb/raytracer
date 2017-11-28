#ifndef OBJPARSER__
#define OBJPARSER__

#include "parsers/parser.h"
#include "objs/object.h"

#include <sstream>
#include <memory>
#include <vector>
#include <string>

class ObjectParser : public Parser {
public:
	bool getObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);
private:
	bool readMash(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &meshList);
	bool readObj(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);
	bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readTriangle(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readPlane(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readBox(std::istringstream &reader, std::shared_ptr<Object> &o);
	Transformation* readTransformations(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readTransformations(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &os); 
	bool readTransf(std::istringstream &reader, Mat4 &m, std::string transfName);
};

#endif