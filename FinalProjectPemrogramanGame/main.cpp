#include "Engine\game_engine.h"
#include "Game\game_state.h"

int main(int argc, char** argv) {
	GameEngine engine;
	engine.init("Test Game Engine", 520, 620, false, WindowFlag::WINDOWED, 0, 1);
	engine.setDebugFPS(true);

	//engine.changeState(GameState::instance());

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