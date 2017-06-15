#include "Game\bullet.h"

void Bullet::update(GameEngine * engine) {
	float currentBulletXSpeed = std::sin(glm::radians(rotation)) * engine->getDeltaReadOnly() * 1000.0f;
	float currentBulletYSpeed = std::cos(glm::radians(rotation)) * engine->getDeltaReadOnly() * 1000.0f;
	glm::vec2 newPos = glm::vec2(position.x - currentBulletXSpeed, position.y + currentBulletYSpeed);
	position = glm::vec3(newPos.x, newPos.y, 0.0f);
}
