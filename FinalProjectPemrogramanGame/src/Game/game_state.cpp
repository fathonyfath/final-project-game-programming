#include "Game\game_state.h"

#include "Engine\game_engine.h"

GameState GameState::_instance;

void GameState::init(GameEngine* engine) {
	this->camera = new Camera(engine->getScreenWidth(), engine->getScreenHeight());

	this->texture = ResourceManager::loadTexture("wall.jpg", false, "Wall");
	Shader shader = ResourceManager::getShader("Sprite");

	renderer = new SpriteRenderer(shader);
	camera->updateShaderViewProjection(shader);
}

void GameState::cleanup(GameEngine* engine) {
	delete(this->camera);
	delete(this->renderer);
}

void GameState::pause(GameEngine* engine) {
}

void GameState::resume(GameEngine* engine) {
}

void GameState::handleEvents(GameEngine * engine) {
	glm::vec3 worldSpace = camera->screenToWorldSpace(engine->getMousePos());
	this->worldPos = worldSpace;
}

void GameState::update(GameEngine * engine) {
}

void GameState::draw(GameEngine * engine) {
	glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	this->renderer->drawSprite(this->texture, glm::vec2(worldPos.x, worldPos.y), glm::vec2(100, 100), 45.0f, glm::vec3(0, 1, 1));

	glDisable(GL_BLEND);
}