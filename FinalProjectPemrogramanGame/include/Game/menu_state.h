#pragma once
#include "Engine\Util\state.h"
#include "Engine\game_object.h"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_sdl_gl3.h"

#include "Game\game_state.h"

class MenuState : public State {

public:
	void init(GameEngine* engine);
	void cleanup(GameEngine* engine);

	void pause(GameEngine* engine);
	void resume(GameEngine* engine);

	void handleEvents(GameEngine* engine);
	void update(GameEngine* engine);
	void draw(GameEngine* engine);

	static MenuState* instance() {
		return &_instance;
	}

private:
	static MenuState _instance;

	ImVec4 clear_color = ImColor(100, 50, 80);
	bool show_window = true;
};