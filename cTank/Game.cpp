#include <iostream>
#include <clocale>
#include <cstdlib>
#include <ctime>
#include "Game.h"

Game* Game::m_instance = nullptr;

Game::Game() {
    std::setlocale(LC_ALL, "");		//Set locale info, "" means default locale
    std::srand(std::time(nullptr));	//Initialize pseudo random number generator with the arugment pass as seed
    /* Setup ncurses library  */

    initscr();		//initsrc function is normally the first call when initializing a ncurses program
    cbreak();		//Don't use line buffering and making user typed character immediately available
    noecho();		//Don't echo user typed characters on cursor position
    start_color();	//Use color for terminal
    curs_set(0);	//Make cursor invisible

    //Create a ncurses window
    m_window = newwin(WINDOW_HEIGHT + WINDOW_POS_Y,	//End row
    	              WINDOW_WIDTH + WINDOW_POS_X,	//End column
		      WINDOW_POS_Y,			//Begin x
		      WINDOW_POS_X);			//Begin y
    nodelay(m_window, true);	//This make functions like getch() or wgetch() to be a non-blocking call
    keypad(m_window, true);	//Enable the keypad
    /* Assign some colors in pair to their index number */
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);

    /* Setup game class members */
    m_ticks = 0;	//Ticks start at 0
	//Create players
	playerOne = Tank(PLAYGROUND_WIDTH / 3 + PLAYGROUND_POS_X,	// centered vertical 
    			 PLAYGROUND_HEIGHT / 3 * 2 + PLAYGROUND_POS_Y,	// centered horizontal
			 1, 1, 'X', 3);

	playerTwo = Tank(PLAYGROUND_WIDTH / 3 * 2 + PLAYGROUND_POS_X,	// centered vertical 
    			 PLAYGROUND_HEIGHT / 3 * 2 + PLAYGROUND_POS_Y,	// centered horizontal
			 1, 1, 'H', 3);

   // Create enemies
   m_enemies = {};
    m_running = true;

}

Game* Game::GetInstance() {
    if (m_instance == nullptr) m_instance = new Game();
    return m_instance;
}

bool Game::IsRunning() const { return m_running; }

void Game::TickTock() { ++m_ticks; }

void Game::Input() {
    int ch = tolower(wgetch(m_window));
    switch (ch) {
	case 'q':
	    m_running = false;
	    break;

	case KEY_UP:
	    if (playerTwo.GetY() > PLAYGROUND_POS_Y + 1)
		playerTwo.SetY(playerTwo.GetY() - 1);
	    break;

	case KEY_DOWN:
	    if (playerTwo.GetY() < PLAYGROUND_HEIGHT - 1)
		playerTwo.SetY(playerTwo.GetY() + 1);
	    break;

	case KEY_LEFT:
	    if (playerTwo.GetX() > PLAYGROUND_POS_X + 1)
		playerTwo.SetX(playerTwo.GetX() - 1);
	    break;

	case KEY_RIGHT:
	    if (playerTwo.GetX() < PLAYGROUND_WIDTH + 1)
		playerTwo.SetX(playerTwo.GetX() + 1);
	    break;
	
	case 'w':
	    if (playerOne.GetY() > PLAYGROUND_POS_Y + 1)
		playerOne.SetY(playerOne.GetY() - 1);
	    break;

	case 's':
	    if (playerOne.GetY() < PLAYGROUND_HEIGHT - 1)
		playerOne.SetY(playerOne.GetY() + 1);
	    break;

	case 'a':
	    if (playerOne.GetX() > PLAYGROUND_POS_X + 1)
		playerOne.SetX(playerOne.GetX() - 1);
	    break;

	case 'd':
	    if (playerOne.GetX() < PLAYGROUND_WIDTH + 1)
		playerOne.SetX(playerOne.GetX() + 1);
	    break;

	default: break;
    }
}

void Game::Update() {
    //Random generate three kinds of rocks on random positions
    int randNum = std::rand();
}

void Game::Render() {
    werase(m_window);	//Clear screen immediately

    /* Render spaceship*/

    /* Render spaceship body */

    wattron(m_window, A_BOLD);
    wattron(m_window, COLOR_PAIR(1));	//Green
    mvwaddch(m_window, playerTwo.GetY(), playerTwo.GetX(), playerTwo.GetChar());
    wattroff(m_window, COLOR_PAIR(1));
    /* Render spaceship engine flame */
    if (m_ticks % 10 > 0) {
	wattron(m_window, COLOR_PAIR(m_ticks % 2 ? 3 : 4));	//Red or Yellow
	mvwaddch(m_window, playerTwo.GetY() + 1, playerTwo.GetX(), 'W');
	wattroff(m_window, COLOR_PAIR(m_ticks % 2 ? 3 : 4));
    }
    wattroff(m_window, A_BOLD);
    /* Render spaceship wings and head */
    wattron(m_window, COLOR_PAIR(2));	//Blue
    mvwaddch(m_window, playerTwo.GetY(), playerTwo.GetX() - 1, '[');
    mvwaddch(m_window, playerTwo.GetY(), playerTwo.GetX() + 1, ']');
    mvwaddch(m_window, playerTwo.GetY(), playerTwo.GetX() - 2, '<');
    mvwaddch(m_window, playerTwo.GetY(), playerTwo.GetX() + 2, '>');
    mvwaddch(m_window, playerTwo.GetY() - 1, playerTwo.GetX(), 'A');
    wattron(m_window, COLOR_PAIR(2));	//Blue

    /* Render UI */
    wattron(m_window, A_BOLD);
    box(m_window, 0, 0);	//Draw a box around the edge of the window
    
    wattron(m_window, COLOR_PAIR(2));	//Blue color
    mvwaddstr(m_window, BORDER_POS_Y, 20, " A Space game ");
    wattroff(m_window, COLOR_PAIR(2));
    
    wattron(m_window, COLOR_PAIR(playerTwo.GetLife() < 3 ? 3 : playerTwo.GetLife() < 6 ? 4 : 1));	//Green->Yellow->Red
    mvwprintw(m_window, BORDER_HEIGHT - BORDER_POS_Y, 60, "[ LIFE : %d ]", playerTwo.GetLife());
    wattroff(m_window, COLOR_PAIR(playerTwo.GetLife() < 3 ? 3 : playerTwo.GetLife() < 6 ? 4 : 1));	//Green->Yellow->Red
    wattroff(m_window, A_BOLD);

    wrefresh(m_window);	//Get actual output to the terminal
}

void Game::Quit() {
    delete m_instance;

    delwin(m_window);
    endwin();

    std::cout << "*************************\n";
    std::cout << "         Game Over       \n";
    std::cout << "*************************\n";
    std::cout << "\n";
}
