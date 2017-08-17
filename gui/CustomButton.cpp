//
// Created by Owen Exall on 2017/08/17.
//

#include "CustomButton.hpp"

cge::GUI::Custom::CustomButton::CustomButton(nanogui::Widget *parent, const std::string &text, int icon) :
		nanogui::Button(parent, text, icon) {

}

cge::GUI::Custom::CustomButton::~CustomButton() {

}

bool cge::GUI::Custom::CustomButton::mouseEnterEvent(const nanogui::Vector2i &p, bool enter) {
	nanogui::Widget::mouseEnterEvent(p, enter);
	if (enter) {

	} else {

	}
	return (true);
}
