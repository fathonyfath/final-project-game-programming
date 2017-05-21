#include "Game\game_state.h"

#include "Engine\game_engine.h"

GameState GameState::_instance;

void GameState::init(GameEngine* engine) {
	this->camera = new Camera(engine->getScreenWidth(), engine->getScreenHeight());

	this->texture = ResourceManager::getTexture("Wall");
	Shader shader = ResourceManager::getShader("Sprite");

	renderer = new SpriteRenderer(shader);
	camera->updateShaderViewProjection(shader);

	// Initialize GameObjects
	wallGameObject = new GameObject(*renderer, texture, glm::vec3(100, 100, 0));
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
	wallGameObject->position = glm::vec3(worldPos.x, worldPos.y, 0.0f);
}

void GameState::draw(GameEngine * engine) {
	glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	wallGameObject->render();

	glDisable(GL_BLEND);
}