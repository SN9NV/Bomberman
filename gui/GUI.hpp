//
// Created by owen on 2017/07/29.
//

#pragma once

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <glm/glm.hpp>
#include <SDL_events.h>
#include <SDL_timer.h>
#include <string>

namespace cge {
	class GUI {
	public:
		//todo: copliens form.
		void init(const std::string &resourceDirectory);

		void destroy();

		void draw();

		void update();

		void loadScheme(const std::string &schemeFile);

		void setFont(const std::string &fontFile);

		void setMouseCursor(const std::string &imageFile);

		void toggleShowMouseCursor();

		void onSDLEvent(SDL_Event &event);

		template<class T>
		T *createWidget(const std::string &type, const glm::vec4 &destRectPerc,
						const glm::vec4 &destRectPix,
						const std::string &name = "") {
			CEGUI::Window *newWindow = CEGUI::WindowManager::getSingleton().createWindow(
					type, name);
			this->_root->addChild(newWindow);
			setWidgetDestRect(newWindow, destRectPerc, destRectPix);
			return (static_cast<T *>(newWindow));
		};

		template<class T>
		T *getChildFromRoot(const std::string& name) {
			return (dynamic_cast<T *>(this->_context->getRootWindow()->getChild(name)));
		}

		void loadLayout(const std::string layoutFile);

		static void
		setWidgetDestRect(CEGUI::Window *widget, const glm::vec4 &destRectPerc,
						  const glm::vec4 &destRectPix);

		//Getters
		static CEGUI::OpenGL3Renderer *getRenderer();

		const CEGUI::GUIContext *getContext();

		//Message Box.
		void showMessageBox(const std::string Message);

		void showMessageBox(const std::string Message, const std::string title);

		bool mb_Message_ClosedClicked(const CEGUI::EventArgs &e);

	private:
		static CEGUI::OpenGL3Renderer *_ceguiRenderer;
		CEGUI::GUIContext *_context;
		CEGUI::Window *_root;
		CEGUI::FrameWindow *_messageBox;

		bool _showCursor;
		unsigned int _lastTime;

		void _initMessageBox();
	};
};