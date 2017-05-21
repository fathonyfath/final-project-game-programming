#pragma once

#include "Engine\Util\state.h"
#include "Engine\Util\camera.h"
#include "Engine\Graphic\sprite_renderer.h"
#include "Engine\game_object.h"

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
	glm::vec3 worldPos;

	Camera* camera;
	SpriteRenderer* renderer;
	Texture2D texture;

	GameObject* wallGameObject;
};