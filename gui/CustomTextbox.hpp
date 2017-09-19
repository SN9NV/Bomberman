//
// Created by owen on 2017/08/25.
//

#ifndef BOMBERMAN_CUSTOMTEXTBOX_HPP
#define BOMBERMAN_CUSTOMTEXTBOX_HPP

#include <nanogui/textbox.h>

namespace cge {
	namespace GUI {
		namespace Custom {
			class CustomTextbox : public nanogui::TextBox {
			public:
				CustomTextbox() = delete;
				CustomTextbox(Custom::CustomTextbox& cpy);
				CustomTextbox &operator=(const CustomTextbox &rhs) = default;
				explicit CustomTextbox(nanogui::Widget* parent, const std::string& caption = "Untitled");
				~CustomTextbox();

				void setTextChangedCallback(std::function<bool(int result)> textChangedCallback);
			private:
				std::function<bool(int result)> _textChangedCallback;

				bool keyboardEvent(int key, int scancode, int action, int modifiers) override;
				bool keyboardCharacterEvent(unsigned int codepoint) override;
			};
		}
	}
}


#endif //BOMBERMAN_CUSTOMTEXTBOX_HPP
