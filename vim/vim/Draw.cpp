#include "Draw.h"

void Draw::Init()
{
	system("mode con cols=160 lines=50");
}

void Draw::SetCursor(unsigned x, unsigned y)
{
	auto StdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD coord = { x,y };
	SetConsoleCursorPosition(StdOut, coord);
}