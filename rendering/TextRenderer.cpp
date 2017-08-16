//
// Created by Owen Exall on 2017/08/16.
//

#include "TextRenderer.hpp"

cge::TextRenderer::TextRenderer() {
	this->_fontNormal = FONS_INVALID;

	this->_blackColor = glfonsRGBA(0,0,0,255);

	if ((this->_context = glfonsCreate(512, 512, FONS_ZERO_TOPLEFT)) == nullptr) {
		std::cout << "Failed to load fonts." << std::endl;
		throw BombermanException("Failed to Init Fonts.");
	}

	this->_fontNormal = fonsAddFont(this->_context, "sans", "../resources/Fonts/DroidSerif-Regular.ttf");
	if (this->_fontNormal == FONS_INVALID) {
		std::cout << "Failed to load regular font." << std::endl;
		throw BombermanException("Failed  to load regular font.");
	}
}

cge::TextRenderer::~TextRenderer() {
	glfonsDelete(this->_context);
}

void cge::TextRenderer::DrawText(std::string text) {
	float sx, sy, dx, dy, lh = 0;

	sx = 50; sy = 50;
	dx = sx; dy = sy;

	dash(dx, dy);
	fonsClearState(this->_context);
	fonsSetSize(this->_context, 24.0f);
	fonsSetFont(this->_context, this->_fontNormal);
	fonsVertMetrics(this->_context, nullptr, nullptr, &lh);
	dx = sx;
	dy += lh;
	dash(dx, dy);

	fonsSetSize(this->_context, 24.0f);
	fonsSetFont(this->_context, this->_fontNormal);
	fonsSetColor(this->_context, this->_blackColor);
	fonsDrawText(this->_context, dx,dy,text.c_str(), nullptr);

	fonsDrawDebug(this->_context, 800.0, 50.0);
	glEnable(GL_DEPTH_TEST);
}

void cge::TextRenderer::dash(float dx, float dy) {
	glBegin(GL_LINES);
	glColor4ub(0, 0, 0, 128);
	glVertex2f(dx-5,dy);
	glVertex2f(dx-10,dy);
	glEnd();
}
