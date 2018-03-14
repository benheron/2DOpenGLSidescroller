#include <SDL.h>
#include <gl/glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include "Platform.h"
#include "states/StateManager.h"
#include "states/GameState.h"
#include "Renderer.h"
#include "ResourceManager.h"


#include <time.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;



//Input handler
void handleKeys(SDL_Event keyType, bool bKeyDown, int x, int y);


//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

bool gTimeStop = false;

KeyboardManager *kbManager;




void handleKeys(SDL_Event events, bool bKeyDown, int x, int y)
{

	switch (events.key.keysym.sym)
	{
	case SDLK_a: kbManager->setKeyDown("a", bKeyDown); break;
	case SDLK_b: kbManager->setKeyDown("b", bKeyDown); break;
	case SDLK_c: kbManager->setKeyDown("c", bKeyDown); break;
	case SDLK_d: kbManager->setKeyDown("d", bKeyDown); break;
	case SDLK_e: kbManager->setKeyDown("e", bKeyDown); break;
	case SDLK_f: kbManager->setKeyDown("f", bKeyDown); break;
	case SDLK_g: kbManager->setKeyDown("g", bKeyDown); break;
	case SDLK_h: kbManager->setKeyDown("h", bKeyDown); break;
	case SDLK_i: kbManager->setKeyDown("i", bKeyDown); break;
	case SDLK_j: kbManager->setKeyDown("j", bKeyDown); break;
	case SDLK_k: kbManager->setKeyDown("k", bKeyDown); break;
	case SDLK_l: kbManager->setKeyDown("l", bKeyDown); break;
	case SDLK_m: kbManager->setKeyDown("m", bKeyDown); break;
	case SDLK_n: kbManager->setKeyDown("n", bKeyDown); break;
	case SDLK_o: kbManager->setKeyDown("o", bKeyDown); break;
	case SDLK_p: kbManager->setKeyDown("p", bKeyDown); break;
	case SDLK_q: kbManager->setKeyDown("q", bKeyDown); break;
	case SDLK_r: kbManager->setKeyDown("r", bKeyDown); break;
	case SDLK_s: kbManager->setKeyDown("s", bKeyDown); break;
	case SDLK_t: kbManager->setKeyDown("t", bKeyDown); break;
	case SDLK_u: kbManager->setKeyDown("u", bKeyDown); break;
	case SDLK_v: kbManager->setKeyDown("v", bKeyDown); break;
	case SDLK_w: kbManager->setKeyDown("w", bKeyDown); break;
	case SDLK_x: kbManager->setKeyDown("x", bKeyDown); break;
	case SDLK_y: kbManager->setKeyDown("y", bKeyDown); break;
	case SDLK_z: kbManager->setKeyDown("z", bKeyDown); break;

	case SDLK_0: kbManager->setKeyDown("0", bKeyDown); break;
	case SDLK_1: kbManager->setKeyDown("1", bKeyDown); break;
	case SDLK_2: kbManager->setKeyDown("2", bKeyDown); break;
	case SDLK_3: kbManager->setKeyDown("3", bKeyDown); break;
	case SDLK_4: kbManager->setKeyDown("4", bKeyDown); break;
	case SDLK_5: kbManager->setKeyDown("5", bKeyDown); break;
	case SDLK_6: kbManager->setKeyDown("6", bKeyDown); break;
	case SDLK_7: kbManager->setKeyDown("7", bKeyDown); break;
	case SDLK_8: kbManager->setKeyDown("8", bKeyDown); break;
	case SDLK_9: kbManager->setKeyDown("9", bKeyDown); break;
	case SDLK_SPACE: kbManager->setKeyDown("space", bKeyDown); break;

	case SDLK_UP: kbManager->setKeyDown("up", bKeyDown); break;
	case SDLK_DOWN: kbManager->setKeyDown("down", bKeyDown); break;
	case SDLK_LEFT: kbManager->setKeyDown("left", bKeyDown); break;
	case SDLK_RIGHT: kbManager->setKeyDown("right", bKeyDown); break;
	case SDLK_ESCAPE: kbManager->setKeyDown("esc", bKeyDown); break;

	case SDLK_LSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;
	case SDLK_RSHIFT: kbManager->setKeyDown("shift", bKeyDown); break;

	}
}



void close()
{

	//Destroy window	
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();
}


int main( int argc, char* args[] )
{

	Platform *platform = new Platform("OpenGL project!", glm::vec2(640, 480));


	srand(time(NULL));
	
	kbManager = new KeyboardManager();
	ResourceManager* rm = new ResourceManager(kbManager);

	
	StateManager *stateManager = new StateManager();
	GameState *gs = new GameState(stateManager, platform, rm);
	stateManager->addState(gs);

	Renderer* renderer = new Renderer(platform, rm);


	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
		
	int x = 0, y = 0;
	SDL_GetMouseState(&x, &y);

	Text *fr = new Text(glm::vec3(10.f, 550.f, 0), "arial", 32, "000000000000", rm->getTextImageManager());


	unsigned int lastTime = SDL_GetTicks();

	//Enable text input
	//SDL_StartTextInput();

	//While application is running
	while( !quit )
	{

		unsigned int current = SDL_GetTicks();
		

		float msbf = current - lastTime;
		

		float dt = (float)(current - lastTime) / 1000.0f;
		lastTime = current;

		


		


		if (dt > 0.050)
		{
			dt = 0.050;
		}

		int frames = 1 / dt;

		if (frames > 0)
		{
			std::string str = std::to_string(frames);
			fr->changeTextEnd(str);
		}
	

		//printf("%i ms/frame\n", int(frames));

		//Handle events on queue
		while( SDL_PollEvent( &e ))
		{
			//User requests quit
			switch (e.type)
			{
			case SDL_QUIT:
				quit = true;
				break;

			case SDL_KEYDOWN:
				handleKeys(e, true, x, y);
				break;
			case SDL_KEYUP:
				handleKeys(e, false, x, y);
				break;
			}
		}

		stateManager->update(dt);


		renderer->render(stateManager->getStates());
		//renderer->renderFrameRate(fr);
			
		//Update screen
		SDL_GL_SwapWindow( platform->getWindow() );
	}
		

	

	//Free resources and close SDL
	close();

	return 0;
}
