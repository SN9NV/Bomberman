#include "XMLParser.hpp"

#include <fstream>
#include <sstream>
#include <string>

static XMLNode		loadNode(std::ifstream file);
static void			addData(const std::string &line, XMLNode &node);
static void			addAttributes(const std::vector<std::string> &titleParts, XMLNode &node);
static void			addAttribute(const std::string &attributeLine, XMLNode &node);
static std::string	getStartTag(const std::string &line);
static void			trim(std::string &str);
static bool			startsWith(const std::string &str, const std::string &match);

namespace XMLParser {
	constexpr std::regex	DATA = std::regex(">(.+?)<");
	constexpr std::regex	START_TAG = std::regex("<(.+?)>");
	constexpr std::regex	ATTR_NAME = std::regex("(.+?)=");
	constexpr std::regex	ATTR_VALUE = std::regex("\"(.+?)\"");
	constexpr std::regex	CLOSED = std::regex("(</|/>)");



}

XMLNode		loadNode(std::ifstream file) {
	std::string line;

	std::getline(file, line);
	trim(line);

	if (startsWith(line, "</")) {
		return nullptr;
	}

	std::vector<std::string>	startTagParts = getStartTag(line).sep
}

// trim from both ends (in place)
void trim(std::string &str) {

}

bool startsWith(const std::string &str, const std::string &match) {
	return (std::strncmp(str.c_str(), match.c_str(), match.size()) == 0);
}