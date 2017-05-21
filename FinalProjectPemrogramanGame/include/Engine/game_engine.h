#pragma once

#include <SDL2\SDL.h>
#include <GL\glew.h>
#include <string>
#include <vector>
#include <iostream>
#include <glm\glm.hpp>

#include "Engine\Util\state.h"
#include "Engine\Util\input.h"
#include "Engine\Util\camera.h"

#include "Engine\Util\resource_manager.h"
#include "Engine\Graphic\sprite_renderer.h"
#include "Engine\Util\camera.h"

using namespace std;

enum class WindowState { RUNNING, EXIT };
enum class WindowFlag { WINDOWED, FULLSCREEN, EXCLUSIVE_FULLSCREEN, BORDERLESS };

class GameEngine {

public:
	void init(string title, unsigned int width, unsigned int height, bool vsync, WindowFlag windowFlag, unsigned int targetFrameRate, float timeScale);
	void cleanup();

	void changeState(State* state);
	void pushState(State* state);
	void popState();

	void updateFPS();
	void handleEvent();
	void update();
	void draw();
	void lateFPS();

	bool isRunning() { return this->windowState == WindowState::RUNNING; };
	void quit() { this->windowState = WindowState::EXIT; }
	void setDebugFPS(bool debugFPS) { this->debugFPS = debugFPS; }
	
	void logError(string errorString);
	void logDebug(string debugString);

	float getScreenHeight();
	float getScreenWidth();
	const Input* getInput();

	glm::vec3 getMousePos();

	void setMainCamera(Camera* camera);
	void unsetMainCamera();

private:
	vector<State*> states;
	unsigned int lastFrame = 0, last = 0, _fps = 0, fps = 0;
	float targetFrameTime = 0, timeScale;
	WindowState windowState;
	unsigned int screenWidth, screenHeight;
	bool debugFPS;
	SDL_Window* window;
	int frameCounter;
	string windowTitle;

	void limitFPS();
	float getDeltaTime();
	void getFPS();

	void handleKeyEvent(Uint32 eventType, SDL_Keycode keycode);

	Camera* mainCamera;
	Input* input;
};
