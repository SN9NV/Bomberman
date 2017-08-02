#include "XMLNode.hpp"

XMLNode::XMLNode(const std::string &name) :
	_name(name)
{

}

void XMLNode::addAttribute(const std::string &attr, const std::string &value) {
	this->_attributes[attr] = value;
}

void XMLNode::addChild(const XMLNode &child) {
	auto list = this->_childNodes.find(child.getName());

	if (list == this->_childNodes.end()) {
		std::vector<XMLNode>	newList = { child };

		this->_childNodes[child.getName()] = newList;
	} else {
		list->second.push_back(child);
	}
}

void XMLNode::setData(const std::string &data) {
	this->_data = data;
}

std::string &XMLNode::getName() const {
	return this->_name;
}

std::string &XMLNode::getData() const {
	return this->_data;
}

std::string XMLNode::getAttribute(const std::string &attr) const {
	auto attribute = this->_attributes.find(attr);

	if (attribute != this->_attributes.end()) {
		return attribute->second;
	}

	return nullptr;
}

XMLNode XMLNode::getChild(const std::string &childName) const {
	auto child = this->_childNodes.find(childName);

	if (child != this->_childNodes.end() && !child->second.empty()) {
		return child->second[0];
	}

	return nullptr;
}

XMLNode XMLNode::getChildWithAttribute(const std::string &childName, const std::string &attr, const std::string &value) const {
	for (auto &child : this->getChildren(childName)) {
		std::string childValue = child.getAttribute(attr);

		if (childValue == value) {
			return child;
		}
	}

	return nullptr;
}

std::vector<XMLNode> XMLNode::getChildren(const std::string &name) const {
	auto children = this->_childNodes.find(name);

	if (children != this->_childNodes.end()) {
		return children->second;
	}

	return std::vector<XMLNode>();
}
