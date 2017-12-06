#ifndef OBJPARSER__
#define OBJPARSER__

#include "parsers/parser.h"
#include "objs/object.h"

#include <sstream>
#include <memory>
#include <vector>
#include <string>
#include <map>

class ObjectParser : public Parser {
public:
	bool getObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);
private:
	bool readMesh(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &meshList);
	bool readObj(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);
	bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readTriangle(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readPlane(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readBox(std::istringstream &reader, std::shared_ptr<Object> &o);
	Transformation* readTransformations(std::istringstream &reader);
	bool readTransf(std::istringstream &reader, Mat4 &m, std::string transfName);
	Point3 getVerticeInMesh(objl::Mesh curMesh, int index); 
};

#endif
