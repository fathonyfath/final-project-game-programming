#pragma once

#include "Engine\Util\state.h"
#include "Engine\Util\camera.h"
#include "Engine\Graphic\sprite_renderer.h"
#include "Engine\game_object.h"
#include "Game\plane.h"
#include "Game\bullet.h"

#include <vector>

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
	glm::vec3 mousePosInWorldSpace;

	Camera* camera;
	SpriteRenderer* renderer;

	Texture2D planeTexture;
	Texture2D pesawatBulletTexture;

	Plane* planeGameObject;
	std::vector<Bullet*> bullets;
	std::vector<GameObject*> enemies;

	bool firstState = true;

	bool canShot = true;

	float cooldown = 0.3f;
	float currentTime = 0.0f;


	void shoot(glm::vec3 position, float rotation);
};