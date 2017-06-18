#include "Game\menu_state.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"

MenuState MenuState::_instance;

void MenuState::init(GameEngine * engine) {

}

void MenuState::cleanup(GameEngine * engine) {
}

void MenuState::pause(GameEngine * engine) {
}

void MenuState::resume(GameEngine * engine) {
}

void MenuState::handleEvents(GameEngine * engine) {
}

void MenuState::update(GameEngine * engine) {
	glViewport(0, 0, engine->getScreenWidth(), engine->getScreenHeight());
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ImGui::Begin("Quez", &show_window);
	ImGui::SetNextWindowSize(ImVec2(100, 100), ImGuiSetCond_FirstUseEver);
	if (ImGui::Button("Play the Game!")) {
		engine->changeState(GameState::instance());
	}
	if (ImGui::Button("Exit Game")) {
		engine->quit();
	}
	ImGui::End();

}

void MenuState::draw(GameEngine * engine) {
}
