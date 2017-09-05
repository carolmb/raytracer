#ifndef PREPROCESS__
#define PREPROCESS__

#include <string>
#include <fstream>

class Preprocess {
public:
	static std::string clearComments(std::string &input);

	static bool isEmpty(std::string input);

	static std::string readInput(std::ifstream &file);
};

#endif