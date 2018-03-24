#pragma once
#include <string>
#include <vector>
#include "../Texture.h"


class Frame {
public:
	Frame(Texture* spritesheet, glm::vec2 framePos, glm::vec2 frameDimens);
	~Frame();


	glm::vec2 getFramePos();
	glm::vec2 getFrameDimens();

protected:
	Texture* spritesheet;
	glm::vec2 framePos;
	glm::vec2 frameDimens;

};