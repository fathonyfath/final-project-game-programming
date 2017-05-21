#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Engine\Graphic\texture.h"
#include "Engine\Graphic\sprite_renderer.h"

class GameObject {
public:
	GameObject(SpriteRenderer& renderer, Texture2D& sprite, glm::vec3 size) : 
		_renderer(renderer), 
		_sprite(sprite), 
		size(size), 
		scale(1.0f, 1.0f, 1.0f), 
		color(1.0f, 1.0f, 1.0f), 
		rotation(0.0f) {};

	void setSprite(const Texture2D& sprite);
	void render();
	glm::vec3 position, scale, size, color;
	float rotation;

private:
	SpriteRenderer& _renderer;
	Texture2D& _sprite;
};