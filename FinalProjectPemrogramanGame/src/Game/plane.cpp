#include "Game\plane.h"
#include "Engine\Util\resource_manager.h"
#include "Engine\game_engine.h"

void Plane::update(GameEngine* engine) {
	if (cooldown > 0.0f) {
		shieldActive = true;
		cooldown -= engine->getDeltaReadOnly();
	} else {
		shieldActive = false;
	}

	if (currentTarget == NULL) {
		float rotation = angleBetweenTwoVector(position, mousePositionToWorld) + 90.0f;
		this->rotation = rotation;
	} else {
		float rotation = angleBetweenTwoVector(position, currentTarget->position) + 90.0f;
		this->rotation = rotation;
	}

	float distance = glm::distance(position, mousePositionToWorld);
	float moveRotation = angleBetweenTwoVector(position, mousePositionToWorld) + 90.0f;
	if (distance > 3.0f) {
		float slowFactor = distance - 3.0f;
		if (slowFactor > 50.0f) slowFactor = 50.0f;
		slowFactor = slowFactor / 50.0f;
		float xDir = std::sin(glm::radians(moveRotation)) * engine->getDeltaReadOnly() * speed * slowFactor;
		float yDir = std::cos(glm::radians(moveRotation)) * engine->getDeltaReadOnly() * speed * slowFactor;
		glm::vec2 newPos = glm::vec2(position.x - xDir, position.y + yDir);
		position = glm::vec3(newPos.x, newPos.y, 0.0f);
	}

	collider.p.x = position.x;
	collider.p.y = position.y;
}