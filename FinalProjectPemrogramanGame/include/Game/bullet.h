#pragma once
#include "Engine\game_object.h"

class Bullet : public GameObject {
public:
	Bullet(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size) : GameObject(renderer, sprite, size) {};
	void update(GameEngine* engine);
	float directionX;
	float directionY;

};