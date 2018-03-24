#include "Frame.h"

Frame::Frame(Texture* spritesheet, glm::vec2 framePos, glm::vec2 frameDimens) : spritesheet(spritesheet), framePos(framePos), frameDimens(frameDimens)
{

}

Frame::~Frame()
{

}

glm::vec2 Frame::getFramePos()
{
	return framePos;
}

glm::vec2 Frame::getFrameDimens()
{
	return frameDimens;
}