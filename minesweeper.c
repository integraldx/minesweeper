#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE		10
#define SQUARE_NUM		(BOARD_SIZE*BOARD_SIZE)
#define MINE_NUM		17
#define SHUFFLE_NUM		100000
#define true			1

int mine_board[BOARD_SIZE][BOARD_SIZE];
/* 0 : non-mined, 1 : mined */

int display_board[BOARD_SIZE][BOARD_SIZE];
/* -1 : no mines around, 0 : unknown, 1~8 : number of mines */

void init_board(); // initialize mine_board by randomly planting fixed number of mines
void show_interface(); // print display_board
int sweep(int x, int y);
/*
 * sweep a square on (x, y). if there is no mines around square on (x, y), recursively sweep adjacent squares
 * return : 1 if player sweeps mined square, else 0
 */

int check_game(); 
/*
 * check if the player swept all non-mined squares
 * return : 1 if player swept all non-mined squares, else 0
 */

int main(void)
{
	int x, y;
	init_board();
	while (true) {
		show_interface();
		printf("input coordinates : ");
		scanf_s("%d %d", &x, &y);
		if (sweep(y - 1, x - 1 )) {
			printf("kaboom!");
			return 0;
		}
		if (check_game()) {
			printf("clear!");
			return 0;
		}
	}
	// TODO
}

void init_board()
{
	int i;
	int shuffle[BOARD_SIZE * BOARD_SIZE];
	int temp;
	int r1, r2;

	srand(time(NULL)); // set seed

	// initialize shuffle array
	for(i=0; i<SQUARE_NUM; i++)
		shuffle[i] = i;

	// shuffling
	for(i=0; i<SHUFFLE_NUM; i++)
	{
		r1 = rand() % SQUARE_NUM;
		r2 = rand() % SQUARE_NUM;

		temp = shuffle[r1];
		shuffle[r1] = shuffle[r2];
		shuffle[r2] = temp;
	}

	// get mine coordinates from shuffled array
	for(i=0; i<MINE_NUM; i++)
		mine_board[shuffle[i]/BOARD_SIZE][shuffle[i]%BOARD_SIZE] = 1;
}

void show_interface()
{
	int i, j;

	system("clear"); // clear the screen

	// rest of this function just prints out display_board
	printf("    ");
	for(i=0; i<BOARD_SIZE; i++)
		printf(" %2d ", i+1);
	printf("-> X\n");

	for(i=0; i<BOARD_SIZE; i++)
	{
		printf("\n %2d ", i+1);

		for(j=0; j<BOARD_SIZE; j++)
		{
			if(display_board[i][j] == -1)
			{
				if(mine_board[i][j] == 1)
					printf("  * ");
				else
					printf("  X ");
			}
			else if(display_board[i][j] == 0)
				printf("  - ");
			else
				printf("  %d ", display_board[i][j]);
		}
		printf("\n");
	}
	printf("\n  |\n  v\n\n  Y\n\n");
}

int sweep(int y, int x)
{
	// TODO
	int i, j;
	int count = 0;
	if (x < 0 || x > 9 || y < 0 || y > 9) {
		return 0;
	}
	if (mine_board[y][x] == 1) {
		return 1;
	}
	for (i = -1; i < 2; i++) {
		for (j = -1; j < 2; j++) {
			if ((y - i > -1) && (x - j > -1) && (y - i < 10) && (x - j < 10) && (mine_board[y - i][x - j] == 1)) {
				count++;
			}
		}
	}
	if (count == 0) {
		display_board[y][x] = -1;
		for (i = -1; i < 2; i++) {
			for (j = -1; j < 2; j++) {
				if (!(display_board[y - i][x - j] == -1)) {
					if (i != 0 || j != 0) {
						sweep(y - i, x - j);
					}
				}
			}
		}
	}
	else {
		display_board[y][x] = count;
	}
	return 0;
}

int check_game()
{
	// TODO
	int i, j;
	int count = 0;
	printf("checking...\n");
	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (display_board[i][j] == 0) {
				count++;
			}
		}
	}
	if (count == MINE_NUM) {
		return 1;
	}
	return 0;
}
