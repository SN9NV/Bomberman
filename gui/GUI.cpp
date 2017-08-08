//
// Created by owen on 2017/07/29.
//

#include "GUI.hpp"

CEGUI::OpenGL3Renderer* cge::GUI::_ceguiRenderer = nullptr;

void cge::GUI::init(const std::string& resourceDirectory) {
	//check if the renderer and system were already initialized.
	if (_ceguiRenderer == nullptr) {
		_ceguiRenderer = &CEGUI::OpenGL3Renderer::bootstrapSystem();

		//setting all the resource directories. resourceDirectory = "/GUI/datafiles"
		CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());
		rp->setResourceGroupDirectory("imagesets", resourceDirectory + "/imagesets/");
		rp->setResourceGroupDirectory("schemes", resourceDirectory + "/schemes/");
		rp->setResourceGroupDirectory("fonts", resourceDirectory + "/fonts/");
		rp->setResourceGroupDirectory("layouts", resourceDirectory + "/layouts/");
		rp->setResourceGroupDirectory("looknfeel", resourceDirectory + "/looknfeel/");
		rp->setResourceGroupDirectory("lua_scripts", resourceDirectory + "/lua_scripts/");

		//tell CEGUI to use the resources.
		CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
		CEGUI::Scheme::setDefaultResourceGroup("schemes");
		CEGUI::Font::setDefaultResourceGroup("fonts");
		CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeel");
		CEGUI::WindowManager::setDefaultResourceGroup("layouts");
		CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");
	}

	this->_context = &CEGUI::System::getSingleton().createGUIContext(_ceguiRenderer->getDefaultRenderTarget());
	this->_root = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
	this->_context->setRootWindow(_root);
	this->_showCursor = true;
	this->_lastTime = 0;
	this->_messageBox = nullptr;
}

void cge::GUI::destroy() {
	CEGUI::System::getSingleton().destroyGUIContext(*_context);
}

CEGUI::OpenGL3Renderer *cge::GUI::getRenderer() {
	return (_ceguiRenderer);
}

const CEGUI::GUIContext *cge::GUI::getContext() {
	return (_context);
}

void cge::GUI::draw() {
	this->_ceguiRenderer->beginRendering();
	this->_context->draw();
	this->_ceguiRenderer->endRendering();

	glDisable(GL_SCISSOR_TEST);
}

void cge::GUI::loadScheme(const std::string &schemeFile) {
	CEGUI::SchemeManager::getSingleton().createFromFile(schemeFile);
}

void cge::GUI::setWidgetDestRect(CEGUI::Window *widget, const glm::vec4 &destRectPerc, const glm::vec4 &destRectPix) {
	widget->setPosition(
			CEGUI::UVector2(
					CEGUI::UDim(destRectPerc.x, destRectPix.x),
					CEGUI::UDim(destRectPerc.y, destRectPix.y))
	);
	widget->setSize(
			CEGUI::USize(
					CEGUI::UDim(destRectPerc.z, destRectPix.z),
					CEGUI::UDim(destRectPerc.w, destRectPix.w))
	);
}

void cge::GUI::setFont(const std::string& fontFile) {
	CEGUI::FontManager::getSingleton().createFromFile(fontFile + ".font");
	this->_context->setDefaultFont(fontFile);
}

void cge::GUI::setMouseCursor(const std::string &imageFile) {
	this->_context->getMouseCursor().setDefaultImage(imageFile);
}

void cge::GUI::toggleShowMouseCursor() {
	this->_showCursor = !this->_showCursor;
	if (this->_showCursor)
		this->_context->getMouseCursor().show();
	else
		this->_context->getMouseCursor().hide();
}

CEGUI::Key::Scan SDLKeyToCEGUIKey(SDL_Keycode key)
{
	using namespace CEGUI;
	switch (key)
	{
		case SDLK_BACKSPACE:    return Key::Backspace;
		case SDLK_TAB:          return Key::Tab;
		case SDLK_RETURN:       return Key::Return;
		case SDLK_PAUSE:        return Key::Pause;
		case SDLK_ESCAPE:       return Key::Escape;
		case SDLK_SPACE:        return Key::Space;
		case SDLK_COMMA:        return Key::Comma;
		case SDLK_MINUS:        return Key::Minus;
		case SDLK_PERIOD:       return Key::Period;
		case SDLK_SLASH:        return Key::Slash;
		case SDLK_0:            return Key::Zero;
		case SDLK_1:            return Key::One;
		case SDLK_2:            return Key::Two;
		case SDLK_3:            return Key::Three;
		case SDLK_4:            return Key::Four;
		case SDLK_5:            return Key::Five;
		case SDLK_6:            return Key::Six;
		case SDLK_7:            return Key::Seven;
		case SDLK_8:            return Key::Eight;
		case SDLK_9:            return Key::Nine;
		case SDLK_COLON:        return Key::Colon;
		case SDLK_SEMICOLON:    return Key::Semicolon;
		case SDLK_EQUALS:       return Key::Equals;
		case SDLK_LEFTBRACKET:  return Key::LeftBracket;
		case SDLK_BACKSLASH:    return Key::Backslash;
		case SDLK_RIGHTBRACKET: return Key::RightBracket;
		case SDLK_a:            return Key::A;
		case SDLK_b:            return Key::B;
		case SDLK_c:            return Key::C;
		case SDLK_d:            return Key::D;
		case SDLK_e:            return Key::E;
		case SDLK_f:            return Key::F;
		case SDLK_g:            return Key::G;
		case SDLK_h:            return Key::H;
		case SDLK_i:            return Key::I;
		case SDLK_j:            return Key::J;
		case SDLK_k:            return Key::K;
		case SDLK_l:            return Key::L;
		case SDLK_m:            return Key::M;
		case SDLK_n:            return Key::N;
		case SDLK_o:            return Key::O;
		case SDLK_p:            return Key::P;
		case SDLK_q:            return Key::Q;
		case SDLK_r:            return Key::R;
		case SDLK_s:            return Key::S;
		case SDLK_t:            return Key::T;
		case SDLK_u:            return Key::U;
		case SDLK_v:            return Key::V;
		case SDLK_w:            return Key::W;
		case SDLK_x:            return Key::X;
		case SDLK_y:            return Key::Y;
		case SDLK_z:            return Key::Z;
		case SDLK_DELETE:       return Key::Delete;
		/*case SDLK_KP0:          return Key::Numpad0;
		case SDLK_KP1:          return Key::Numpad1;
		case SDLK_KP2:          return Key::Numpad2;
		case SDLK_KP3:          return Key::Numpad3;
		case SDLK_KP4:          return Key::Numpad4;
		case SDLK_KP5:          return Key::Numpad5;
		case SDLK_KP6:          return Key::Numpad6;
		case SDLK_KP7:          return Key::Numpad7;
		case SDLK_KP8:          return Key::Numpad8;
		case SDLK_KP9:          return Key::Numpad9;*/
		case SDLK_KP_PERIOD:    return Key::Decimal;
		case SDLK_KP_DIVIDE:    return Key::Divide;
		case SDLK_KP_MULTIPLY:  return Key::Multiply;
		case SDLK_KP_MINUS:     return Key::Subtract;
		case SDLK_KP_PLUS:      return Key::Add;
		case SDLK_KP_ENTER:     return Key::NumpadEnter;
		case SDLK_KP_EQUALS:    return Key::NumpadEquals;
		case SDLK_UP:           return Key::ArrowUp;
		case SDLK_DOWN:         return Key::ArrowDown;
		case SDLK_RIGHT:        return Key::ArrowRight;
		case SDLK_LEFT:         return Key::ArrowLeft;
		case SDLK_INSERT:       return Key::Insert;
		case SDLK_HOME:         return Key::Home;
		case SDLK_END:          return Key::End;
		case SDLK_PAGEUP:       return Key::PageUp;
		case SDLK_PAGEDOWN:     return Key::PageDown;
		case SDLK_F1:           return Key::F1;
		case SDLK_F2:           return Key::F2;
		case SDLK_F3:           return Key::F3;
		case SDLK_F4:           return Key::F4;
		case SDLK_F5:           return Key::F5;
		case SDLK_F6:           return Key::F6;
		case SDLK_F7:           return Key::F7;
		case SDLK_F8:           return Key::F8;
		case SDLK_F9:           return Key::F9;
		case SDLK_F10:          return Key::F10;
		case SDLK_F11:          return Key::F11;
		case SDLK_F12:          return Key::F12;
		case SDLK_F13:          return Key::F13;
		case SDLK_F14:          return Key::F14;
		case SDLK_F15:          return Key::F15;
		/*case SDLK_NUMLOCK:      return Key::NumLock;
		case SDLK_SCROLLOCK:    return Key::ScrollLock;*/
		case SDLK_RSHIFT:       return Key::RightShift;
		case SDLK_LSHIFT:       return Key::LeftShift;
		case SDLK_RCTRL:        return Key::RightControl;
		case SDLK_LCTRL:        return Key::LeftControl;
		case SDLK_RALT:         return Key::RightAlt;
		case SDLK_LALT:         return Key::LeftAlt;
		/*case SDLK_LSUPER:       return Key::LeftWindows;
		case SDLK_RSUPER:       return Key::RightWindows;*/
		case SDLK_SYSREQ:       return Key::SysRq;
		case SDLK_MENU:         return Key::AppMenu;
		case SDLK_POWER:        return Key::Power;
		default:                return Key::Unknown;
	}
}

CEGUI::MouseButton SDLMouseButtonToCEGUIMouseButton(Uint8 sdlButton)
{
	switch (sdlButton) {
		case SDL_BUTTON_LEFT:	return CEGUI::MouseButton::LeftButton;
		case SDL_BUTTON_MIDDLE:	return CEGUI::MouseButton::MiddleButton;
		case SDL_BUTTON_RIGHT:	return CEGUI::MouseButton::RightButton;
		case SDL_BUTTON_X1:		return CEGUI::MouseButton::X1Button;
		case SDL_BUTTON_X2:		return CEGUI::MouseButton::X2Button;
		default:				return CEGUI::MouseButton::NoButton;
	}
}

void cge::GUI::onSDLEvent(SDL_Event &event) {
	CEGUI::utf32 codePoint;

	switch (event.type)
	{
		case SDL_MOUSEMOTION:
			this->_context->injectMousePosition(event.motion.x, event.motion.y);
			break;
		case SDL_KEYDOWN:
			this->_context->injectKeyDown(SDLKeyToCEGUIKey(event.key.keysym.sym));
			break;
		case SDL_KEYUP:
			this->_context->injectKeyUp(SDLKeyToCEGUIKey(event.key.keysym.sym));
			break;
		case SDL_TEXTINPUT:
			codePoint = 0;
			for(int i = 0; event.text.text[i] != '\0'; i++) {
				codePoint |= (((CEGUI::utf32)*(unsigned int*)&event.text.text[i]) << (i * 8));
			}
			this->_context->injectChar(codePoint);
			break;
		case SDL_MOUSEBUTTONDOWN:
			this->_context->injectMouseButtonDown(SDLMouseButtonToCEGUIMouseButton(event.button.button));
			break;
		case SDL_MOUSEBUTTONUP:
			this->_context->injectMouseButtonUp(SDLMouseButtonToCEGUIMouseButton(event.button.button));
			break;
		default:
			break;
	}
}

void cge::GUI::update() {
	unsigned int elapsed;
	if (this->_lastTime == 0) {
		elapsed = 0;
		this->_lastTime = SDL_GetTicks();
	} else {
		unsigned int nextTime = SDL_GetTicks();
		elapsed = nextTime - this->_lastTime;
		this->_lastTime = nextTime;
	}
	this->_context->injectTimePulse((float)elapsed / 1000.0f);
}

void cge::GUI::loadLayout(const std::string layoutFile) {
	CEGUI::Window *layoutWindow = CEGUI::WindowManager::getSingleton().loadLayoutFromFile(layoutFile);
	this->_context->setRootWindow(layoutWindow);
}

void cge::GUI::_initMessageBox() {
	if (this->_messageBox == nullptr) {
		this->_messageBox = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/FrameWindow", "fw_MessageBox"));
		this->_context->getRootWindow()->addChild(this->_messageBox);
		this->setWidgetDestRect(this->_messageBox, glm::vec4(0.33f, 0.4f, 0.33f, 0.2f), glm::vec4(0.0f));
		this->_messageBox->getCloseButton()->subscribeEvent(CEGUI::PushButton::EventClicked,
				CEGUI::Event::Subscriber(&GUI::mb_Message_ClosedClicked, this));
		CEGUI::Window* label = CEGUI::WindowManager::getSingleton().createWindow("AlfiskoSkin/Label", "lbl_Message");
		this->_messageBox->addChild(label);
		this->setWidgetDestRect(label, glm::vec4(0.01f, 0.01f, 0.99f, 0.99f), glm::vec4(0.0f));
		this->_messageBox->setVisible(false);
	}
}

void cge::GUI::showMessageBox(const std::string Message) {
	this->_initMessageBox();
	this->_messageBox->getChild("lbl_Message")->setText(Message);
	this->_messageBox->moveToFront();
	this->_messageBox->setVisible(true);
	this->_messageBox->setModalState(true);
}

void cge::GUI::showMessageBox(const std::string Message, const std::string title) {
	this->_initMessageBox();
	this->_messageBox->getTitlebar()->setText(title);
	this->_messageBox->getChild("lbl_Message")->setText(Message);
	this->_messageBox->moveToFront();
	this->_messageBox->setVisible(true);
	this->_messageBox->setModalState(true);
}

bool cge::GUI::mb_Message_ClosedClicked(const CEGUI::EventArgs &e) {
	(void)e;
	this->_messageBox->setModalState(false);
	this->_messageBox->setVisible(false);
	this->_messageBox->moveToBack();
	return (true);
}






