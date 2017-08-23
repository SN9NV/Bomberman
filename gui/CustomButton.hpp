//
// Created by Owen Exall on 2017/08/17.
//

#ifndef BOMBERMAN_CUSTOMBUTTON_HPP
#define BOMBERMAN_CUSTOMBUTTON_HPP

#include <nanogui/button.h>
#include <functional>

namespace cge {
	namespace GUI {
		namespace Custom {
			class CustomButton : public nanogui::Button {
			public:
				CustomButton(nanogui::Widget *parent, const std::string &text = "Untitled", int icon = 0);
				CustomButton(CustomButton & cpy);
				CustomButton operator=(const CustomButton & rhs);
				~CustomButton() override;

				void setMouseEnterCallback(const std::function<void()> &callback);
			private:
				CustomButton();

				bool mouseEnterEvent(const nanogui::Vector2i &p, bool enter) override ;

				std::function<void()> mMouseEnterCallback;
			};
		}
	}
}

#endif //BOMBERMAN_CUSTOMBUTTON_HPP
