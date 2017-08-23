//
// Created by Owen Exall on 2017/08/17.
//

#include "CustomButton.hpp"

cge::GUI::Custom::CustomButton::CustomButton(nanogui::Widget *parent, const std::string &text, int icon) :
		nanogui::Button(parent, text, icon) {
	this->mMouseEnterCallback = nullptr;
}

cge::GUI::Custom::CustomButton::~CustomButton() {
}

bool cge::GUI::Custom::CustomButton::mouseEnterEvent(const nanogui::Vector2i &p, bool enter) {
	nanogui::Widget::mouseEnterEvent(p, enter);
	if (enter && this->mMouseEnterCallback) {
		this->mMouseEnterCallback();
	}
	return (false);
}

void cge::GUI::Custom::CustomButton::setMouseEnterCallback(const std::function<void()> &callback) {
	this->mMouseEnterCallback = callback;
}

cge::GUI::Custom::CustomButton::CustomButton(cge::GUI::Custom::CustomButton &cpy) :
		nanogui::Button(cpy.parent(), cpy.caption(), cpy.icon()) {
	this->mMouseEnterCallback = cpy.mMouseEnterCallback;
}

cge::GUI::Custom::CustomButton cge::GUI::Custom::CustomButton::operator=(const cge::GUI::Custom::CustomButton &rhs) {
	*this = rhs;
	return (*this);
}
