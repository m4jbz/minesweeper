#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define POSITIONS 64
#define MINES 10
// Colors
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int *minePositions();
int possiblePos(char *board);
char *boardMaker(char *board);
void printBoard(char *board);
void resetBoard(char *board);
void cleanTerm();

int main()
{
	char *board = calloc(POSITIONS, sizeof(int));
	resetBoard(board);

	while (1)
	{
		cleanTerm();
		printBoard(boardMaker(board));
		resetBoard(board);
		sleep(2);
	}
	return 0;
	free(board);
}

char *boardMaker(char *board)
{
	int *numbers = minePositions();

	for (int i = 0; i < 10; i++)
		board[numbers[i]] = 'Q';

	return board;
	free(numbers);
}

int possiblePos(char *board)
{
	for (int i = 0; i < POSITIONS; i++)
	{
		if (board[i] != 'Q')
		{
			if (i == 0 || i == 7 || i == 56 || i == 63)
				return 3;
			else if (i % 8 == 0 || i % 8 == 7 || i < 8 || i > 55)
				return 5;
			else
				return 8;
		}
	}
	return 0;
}

int* minePositions()
{
	srand(time(NULL));
	int *array = malloc(10 * sizeof(int));

	for (int i = 0; i < 10; i++) {
		int nuevoNumero;
		int repetido;

		do {
			repetido = 0;  
			nuevoNumero = rand() % 64;  

			for (int j = 0; j < i; j++) {
				if (array[j] == nuevoNumero) {
					repetido = 1;  
					break;
				}
			}
		} while (repetido);
		array[i] = nuevoNumero;
	}

	return array;

	free(array);
}

void printBoard(char *board) 
{
	int k = 0;

	printf("%*s|---|---|---|---|---|---|---|---|\n", 55, "");
	for (int i = 0; i < 8; i++)
	{
		printf("%*s|", 55, "");
		for (int j = 0; j < 8; j++)
		{
			if (board[k] == ' ')
				printf(" %s%c %s", RED, board[k], RESET);
			else if (board[k] == 'Q')
				printf(" %s%c %s", GREEN, board[k], RESET);
			else 
				printf(" %s%c %s", BLUE, board[k], RESET);
			printf("|");
			k++;
		}
		printf("\n");
		printf("%*s|---|---|---|---|---|---|---|---|\n", 55, "");
	}
}

void resetBoard(char *board) {
	for (int i = 0; i < POSITIONS; i++)
		board[i] = ' ';
}

void cleanTerm()
{
	system("clear");
}
