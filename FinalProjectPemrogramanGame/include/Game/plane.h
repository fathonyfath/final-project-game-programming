#pragma once
#include "Engine\game_object.h"

class Plane : public GameObject {
public:
	Plane(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size) : GameObject(renderer, sprite, size) {};
	void update(GameEngine* engine);
	glm::vec3 mousePositionToWorld;

	void setTarget(GameObject* target) {
		this->currentTarget = target;
	}

	GameObject* currentTarget = NULL;

private:
	float angleBetweenTwoVector(glm::vec3 a, glm::vec3 b) {
		float first = a.y - b.y;
		float second = a.x - b.x;
		return glm::degrees(std::atan2f(first, second));
	}

	Texture2D planeSprite;
	float speed = 500.0f;
};