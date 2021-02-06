#ifndef _GAME_H_
#define _GAME_H_

#include <ncurses.h>
#include <vector>
#include "Tank.h"
#include "constants.h"

class Game {
    public:
	Game();

	static Game* GetInstance();

	bool IsRunning() const;
	void TickTock();

	void Input();
	void Update();
	void Render();

	void Quit();
	
    private:
	static Game* m_instance;    //The singleton

	unsigned m_ticks;	//Frame number from game started

	WINDOW* m_window;	//The main ncurses window
	bool m_running;		//Game is running or not
	Tank playerOne;//The first player
	Tank playerTwo;//The second player
	std::vector<Tank> m_enemies;
};


#endif
