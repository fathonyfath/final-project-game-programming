#include "Engine\game_object.h"

void GameObject::setSprite(const Texture2D & sprite) {
	this->_sprite = sprite;
}

void GameObject::update(GameEngine * engine) {
}

void GameObject::render() {
	this->_renderer.drawSprite(this->_sprite, this->position, this->size * this->scale, this->rotation, this->color);
}
