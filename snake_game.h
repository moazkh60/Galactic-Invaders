
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>

#define MAX_X 79		
#define MAX_Y 39
#define MIN_X 0
#define MIN_Y 0

#define UP 1
#define RIG 2
#define DOW 3
#define LEF 4
#define HEAD 10		//For Checking That whether Current End being Passed to "moveSnake" function is HEAD or TAIL
#define TAIL 20				
#define ON 1		//Checker for Snake's body Array
#define OFF 0

#define SNAKE 200	  //For SNAKE GAME
#define SPACE 300
#define SAVE 400

#define BLOCK 219
#define BKGRID 176

void SnakeGame();
void SnakeBoundary();
void moveSnake();

////////////////////////////////////// START GAME OF SNAKE \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//
void SnakeGame()
{
	int hx = MAX_X / 2, hy = MAX_Y / 2;					//Coordinates of head of Snake
	int tx = hx - 3, ty = hy;							//Coordinates of tail of Snake
	int sx, sy;											//Coordinates of Seed
	int snake_head = RIG;								//Current direction of motion of snake is RIGHT

	int score = 0;

	int turn_x[10000] = { 0 }, turn_y[10000] = { 0 };			//To remember the turning points because the tail is trailing behind
	int snake_tail[10000] = { 0 };							//Flag for tail of snake to REMEBER directions to follow after each turning point, because its direction is different then the direction of HEAD after the turning point
	int i = 0, j = 0;										//subscript for snake_tail array
	int seed = OFF;

	int snake_body[MAX_X][MAX_Y] = { 0 };					//Array to keep track of body of snake. It'd help in place seed at random points except on the body of the snake


	system("cls");
	system("color F0");

	color(249);
	SnakeBoundary();										//Drawing the Boundary of the Court

	srand(time(NULL));
	snake_tail[0] = RIG;
	while (1)
	{
		if (seed == OFF)									//Place new seed only if previous seed is OFF i.e. Eaten!
		do{													//Randomizing the coordinates of snake and placing it not on the body of snake
			sx = 1 + rand() % (MAX_X - 1);
			sy = 1 + rand() % (MAX_Y - 1);

			seed = ON;
		} while (snake_body[sx][sy] != 0);

		color(252);
		PlaceCursor(sx, sy);
		printf("%c", 3);

		if (_kbhit()){										//Controlling the motion of snake based on the keys pressed by the player
			_getch();
			if (GetAsyncKeyState(VK_RIGHT))
			{
				if ((snake_head != RIG) && (snake_head != LEF)){			//if snake's is not moving in right or left direction, only then turn it to RIGHT
					snake_head = RIG;
					turn_x[i] = hx;
					turn_y[i] = hy;
					snake_tail[++i] = RIG;
				}
			}
			else if (GetAsyncKeyState(VK_LEFT))
			{
				if ((snake_head != RIG) && (snake_head != LEF)){			//if snake's is not moving in right or left direction, only then turn it to LEFT
					snake_head = LEF;
					turn_x[i] = hx;
					turn_y[i] = hy;
					snake_tail[++i] = LEF;
				}
			}
			else if (GetAsyncKeyState(VK_UP))
			{
				if ((snake_head != UP) && (snake_head != DOW)){				//if snake's is not moving in upward or downward direction, only then turn it to UP
					snake_head = UP;
					turn_x[i] = hx;
					turn_y[i] = hy;
					snake_tail[++i] = UP;
				}
			}
			else if (GetAsyncKeyState(VK_DOWN))
			{
				if ((snake_head != UP) && (snake_head != DOW)){				//if snake's is not moving in upward or downward direction, only then turn it to DOWN
					snake_head = DOW;
					turn_x[i] = hx;
					turn_y[i] = hy;
					snake_tail[++i] = DOW;
				}
			}
			else if (GetAsyncKeyState(VK_ESCAPE))
				pause(SNAKE);

		}

		moveSnake(snake_head, &hx, &hy, HEAD);
		if (snake_body[hx][hy] == ON){
			break;
		}
		else{
			snake_body[hx][hy] = ON;										//Turning on the Array element  at that position in array where snake's body lies
		}
		if (sx == hx && sy == hy){
			seed = OFF;
			printf("\a");
			score++;
			update_profile(score, 0, 0, SNAKE);			//update profile on each iteration
		}

		if ((hx == MAX_X) && ((hy == MAX_Y / 2) || (hy == MAX_Y / 2 - 1) || (hy == MAX_Y / 2 + 1)))
			hx = MIN_X;
		else if ((hx == MIN_X) && ((hy == MAX_Y / 2) || (hy == MAX_Y / 2 - 1) || (hy == MAX_Y / 2 + 1)))
			hx = MAX_X;
		else if ((hx == MIN_X || hx == MAX_X || hy == MIN_Y || hy == MAX_Y))		//break the loop if snake touches the boundry except the slots
			break;
		if (seed == ON){													//i.e. if seed is eaten, Don't remove the tail at that instant

			if (tx == turn_x[j] && ty == turn_y[j])							//Checking The Turning ponts if any
				++j;
			moveSnake(snake_tail[j], &tx, &ty, TAIL);						//Calling the move function to move the TAIL
			snake_body[tx][ty] = OFF;										//Removing the footprint of TAIL from Array
		}
		if ((tx == MAX_X) && ((ty == MAX_Y / 2) || (ty == MAX_Y / 2 - 1) || (ty == MAX_Y / 2 + 1)))
			tx = MIN_X;
		else if ((tx == MIN_X) && ((ty == MAX_Y / 2) || (ty == MAX_Y / 2 - 1) || (ty == MAX_Y / 2 + 1)))
			tx = MAX_X;

		color(249);
		PlaceCursor(35, 45);
		printf("Your Score: %3d", score);



		Sleep(70);
	}	//end while

	printf("\a");
	gameover(score);

	_getch();
}
//========================= SNAKE BOUNDARY FUNCTION =============================================
void SnakeBoundary()
{
	int i, j;
	for (i = 0; i <= MAX_X; ++i){
		for (j = 0; j <= MAX_Y; ++j){
			if ((i == MIN_X || i == MAX_X || j == MIN_Y || j == MAX_Y) && (j != MAX_Y / 2) && (j != MAX_Y / 2 - 1) && (j != MAX_Y / 2 + 1)){
				PlaceCursor(i, j);
				printf("%c", BLOCK);
			}
		}
	}
}

//============================= MOVEMENT OF SNAKE ================================================

void moveSnake(int snake, int *x, int *y, int end)
{
	switch (snake)
	{
	case UP: --*y;
		break;
	case DOW: ++*y;
		break;
	case LEF: --*x;
		break;
	case RIG: ++*x;
		break;
	}

	PlaceCursor(*x, *y);
	if (end == HEAD)					//If the end Passed to this function is HEAD, then move the head by printing block at next point
	{
		color(250);
		printf("%c", 223);
	}
	else if (end == TAIL)				//If end passed to this fuction is TAIL, then move the tail forward by printing space at that point
		printf(" ");
}