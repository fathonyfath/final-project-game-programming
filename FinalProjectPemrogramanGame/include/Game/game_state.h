#pragma once

#include "Engine\Util\state.h"
#include "Engine\Util\camera.h"
#include "Engine\Graphic\sprite_renderer.h"
#include "Engine\game_object.h"
#include "Game\plane.h"
#include "Game\bullet.h"
#include "Game\enemy_plane.h"
#include "Game\bullet_impact.h"

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

	void getAndUpdateNearestEnemyPlane();

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
	Texture2D enemyBoxTexture;
	Texture2D enemyBulletTexture;
	Texture2D backgroundTexture;

	Texture2D planeShadowTexture;
	Texture2D enemyBoxShadowTexture;

	Texture2D bulletImpactTexture;
	Texture2D bulletImpactEnemyTexture;

	GameObject* background;

	Plane* planeGameObject;
	GameObject* planeShadowObject;
	std::vector<Bullet*> bullets;
	std::vector<EnemyPlane*> enemies;
	std::vector<GameObject*> enemiesShadow;
	std::vector<BulletImpact*> bulletImpacts;

	std::vector<Bullet*> bulletsToPlayer;

	bool firstState = true;

	bool canShot = true;

	float cooldown = 0.1f;
	float currentTime = 0.0f;


	void shoot(glm::vec3 position, float rotation);
	void enemyPlaneDestroyed(glm::vec3 position, float rotation);
};