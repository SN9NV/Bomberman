#ifndef NEW_XMLPARSER_HPP
#define NEW_XMLPARSER_HPP

#include <regex>

#include "XMLNode.hpp"

namespace XMLParser {
	XMLNode	loadXMLFile(const std::string &filePath);
};


#endif //NEW_XMLPARSER_HPP
