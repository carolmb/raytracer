#ifndef OBJPARSER__
#define OBJPARSER__

#include "parser.h"
#include "object.h"

#include <sstream>
#include <memory>
#include <vector>

class ObjectParser : public Parser {
public:
	bool getObjList(std::istringstream &reader, std::vector<std::shared_ptr<Object> > &objs);
private:
	bool readObj(std::istringstream &reader, std::shared_ptr<Object> &o);
	bool readSphere(std::istringstream &reader, std::shared_ptr<Object> &o);
};

#endif