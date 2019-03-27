// TextParser.hpp

#ifndef FILE_TEXTPARSER_HPP_INCLUDED
#define FILE_TEXTPARSER_HPP_INCLUDED

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class TextParser {
public:
	TextParser(const std::string & path);
	const std::vector<std::string> & getLine(int index) const;
	int size() const;

	static std::string getResourceName(std::string path);
	static int parseInt(const std::string & token);
	static float parseFloat(const std::string & token);

private:
	std::string _name;
	std::vector< std::vector<std::string> > _data;
};

#endif // #ifndef FILE_TEXTPARSER_HPP_INCLUDED