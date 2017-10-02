#include "parsers/headerparser.h"

bool HeaderParser::getHeader(std::istringstream &reader, Package *p) {
	std::string field;

	if(!checkFieldName(reader, "FILENAME")) return false;
	reader >> p->outputfile;

	if(!checkFieldName(reader, "FILETYPE")) return false;
	reader >> p->type;

	if(!checkFieldName(reader, "WIDTH")) return false;
	reader >> p->cols;

	if(!checkFieldName(reader, "HEIGHT")) return false;
	reader >> p->rows;

	if(!checkFieldName(reader, "SAMPLES")) return false;
	reader >> p->samples;

	if(!checkFieldName(reader, "REC_DEPTH")) return false;
	reader >> p->rec;

	return true;
}