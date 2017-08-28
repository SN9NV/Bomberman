//
// Created by owen on 2017/08/25.
//

#include "CustomTextbox.hpp"

cge::GUI::Custom::CustomTextbox::CustomTextbox(nanogui::Widget *parent, const std::string &caption)
		: TextBox(parent, caption) {
	_textChangedCallback = nullptr;
}

cge::GUI::Custom::CustomTextbox::~CustomTextbox() {

}

bool cge::GUI::Custom::CustomTextbox::keyboardEvent(int key, int scancode, int action, int modifiers) {
	nanogui::TextBox::keyboardEvent(key, scancode, action, modifiers);
	return (true);
}

bool cge::GUI::Custom::CustomTextbox::keyboardCharacterEvent(unsigned int codepoint) {
	nanogui::TextBox::keyboardCharacterEvent(codepoint);
	if (this->_textChangedCallback)
		return (this->_textChangedCallback(codepoint));
	return (false);
}

void cge::GUI::Custom::CustomTextbox::setTextChangedCallback(
		std::function<bool(int result)> textChangedCallback) {
	this->_textChangedCallback = textChangedCallback;
}

cge::GUI::Custom::CustomTextbox::CustomTextbox(cge::GUI::Custom::CustomTextbox &cpy) :
	nanogui::TextBox(cpy.parent(), cpy.value())
{
	this->_textChangedCallback = cpy._textChangedCallback;
}

cge::GUI::Custom::CustomTextbox cge::GUI::Custom::CustomTextbox::operator=(
		const cge::GUI::Custom::CustomTextbox &rhs) {
	*this = rhs;
	return (*this);
}
