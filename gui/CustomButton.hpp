//
// Created by Owen Exall on 2017/08/17.
//

#ifndef BOMBERMAN_CUSTOMBUTTON_HPP
#define BOMBERMAN_CUSTOMBUTTON_HPP

#include <nanogui/button.h>

namespace cge {
	namespace GUI {
		namespace Custom {
			class CustomButton : public nanogui::Button {
			public:
				explicit CustomButton(nanogui::Widget *parent, const std::string &text = "Untitled", int icon = 0);

				~CustomButton() override;

			private:
				bool mouseEnterEvent(const nanogui::Vector2i &p, bool enter) override ;
			};
		}
	}
}

#endif //BOMBERMAN_CUSTOMBUTTON_HPP
