#pragma once
#include "Engine\game_object.h"
#include <cstdlib>

class EnemyPlane : public GameObject {
public:
	EnemyPlane(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size) : GameObject(renderer, sprite, size), health(15), isDead(false) {
		collider.r = size.x / 2.0f;
	};
	void update(GameEngine* engine);

	int health;

	c2Circle collider;
	bool isDead = false;

private:
	Texture2D planeSprite;
	float speed = 50.0f;
	float rotationSpeed;
	float directionX = -1.0f;
	float directionY = -1.0f;

	bool firstTime = true;

	float limitTop, limitBottom, limitLeft, limitRight;
};