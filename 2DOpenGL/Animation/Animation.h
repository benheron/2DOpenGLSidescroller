#pragma once
#include <string>
#include <vector>
#include "AnimationType.h"

class Animation {
public:
	Animation();
	~Animation();

	void animationInit();

	void update(float dt);

	
	Frame* getFrame(int index);
	Frame* getCurrentFrame();

	void setAnimationType(AnimationType* anTy); 
	AnimationType* getAnimationType() { return aniType; }

	int getNumFrames();

	void setFrameRate(int fr);
	int getFrameRate();


	void pauseAnimation();
	void playAnimation();

protected:
	AnimationType *aniType;
	int currentFrameIndex;

	int frameRate;

	bool playTheAnimation;

	float frameTimings;
};