#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<string.h>


#define MAX_XCOORD 60 // for galactic warriors
#define MIN_XCOORD 0
#define MAX_YCOORD 49
#define MIN_YCOORD 0

#define SNAKE 200	  //For SNAKE GAME
#define SPACE 300
#define SAVE 400

#define BLOCK 219
#define BKGRID 176

struct profile {
	char name[20];
	char password[4];
	int enemy_lives_remaining;
	int players_lives_remaining;
	int p_score;
	int snake_score;

}p;

FILE *fptr;		//Global variables
char temp_name[20];

void menu();
void startgame();

void movement(int *x, int *y, int *b_Xcoord, int *b_Ycoord, BOOL *fire);
void enemy_movement(int e_xcoord, int e_ycoord);
void fire(int x, int y, BOOL *fire_b);

BOOL bullet_hit(int b_xcoord, int b_ycoord, int ship_xcoord, int ship_ycoord);
void bomb_drop(int bomb_xcoord, int bomb_ycoord);
BOOL bomb_hit(int ship_x, int ship_y, int bomb_x, int bomb_y);

BOOL checklives(int l, int e_l);
void calculatepoints(int points);
void remaining_lives(int, int);

void controls();
void erase(int x, int y);
void erase_ship(int e_x, int e_y);

void timer(int *, int *, int *);
void pause(int game);
void gameover(int score);
void loading(int);

void add_new_profile();
void view_profiles();
void select_profile(int z);
void update_profile(int score, int enemylives, int playerlives, int game);
void delete_profile();

void print_background();
void game_boundary();

void boundary();
void help_credits();
void exit_game();

void color(int x);
void PlaceCursor(int x, int y);
void setwindowsize(int height, int width);

void menu()
{
	system("cls");
	system("color F0");
	color(249);
	boundary();

	int xcoordinate = MAX_XCOORD - 27, ycoordinate = MAX_YCOORD - 32, state;
	color(159);
	PlaceCursor(30, 14);
	printf("       GAME MENU       ");
	color(159);

	PlaceCursor(xcoordinate, ycoordinate);
	while (1)
	{

		if (ycoordinate == 17)	/*if this coordinate then the color is blue otherwise white*/
		{
			color(159); 
			PlaceCursor(33, 17);
			printf(" Galactic Warrior ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 17);
			printf(" Galactic Warrior ");
		}
		if (ycoordinate == 19)/*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(33, 19);
			printf(" Galactic Snake   ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 19);
			printf(" Galactic Snake   ");
		}
		if (ycoordinate == 21)/*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(33, 21);
			printf(" Add New Profile  ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 21);
			printf(" Add New Profile  ");
		}
		if (ycoordinate == 23)/*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(33, 23);
			printf(" View Statistics  ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 23);
			printf(" View Statistics  ");
		}
		if (ycoordinate == 25)/*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(33, 25);
			printf(" Credits          ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 25);
			printf(" Credits          ");
		}
		if (ycoordinate == 27)/*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(33, 27);
			printf(" Exit Game        ");
		}
		else
		{
			color(249);
			PlaceCursor(33, 27);
			printf(" Exit Game        ");
		}
		PlaceCursor(79, 48);
		_getch();
		if (GetAsyncKeyState(VK_UP) && ycoordinate > 17)
			PlaceCursor(xcoordinate, --ycoordinate);
		if (GetAsyncKeyState(VK_DOWN) && ycoordinate < 27)
			PlaceCursor(xcoordinate, ++ycoordinate);
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 16 && ycoordinate < 18)
		{
			state = 1;
			break;
		}
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 18 && ycoordinate < 20)
		{
			state = 2;
			break;
		}
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 20 && ycoordinate < 22)
		{
			state = 3;
			break;
		}
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 22 && ycoordinate < 24)
		{
			state = 4;
			break;
		}
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 24 && ycoordinate < 26)
		{
			state = 5;
			break;
		}
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 26 && ycoordinate < 28)
		{
			state = 6;
			break;
		}
	}
	switch (state)
	{
	case 1:
		Beep(120, 500);
		select_profile(SPACE);
		break;
	case 2:
		Beep(120, 500);
		select_profile(SNAKE);
		break;
	case 3:
		Beep(120, 500);
		add_new_profile();
		break;
	case 4:
		Beep(120, 500);
		view_profiles();
		break;
	case 5:
		Beep(120, 500);
		help_credits();
		break;
	case 6:
		Beep(120, 500);
		exit_game();
		break;
	}
}

void startgame()
{
	system("cls");
	system("color F0");
	color(249);
	print_background();
	game_boundary();
	remaining_lives(6, 3);
	controls();

	char ship[3] = { 17, 254, 16 }; /* left arrow, box, right arrow and their coordinates*/

	BOOL fire_bullet = FALSE;
	BOOL ship_moved = FALSE;
	int points = 0, player_lives = 3, enemy_lives = 6;

	int xcoord = MIN_XCOORD + 2, ycoord = MAX_YCOORD - 2; /* 47*/
	int bomb_xcoord = 30, bomb_ycoord = 5;
	int bullet_xcoord = 30, bullet_ycoord = ycoord; /*starting bullet will be fired from the ship's position */
	int hour = 0, min = 1, sec = 1, count = 1, i;

	srand(time(NULL)); /* randomize x axis for droping bombs*/

	while (checklives(player_lives, enemy_lives) == TRUE)
	{
		if (hour == 0 && min == 0 && sec == 0)	/* checking the time */
			gameover(points);

		if (_kbhit()) /*checking if any key is pressed on every iteration */
		{
			erase_ship(xcoord, ycoord);	/* remove footprints */
			movement(&xcoord, &ycoord, &bullet_xcoord, &bullet_ycoord, &fire_bullet); /* move tray and check for fire */
		}
		if (bullet_hit(bullet_xcoord, bullet_ycoord, bomb_xcoord, 4) == TRUE) /*check if bullet hit the enemy */
		{
			--enemy_lives;
			points += 10;
		}

		if (bomb_hit(xcoord, ycoord, bomb_xcoord, bomb_ycoord) == TRUE)		  /*check if enemy bomb hit the players ship*/
		{
			bomb_ycoord = 5; /* fire a new bomb */
			--player_lives;
		}
		if (count == 20)	/* as 50*20 = 1000ms = 1s */
		{
			count = 1;
			sec--;
			timer(&hour, &min, &sec);	/* start the timer */
		}

		if (bomb_ycoord == 5)
		{
			for (i = 1; i <= 3; i++)
				erase_ship(bomb_xcoord, i);		/* erasing enemy ship footprint */

			bomb_xcoord = 2 + (rand() % (MAX_XCOORD - 8));	   /* randomizing the xcoordinate of enemy ship */
			enemy_movement(bomb_xcoord, 1);
		}

		if (fire_bullet == FALSE)
			bullet_ycoord = ycoord;

		if (fire_bullet == TRUE) /* fire bullet is true if space is pressed */
		{

			if (bullet_ycoord >= 4)
				fire(bullet_xcoord, bullet_ycoord--, &fire_bullet);
			else
			{
				bullet_ycoord = ycoord;
				fire_bullet = FALSE;
			}
		}
		if (bomb_ycoord < MAX_YCOORD - 1)
			bomb_drop(bomb_xcoord, bomb_ycoord++);

		else
			bomb_ycoord = 5;

		color(250);
		PlaceCursor(xcoord, ycoord);
		printf("%c%c%c", ship[0], ship[1], ship[2]);
		Sleep(50);
		count++;

		if (bomb_ycoord != 5)
			erase(bomb_xcoord, bomb_ycoord - 1);

		calculatepoints(points);
		update_profile(points, enemy_lives, player_lives, SPACE); /* update profile on each iteration */

		remaining_lives(enemy_lives, player_lives); /* calculate remaining lives on each iteration */
	}
	remaining_lives(enemy_lives, --player_lives);
	gameover(points);
}


/******************************** TRAY MOVEMENT ******************************/

void movement(int *x, int *y, int *b_Xcoord, int *b_Ycoord, BOOL *fire) /* to move the tray with arrow keys */
{
	_getch();
	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (*x<MAX_XCOORD - 4)
			++*x;
	}
	else if (GetAsyncKeyState(VK_LEFT))
	{
		if (*x>MIN_XCOORD + 1)
			--*x;
	}
	else if (GetAsyncKeyState(VK_UP))
	{
		if (*y > MAX_YCOORD / 2)
			--*y;
	}
	else if (GetAsyncKeyState(VK_DOWN))
	{
		if (*y < MAX_YCOORD - 2)
			++*y;
	}
	else if (GetAsyncKeyState(VK_SPACE))
	{
		if (*fire == FALSE) /* one bullet should be fired at time */
		{
			*fire = TRUE;
			*b_Xcoord = *x;
		}
	}
	else if (GetAsyncKeyState(VK_ESCAPE))
		pause(SPACE);
}
/******************************** ENEMEY MOVEMENT ***************************/

void enemy_movement(int e_xcoord, int e_ycoord)
{
	static char e_ship[3][3] = { { 1, 1, 1 }, { 186, 186, 186 }, { 1, 1, 1 } };
	int i, j;

	color(252);
	for (i = 0; i < 3; i++)
	{
		PlaceCursor(e_xcoord, e_ycoord);
		for (j = 0; j < 3; j++)
		{
			printf("%c", e_ship[i][j]);
		}
		e_ycoord++;
	}
}

/****************************** FIRE BULLET ***************************/

void fire(int x, int y, BOOL *fire_b)
{
	if (y > MIN_YCOORD + 3) /* y should be greater than 4 */
	{
		if (y < MAX_YCOORD - 2)
			erase(x, y + 1); /* erasing the bullet from y+1 */

		color(244);
		PlaceCursor(x, y);
		printf("|");

		if (y == 4)  /* for erasing the last bullet*/
			erase(x, y);
	}
	else
		*fire_b = FALSE;
}
/******************************* BULLET HIT *****************************/
BOOL bullet_hit(int b_xcoord, int b_ycoord, int ship_xcoord, int ship_ycoord) /* check whether bullet hit the enemyship */
{
	if (((b_xcoord == ship_xcoord) || (b_xcoord == ship_xcoord + 1) || (b_xcoord == ship_xcoord + 2)) && (b_ycoord == ship_ycoord))
	{
		Beep(523, 100);
		return TRUE;
	}
	else
		return FALSE;
}
/***************************** ENEMY BOMB DROP **************************/

void bomb_drop(int bomb_xcoord, int bomb_ycoord) /* for droping bomb from random x coordinate */
{
	color(240);
	PlaceCursor(bomb_xcoord, bomb_ycoord);
	printf("%c", 2);
}

/****************************** CHECK BOMB HIT ***************************/

BOOL bomb_hit(int ship_x, int ship_y, int bomb_x, int bomb_y) /*check whether the bomb hit the players ship */
{
	if (((ship_x == bomb_x) || (ship_x + 1 == bomb_x) || (ship_x + 2 == bomb_x)) && (ship_y == bomb_y))
	{
		Beep(800, 100);
		return TRUE;
	}
	else
		return FALSE;
}
/****************************** CHECK LIVES ******************************/

BOOL checklives(int l, int e_l) /* check enemy and players lives */
{
	if (l == 0 || e_l == 0)
		return FALSE;
	else
		return TRUE;
}

/*************************** CALCULATING POINTS **************************/

void calculatepoints(int points)
{
	color(243);
	PlaceCursor(66, 18);
	printf(" POINTS ");

	PlaceCursor(68, 19);
	printf(" %d ", points);
}

/************************** REMAINING LIVES *****************************/

void remaining_lives(int e_l, int p_l)
{
	int i;
	static int e_lives = 6, p_lives = 3;
	static char enemylives[] = { 3, 3, 3, 3, 3, 3 };
	static char playerlives[] = { 3, 3, 3 };

	color(241);
	PlaceCursor(62, 26);
	printf(" REMAINING LIVES ");
	PlaceCursor(61, 28);
	printf("ENEMY LIVES:");
	PlaceCursor(67, 30);

	for (i = 0; i < 6; i++)
		printf("%c", enemylives[i]);

	PlaceCursor(61, 32);
	printf("PLAYER LIVES:");
	PlaceCursor(67, 34);

	for (i = 0; i < 3; i++)
		printf("%c", playerlives[i]);

	if (e_l <= 6)
		enemylives[e_l] = 32;

	if (p_l <= 3)
		playerlives[p_l] = 32;
}

/*************************** CONTROLS ***********************************/

void controls()
{
	color(246);
	PlaceCursor(65, 38);
	printf(" CONTROLS ");
	PlaceCursor(61, 41);
	printf("%c  UP", 24);
	PlaceCursor(61, 43);
	printf("%c  DOWN", 25);
	PlaceCursor(61, 45);
	printf("%c  LEFT", 27);
	PlaceCursor(70, 41);
	printf("%c   RIGHT", 26);
	PlaceCursor(70, 43);
	printf("%c%c%c FIRE", 192, 196, 217);
	PlaceCursor(70, 45);
	printf("Esc PAUSE");

}

/**************************** REMOVING FOOTPRINTS ***********************/

void erase(int x, int y) /* erasing x and y coordinates */
{
	PlaceCursor(x, y);
	printf(" ");
}

void erase_ship(int e_x, int e_y)
{
	int i;
	PlaceCursor(e_x, e_y);
	for (i = 0; i < 3; i++)
		printf(" ");
}

/******************************** TIMER **********************************/

void timer(int *hour, int *min, int *sec) /* for displaying the timer */
{
	color(252);
	PlaceCursor(67, 5);
	printf(" TIMER ");
	PlaceCursor(62, 6);
	printf(" H:M:S : %d: %d: %d ", *hour, *min, *sec);

	if (*min > 0 && *sec == 0)
	{
		*sec += 60;
		--*min;
	}
	if (*hour > 0 && *min == 0)
	{
		*min += 60;
		--hour;
	}
}


void pause(int game) /* for pausing the game when escape is pressed */
{

	int space;
	if (game == SPACE)
	{
		color(249);
		PlaceCursor(15, 10);
		for (space = 0; space < 25; space++)
			printf("%c", BLOCK);

		PlaceCursor(21, 10);
		printf(" GAME PAUSED ");

		PlaceCursor(14, 12);
		printf(" PRESS ESCAPE AGAIN TO CONTINUE. ");
		
		rewind(stdin);
		while (1)
		{
			_getch();  /* waiting for the user to press any key */
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
		}
		rewind(stdin);

		PlaceCursor(15, 10); /* clearing the screen */
		for (space = 1; space < 50; space++)
		{
			printf("  ");

			if (space % 20 == 0)
			{
				printf("\n");
				PlaceCursor(14, 12);
			}
		}
	}
	else if (game == SNAKE)
	{
		color(249);
		PlaceCursor(28, 41);
		for (space = 0; space < 25; space++)
			printf("%c", BLOCK);

		PlaceCursor(34, 41);
		printf(" GAME PAUSED ");

		PlaceCursor(27, 42);
		printf(" PRESS ESCAPE AGAIN TO CONTINUE. ");
		rewind(stdin);
		while (1)
		{
			_getch();  /* waiting for the user to press any key */
			if (GetAsyncKeyState(VK_ESCAPE))
				break;
		}
			rewind(stdin);

		PlaceCursor(28, 41); /* clearing the screen */
		for (space = 1; space < 160; space++)
		{
			printf("  ");
		}
	}
}

/******************************* GAMEOVER ********************************/

void gameover(int score) /* for pausing the game when escape is pressed */
{
	int space;
	color(249);
	PlaceCursor(15, 20);
	for (space = 0; space < 25; space++)
		printf("%c", BLOCK);

	PlaceCursor(21, 20);
	printf(" GAME OVER ");

	PlaceCursor(21, 22);
	printf(" SCORE : %d", score);

	PlaceCursor(9, 26);
	printf("  PRESS ESC TO GO BACK TO THE MENU.");

	while (1)  /* waiting for the user to ESCAPE key */
	{
		_getch();
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}

/**************************** ADD NEW PROFILE ***************************/

void add_new_profile() /*for making a new profile*/
{
	system("color F0");
	system("cls");
	color(249);
	boundary();
	int x = 5, y = 3;
	char again = 'y';
	if ((fptr = fopen("playersprofile.txt", "ab+")) == NULL)
	{
		PlaceCursor(x, y);
		printf("Unable to write data.");
	}
	else
	while (again == 'y' || again == 'Y')
	{
		fptr = fopen("playersprofile.txt", "ab+"); /*opening the file in ab+ so that new profile is added at the end*/
		PlaceCursor(x, y += 2);
		printf("Enter Name: ");
		scanf("%s", p.name);

		p.p_score = 0;
		p.enemy_lives_remaining = 0;
		p.players_lives_remaining = 0;
		p.snake_score = 0;

		fwrite(&p, sizeof(struct profile), 1, fptr); /*writing the details in the file */
		fclose(fptr);

		PlaceCursor(x, ++y);
		printf("Do you want to add another profile? (Y/N): ");
		scanf(" %c", &again);
	}
	menu();
}
/**************************** VIEW PROFILE ****************************/

void view_profiles() /*viewing or deleting different profiles */
{
	int i = 5, j = 8;
	system("cls");
	system("color F0");
	color(249);
	boundary();
	PlaceCursor(35, 0);
	printf(" STATISTICS ");
	PlaceCursor(3, 3);
	printf("- PRESS ESCAPE KEY TO GO BACK TO THE MENU.");
	PlaceCursor(3, 4);
	printf("- PRESS DELETE TO ENTER INTO DELETING MODE.");

	fptr = fopen("playersprofile.txt", "ab+");
	PlaceCursor(i, j);
	printf("%s\t%s\t%s\t%s\t%s", "Names", "Warrior Score", "Enemies left", "Player lives", "Snake Score");
	j++;

	while (fread(&p, sizeof(struct profile), 1, fptr) == 1) /*reading structure to structure */
	{
		{
			PlaceCursor(i, ++j);
			printf("%s\t%9d\t%11d\t%11d\t%11d\n", p.name, p.p_score, p.enemy_lives_remaining, p.players_lives_remaining, p.snake_score);
		}
	}
	fclose(fptr);

	while (1)
	{
		_getch();
		if (GetAsyncKeyState(VK_DELETE))
			delete_profile();
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}
/**************************** SELECT PROFILE **************************/

void select_profile(int z) /* for selecting a already made profile */
{
	int i = 5, j = 3;
	system("cls");
	system("color F0");
	color(249);
	boundary();
	PlaceCursor(i, j);
	printf("Enter name: ");
	scanf("%s", temp_name);

	fptr = fopen("playersprofile.txt", "rb");

	if ((fptr = fopen("playersprofile.txt", "rb")) == NULL)
	{
		PlaceCursor(i, ++j);
		printf("No profile found.");
		PlaceCursor(i, ++j);
		printf("Press SPACE to make a profile or press ESCAPE to go back to the menu.");
		while (1)
		{
			_getch();
			if (GetAsyncKeyState(VK_ESCAPE))
				menu();
			if (GetAsyncKeyState(VK_SPACE))
				add_new_profile();
		}
	}
	else
	{
		while ((fread(&p, sizeof(struct profile), 1, fptr)) == 1)
		{
			if (strcmp(p.name, temp_name) == 0)
			{
				loading(z);			//loading game. if z = SNAKE, snake is loaded, if SPACE, space invader loads
			}
		}
		PlaceCursor(i, ++j);
		printf("Make a profile first.");
		PlaceCursor(i, ++j);
		printf("Press SPACE to make a profile or press ESCAPE to go back to the menu.");

		while (1)
		{
			_getch();
			if (GetAsyncKeyState(VK_ESCAPE))
				menu();
			if (GetAsyncKeyState(VK_SPACE))
				add_new_profile();
		}
	}
}
/**************************** UPDATE PROFILE **************************/

void update_profile(int score, int enemylives, int playerlives, int game) /* Updating on score on each iteration */
{
	fptr = fopen("playersprofile.txt", "rb+"); /* Opening a file to update(read and write) in binary mode */

	while (fread(&p, sizeof(struct profile), 1, fptr) == 1)
	{
		if (strcmp(p.name, temp_name) == 0)
		{
			if (game == SPACE){			//update space invader score if game being played is SPACE INVADER
				p.p_score = score;
				p.enemy_lives_remaining = enemylives;
				p.players_lives_remaining = playerlives;
				fseek(fptr, ftell(fptr) - sizeof(struct profile), SEEK_SET);
				fwrite(&p, sizeof(struct profile), 1, fptr);
				fclose(fptr);
			}
			else if (game == SNAKE){		// update just GALACTIC SNAKE'S score if game eing played is snake
				p.snake_score = score;
				fseek(fptr, ftell(fptr) - sizeof(struct profile), SEEK_SET);
				fwrite(&p, sizeof(struct profile), 1, fptr);
				fclose(fptr);
			}
		}
	}
}

/**************************** DELETE PROFILE **************************/
void delete_profile() /* for deleting a profile */
{
	FILE *tempfptr;
	BOOL found = FALSE;

	fseek(fptr, 0, SEEK_SET);
	PlaceCursor(3, 5);
	printf("Enter the profile name to DELETE: ");
	scanf("%s", temp_name);

	fptr = fopen("playersprofile.txt", "rb+");
	tempfptr = fopen("temp.txt", "wb");

	while (fread(&p, sizeof(struct profile), 1, fptr) == 1) /* read th file and find the name entered */
	{
		if (strcmp(p.name, temp_name) == 0)
			found = TRUE;

		if (strcmp(p.name, temp_name) != 0)
			fwrite(&p, sizeof(struct profile), 1, tempfptr);
	}
	fclose(fptr);
	fclose(tempfptr);

	fptr = fopen("playersprofile.txt", "wb"); /*open file again and copy */
	tempfptr = fopen("temp.txt", "rb+");

	while (fread(&p, sizeof(struct profile), 1, tempfptr) == 1)
		fwrite(&p, sizeof(struct profile), 1, fptr);

	fclose(fptr);
	fclose(tempfptr);

	if (found == TRUE) /*if profile found and deleted */
	{
		PlaceCursor(3, 6);
		printf("Profile successfully deleted!");
	}
	else
	{
		PlaceCursor(3, 6);
		printf("No record found.");
	}

	while (1)
	{
		_getch();
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}
/*************************** PRINTING BACKGROUND **********************/

void print_background() /*printing a background with ASC2 176 */
{
	int  j;
	for (j = 0; j < 3920; j++)
		printf("%c", BKGRID);
}

/**************************  GAME BOUNDARY ***************************/

void game_boundary() /*for printing the menu boundry */
{
	int i, j;
	for (j = 0; j < MAX_YCOORD; j++)
	{
		for (i = 0; i < MAX_XCOORD; i++)
		{
			if ((i>0 && i< MAX_XCOORD - 1) && (j>0 && j < MAX_YCOORD - 1))
				printf(" ");
			else
			{
				PlaceCursor(i, j);
				printf("%c", BLOCK); /* 219 Asc2 for a block */
			}
		}
	}
	for (j = 0; j <= MAX_YCOORD; j += 12) /* making seprate boxes */
	{
		for (i = MAX_XCOORD; i < MAX_XCOORD + 20; i++)
		{
			PlaceCursor(i, j);
			printf("%c", BLOCK);
		}
	}
	PlaceCursor(0, 0);
}

/****************************** MENU BOUNDARY ******************************/
void boundary()
{
	int i, j;
	for (j = 0; j < MAX_YCOORD; j++) /* MAX_YCOORD 50 */
	{
		for (i = 0; i < MAX_XCOORD + 20; i++) /*MAX_XCOORD 60 */
		{
			if ((i>0 && i< MAX_XCOORD + 19) && (j>0 && j < MAX_YCOORD - 1))
				continue;
			else
			{
				PlaceCursor(i, j);
				printf("%c", BLOCK); /* 219 Asc2 for a block */
			}
		}
	}
	PlaceCursor(0, 0);
}
/****************************  HELP AND CREDITS *****************************/
void help_credits()
{
	system("cls");
	system("color F0");
	color(249);

	print_background();
	boundary();

	int xcoordinate = MAX_XCOORD - 30, ycoordinate = MAX_YCOORD - 40;

	PlaceCursor(30, 0);
	printf(" HELP AND CREDITS "); /* simply printing at specific coordinates */
	PlaceCursor(xcoordinate, ycoordinate -= 3);
	printf(" GALACTIC INVADERS%c ", 169);
	PlaceCursor(xcoordinate += 3, ++ycoordinate);
	printf(" Version 1.0 ");
	PlaceCursor(xcoordinate -= 8, ++ycoordinate);
	printf(" 2013, All Rights Reserved. ");
	PlaceCursor(xcoordinate -= 20, ycoordinate += 6);
	printf(" PROGRAMMED BY: ");
	PlaceCursor(xcoordinate += 6, ycoordinate += 2);
	printf(" - Raza Yunus ");
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" - Moaz Khan  ");
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" - Emad Ehsan ");
	PlaceCursor(xcoordinate -= 6, ycoordinate += 4);
	printf(" HOW TO PLAY: ");
	PlaceCursor(xcoordinate += 4, ycoordinate += 2);
	printf(" For Galactic Warrior: Kill the enemy within the time limit. ");
	PlaceCursor(xcoordinate, ycoordinate += 1);
	printf(" Shoot the enemy to gain points and try to avoid the bombs. ");
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" For Galactic Snake: Avoid the boundary and your own tail and ");
	PlaceCursor(xcoordinate, ycoordinate += 1);
	printf(" eat as many hearts as you can for points. ");
	PlaceCursor(xcoordinate -= 4, ycoordinate += 4);
	printf(" CONTROLS: ");
	PlaceCursor(xcoordinate += 8, ycoordinate += 3);
	printf(" %c\tUP   ", 24);
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" %c\tDOWN ", 25);
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" %c\tLEFT ", 27);
	PlaceCursor(xcoordinate += 30, ycoordinate -= 4);
	printf(" %c\t RIGHT ", 26);
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" %c%c%c\t FIRE  ", 192, 196, 217);
	PlaceCursor(xcoordinate, ycoordinate += 2);
	printf(" Esc\t PAUSE ");
	PlaceCursor(xcoordinate -= 38, ycoordinate += 5);
	printf(" - PRESS ESCAPE TO GO BACK TO THE MENU. ");
	PlaceCursor(79, 48);

	while (1)
	{
		_getch();
		if (GetAsyncKeyState(VK_ESCAPE))
			menu();
	}
}

void exit_game()
{
	system("cls");
	system("color F0");

	int xcoordinate = MAX_XCOORD - 23, ycoordinate = MAX_YCOORD - 28;
	color(249);
	boundary();
	PlaceCursor(20, 19);
	printf(" Are you sure you want to exit the game? ");
	PlaceCursor(xcoordinate, ycoordinate);

	while (1)
	{
		if (ycoordinate == 21) /*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(37, 21);
			printf(" Yes ");
		}
		else
		{
			color(249);
			PlaceCursor(37, 21);
			printf(" Yes ");
		}
		if (ycoordinate == 23) /*if this coordinate then the color is blue otherwise white*/
		{
			color(159);
			PlaceCursor(37, 23);
			printf(" No ");
		}
		else
		{
			color(249);
			PlaceCursor(37, 23);
			printf(" No ");
		}
		PlaceCursor(79, 48);
		_getch();
		if (GetAsyncKeyState(VK_UP) && ycoordinate > 21)
			PlaceCursor(xcoordinate, --ycoordinate);
		if (GetAsyncKeyState(VK_DOWN) && ycoordinate < 23)
			PlaceCursor(xcoordinate, ++ycoordinate);
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 20 && ycoordinate < 22) /* if yes and enter is pressed exit */
			exit(0);
		if (GetAsyncKeyState(VK_RETURN) && ycoordinate > 22 && ycoordinate < 24)
			menu();
	}
}

/****************************** COLOR *************************************/

void color(int x) /*differet console colors */
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(handle, x);
}

/************************ PLACING CURSOR ON THE SCREEN ********************/

void PlaceCursor(int x, int y) /* placing cursor at x and y coordinates */
{
	COORD c;
	c.X = x;
	c.Y = y;

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);
}

/**************************** SET WINDOW SIZE ****************************/

void setwindowsize(int height, int width) /* placing cursor at x and y coordinates */
{
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);

	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, height, width, TRUE);
}
