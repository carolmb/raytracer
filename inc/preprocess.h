#ifndef __PREPROCESS__
#define __PREPROCESS__

#include <string>
#include <fstream>
#include <iostream>

class Preprocess {
public:
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
};

#endif