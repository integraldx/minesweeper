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
	printf("does it run?\n");
	system("pause");
	return 0;
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

int sweep(int x, int y)
{
	// TODO
}

int check_game()
{
	// TODO
}
