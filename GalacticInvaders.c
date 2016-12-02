/*			COMPUTER PROGRAMMING FINAL PROJECT

Programmed by: Muhammmad Moaz Khan			SECTION: BESE 4B
	       Raza Yunus
	       Emad ul Ehsan
==========================================================================*/
#include"galactic_warriors.h"
#include"snake_game.h"

void loading(int);

int main()
{
	setwindowsize(800, 642);
		menu();

	return 0;
}
/****************************** LOADING ********************************/
void loading(int z)
{
	system("cls");
	system("color F9"); // blue and white background
	
	int xcoordinate = 0, ycoordinate = MAX_YCOORD / 2, i;
	PlaceCursor(xcoordinate + 35, ycoordinate);
	printf(" LOADING ");
	PlaceCursor(xcoordinate, ycoordinate += 2);
	color(153);
	for (i = xcoordinate; i < MAX_XCOORD + 20; i++)
	{
		printf("%c", BLOCK);
		Sleep(50);
	}
	if (z == SPACE)
		startgame();
	else if (z == SNAKE)
		SnakeGame();
}