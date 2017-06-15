#include "Game\plane.h"
#include "Engine\Util\resource_manager.h"
#include "Engine\game_engine.h"

void Plane::update(GameEngine* engine) {
	float rotation = angleBetweenTwoVector(position, mousePositionToWorld) + 90.0f;
	this->rotation = rotation;

	float distance = glm::distance(position, mousePositionToWorld);
	if (distance > 3.0f) {
		float slowFactor = distance - 3.0f;
		if (slowFactor > 50.0f) slowFactor = 50.0f;
		slowFactor = slowFactor / 50.0f;
		float xDir = std::sin(glm::radians(this->rotation)) * engine->getDeltaReadOnly() * speed * slowFactor;
		float yDir = std::cos(glm::radians(this->rotation)) * engine->getDeltaReadOnly() * speed * slowFactor;
		glm::vec2 newPos = glm::vec2(position.x - xDir, position.y + yDir);
		position = glm::vec3(newPos.x, newPos.y, 0.0f);
	}
}