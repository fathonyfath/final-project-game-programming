#pragma once
#include "Engine\game_object.h"

class Plane : public GameObject {
public:
	Plane(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size) : GameObject(renderer, sprite, size), shieldActive(false), cooldown(0.0f), resetCooldown(1.5f), health(3) {
		collider.p = colliderPos;
		collider.r = 20.0f;
	};
	void update(GameEngine* engine);
	glm::vec3 mousePositionToWorld;

	void setTarget(GameObject* target) {
		this->currentTarget = target;
	}

	void resetShiled() {
		cooldown = resetCooldown;
	}

	c2Circle collider;
	c2v colliderPos;

	bool shieldActive;
	float cooldown;

	int health;

	GameObject* currentTarget = NULL;

private:
	float angleBetweenTwoVector(glm::vec3 a, glm::vec3 b) {
		float first = a.y - b.y;
		float second = a.x - b.x;
		return glm::degrees(std::atan2f(first, second));
	}

	float resetCooldown;

	Texture2D planeSprite;
	float speed = 500.0f;
};