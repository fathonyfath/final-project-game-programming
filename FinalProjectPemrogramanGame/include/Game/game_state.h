#pragma once

#include "Engine\Util\state.h"
#include "Engine\Util\camera.h"
#include "Engine\Graphic\sprite_renderer.h"

#include "Engine\Util\box.h"

class GameState : public State {

public:
	void init(GameEngine* engine);
	void cleanup(GameEngine* engine);

	void pause(GameEngine* engine);
	void resume(GameEngine* engine);

	void handleEvents(GameEngine* engine);
	void update(GameEngine* engine);
	void draw(GameEngine* engine);

	static GameState* instance() {
		return &_instance;
	}

private:
	static GameState _instance;

	Camera* camera;
	glm::vec3 worldPos;

	GKV::Box box;
};