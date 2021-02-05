#include <thread>
#include <chrono>
#include "Game.h"

//Access the literal that representing chrono secondseg. 1s or 0.2s
using namespace std::chrono_literals;

int main() {
    Game* game = Game::GetInstance();

    while (game->IsRunning()) {
	game->Input();
	game->Update();
	game->Render();

	game->TickTock();
	std::this_thread::sleep_for(0.05s);
	
    }

    game->Quit();

    return 0;
}
