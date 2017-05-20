#include "Game\game_state.h"

#include "Engine\game_engine.h"

GameState GameState::_instance;

void GameState::init(GameEngine* engine) {
	this->camera = new Camera(engine->getScreenWidth(), engine->getScreenHeight());
	engine->setMainCamera(this->camera);
	Texture2D texture = ResourceManager::loadTexture("wall.jpg", false, "Wall");
	Shader shader = ResourceManager::getShader("Sprite");

	box = GKV::Box(glm::vec2(100, 100), "wall.jpg", shader.id);
	box.position = glm::vec2(0, 0);
}

void GameState::cleanup(GameEngine* engine) {
	engine->unsetMainCamera();
	delete(this->camera);
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
	glClearColor(0.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	box.render();

	glDisable(GL_BLEND);
}