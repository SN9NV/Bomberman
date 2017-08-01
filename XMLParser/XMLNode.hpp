#ifndef NEW_XMLNODE_HPP
#define NEW_XMLNODE_HPP

#include <string>
#include <map>
#include <vector>

class XMLNode {
public:
	explicit XMLNode(const std::string &name);
	~XMLNode() = default;

	void		addAttribute(const std::string &attr, const std::string &value);
	void		addChild(const XMLNode &child);
	void		setData(const std::string &data);

	std::string				&getName() const;
	std::string				&getData() const;
	std::string				getAttribute(const std::string &attr) const;
	XMLNode					getChild(const std::string &childName) const;
	XMLNode					getChildWithAttribute(const std::string &childName, const std::string &attr, const std::string &value) const;
	std::vector<XMLNode>	getChildren(const std::string &name) const;

private:
	std::string		_name;
	std::string		_data;
	std::map<std::string, std::string>			_attributes;
	std::map<std::string, std::vector<XMLNode>>	_childNodes;
};


#endif //NEW_XMLNODE_HPP
