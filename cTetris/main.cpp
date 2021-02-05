#include <iostream>
#include <ncurses.h>
using namespace std;

string tetromino[7];
int nFieldWidth = 12;
int nFieldHeight = 18;
int nScreenWidth;
int nScreenHeight;
unsigned char *pField = nullptr;

int Rotate(int px, int py, int r) 
{
	switch(r % 4) {
		case 0 : return py * 4 + px; // 0 degree
		case 1 : return 12 + py - (px * 4);
		case 2 : return 15 - (py * 4) - px;
		case 3 : return 3 - py + (px * 4);
	}
	return 0;
}

int main()
{

	initscr();
	cbreak();
	noecho();
	clear();

	nScreenHeight = LINES - 1;
	nScreenWidth = COLS - 1;
	cout<<nScreenHeight<<" "<<nScreenWidth<<endl;
	
	//create asssets
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");
	tetromino[0].append("..X.");


	tetromino[1].append("..X.");
	tetromino[1].append(".XX.");
	tetromino[1].append(".X..");
	tetromino[1].append("....");
	
	tetromino[2].append(".X..");
	tetromino[2].append(".XX.");
	tetromino[2].append("..X.");
	tetromino[2].append("....");

	tetromino[3].append("....");
	tetromino[3].append(".XX.");
	tetromino[3].append(".XX.");
	tetromino[3].append("....");

	tetromino[4].append("..X.");
	tetromino[4].append(".XX.");
	tetromino[4].append("..X.");
	tetromino[4].append("....");

	tetromino[5].append("....");
	tetromino[5].append(".XX.");
	tetromino[5].append("..X.");
	tetromino[5].append("..X.");

	tetromino[6].append("....");
	tetromino[6].append(".XX.");
	tetromino[6].append(".X..");
	tetromino[6].append(".X..");

	pField = new unsigned char[nFieldWidth * nFieldHeight];
	for (int x = 0; x < nFieldWidth; ++x)
		for (int y = 0; y < nFieldHeight; ++y)
			pField[y * nFieldWidth + x] = (x == 0 || x == nFieldWidth - 1 || y == nFieldHeight - 1) ? 9 : 0;

	char *screen = new char[nScreenWidth * nScreenHeight];
	for (int i = 0; i < nScreenWidth * nScreenHeight; ++i) screen[i] = ' ';
	bool bGameOver = false;
	while (!bGameOver) {
		
		for (int x = 0; x < nFieldWidth; ++x) {
			for (int y = 0; y < nFieldHeight; ++y) {
				screen[(y + 2) * nScreenWidth + (x + 2) * nScreenHeight] = " ABCDEFG=#"[pField[y * nFieldWidth + x]];

			}
		}
		mvaddstr(0, 0, screen);
		refresh();
	}
	
}
