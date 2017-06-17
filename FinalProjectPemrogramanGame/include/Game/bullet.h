#pragma once
#include "Engine\game_object.h"

class Bullet : public GameObject {
public:
	Bullet(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size, float speed) : GameObject(renderer, sprite, size), speed(speed) {
		collider.p = colliderPos;
		collider.r = 9.0f;
	};
	void update(GameEngine* engine);
	float directionX;
	float directionY;

	float speed;

	c2Circle collider;
	c2v colliderPos;

};