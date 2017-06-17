#include "Game\enemy_plane.h"

void EnemyPlane::update(GameEngine * engine) {
	if (firstTime) {
		int xLimit = engine->getScreenWidth();
		int yLimit = engine->getScreenHeight();
		int xRand = rand() % xLimit;
		int yRand = rand() % yLimit;

		xRand += 1;
		yRand += 1;

		xRand -= xLimit / 2.0f;
		yRand -= yLimit / 2.0f;

		position.x = xRand;
		position.y = yRand;

		limitTop = engine->getScreenHeight() / 2.0f;
		limitBottom = -engine->getScreenHeight() / 2.0f;

		limitLeft = -engine->getScreenWidth() / 2.0f;
		limitRight = engine->getScreenWidth() / 2.0f;

		float floatDir = (float)(rand() % 360);

		this->rotationSpeed = (float)(rand() % 50 + 20);

		directionX = std::sin(glm::radians(floatDir));
		directionY = std::cos(glm::radians(floatDir));

		int speedRand = rand() % 200 + 100;
		this->speed = speedRand;

		firstTime = false;
	}

	float deltaTime = engine->getDeltaReadOnly();

	float xSpeed = directionX * this->speed * deltaTime;
	float ySpeed = directionY * this->speed * deltaTime;

	this->rotation += rotationSpeed * deltaTime;

	position.x = position.x + xSpeed;
	position.y = position.y + ySpeed;

	if (position.x < limitLeft) {
		position.x = limitLeft;
		directionX *= -1;
	}
	if (position.x > limitRight) {
		position.x = limitRight;
		directionX *= -1;
	}
	if (position.y < limitBottom) {
		position.y = limitBottom;
		directionY *= -1;
	}
	if (position.y > limitTop) {
		position.y = limitTop;
		directionY *= -1;
	}

	collider.p.x = position.x;
	collider.p.y = position.y;
}
