#include "Game\bullet.h"

void Bullet::update(GameEngine * engine) {
	float currentBulletXSpeed = std::sin(glm::radians(rotation)) * engine->getDeltaReadOnly() * speed;
	float currentBulletYSpeed = std::cos(glm::radians(rotation)) * engine->getDeltaReadOnly() * speed;
	glm::vec2 newPos = glm::vec2(position.x - currentBulletXSpeed, position.y + currentBulletYSpeed);
	position = glm::vec3(newPos.x, newPos.y, 0.0f);

	collider.p.x = position.x;
	collider.p.y = position.y;
}
