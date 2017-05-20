#pragma once

class GameEngine;

class State {

public:
	virtual void init(GameEngine* engine) = 0;
	virtual void cleanup(GameEngine* engine) = 0;

	virtual void pause(GameEngine* engine) = 0;
	virtual void resume(GameEngine* engine) = 0;

	virtual void handleEvents(GameEngine* engine) = 0;
	virtual void update(GameEngine* engine) = 0;
	virtual void draw(GameEngine* engine) = 0;

protected:
	State() {}
};