#include "Game\game_state.h"

#include "Engine\game_engine.h"

#include <glm\gtx\compatibility.hpp>
#include <cmath>

GameState GameState::_instance;

void GameState::init(GameEngine* engine) {
	this->camera = new Camera(engine->getScreenWidth(), engine->getScreenHeight());

	this->planeTexture = ResourceManager::getTexture("Pesawat");
	this->pesawatBulletTexture = ResourceManager::getTexture("Wall");
	Shader shader = ResourceManager::getShader("Sprite");

	renderer = new SpriteRenderer(shader);
	camera->updateShaderViewProjection(shader);

	firstState = true;

	// Initialize GameObjects
	planeGameObject = new Plane(*renderer, planeTexture, glm::vec3(50, 50, 0));
	planeGameObject->position = glm::vec3(0, 0, 0);
}

void GameState::cleanup(GameEngine* engine) {
	delete(this->camera);
	delete(this->renderer);
}

void GameState::pause(GameEngine* engine) {
}

void GameState::resume(GameEngine* engine) {
}

void GameState::handleEvents(GameEngine * engine) {
	glm::vec3 mousePos = camera->screenToWorldSpace(engine->getMousePos());
	planeGameObject->mousePositionToWorld = mousePos;

	if (engine->leftMouseDown() && canShot) {
		shoot(planeGameObject->position, planeGameObject->rotation);
		canShot = false;
	}
}

void GameState::update(GameEngine * engine) {
	if (firstState) {
		firstState = false;
		return;
	}

	if (!canShot) {
		if (currentTime < cooldown) {
			currentTime += engine->getDeltaReadOnly();
		} else {
			currentTime = 0.0f;
			canShot = true;
		}
	}

	planeGameObject->update(engine);

	// Bullet gameObject
	for (unsigned int i = 0; i < bullets.size(); ++i) {
		Bullet* bulletGameObject = bullets[i];
		if ((bulletGameObject->position.x > 400.0f || bulletGameObject->position.x < -400.0f) ||
			(bulletGameObject->position.y > 400.0f || bulletGameObject->position.y < -400.0f)) {
			bullets.erase(bullets.begin() + i);
		}
	}

	for (unsigned int i = 0; i < bullets.size(); ++i) {
		Bullet* bulletGameObject = bullets[i];
		bulletGameObject->update(engine);
	}
}

void GameState::draw(GameEngine * engine) {
	glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (unsigned int i = 0; i < bullets.size(); ++i) {
		GameObject* bulletGameObject = bullets[i];
		bulletGameObject->render();
	}

	planeGameObject->render();

	glDisable(GL_BLEND);
}

void GameState::shoot(glm::vec3 position, float rotation) {
	Bullet* bullet = new Bullet(*renderer, pesawatBulletTexture, glm::vec3(10, 10, 0));
	bullet->position = position;
	bullet->rotation = rotation;
	bullets.push_back(bullet);
}
