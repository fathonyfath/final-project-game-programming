#include "Engine\game_engine.h"
#include "Game\game_state.h"
#include "Game\menu_state.h"

int main(int argc, char** argv) {
	GameEngine engine;
	engine.init("Quez", 520, 620, false, WindowFlag::WINDOWED, 0, 1);
	engine.setDebugFPS(false);

	engine.changeState(MenuState::instance());

	while (engine.isRunning()) {
		engine.updateFPS();
		engine.handleEvent();
		engine.update();
		engine.draw();
		engine.lateFPS();
	}

	engine.cleanup();
	
	return 0;
}