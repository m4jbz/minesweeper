#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define PLACES 64
#define MINES 10
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

int *minePositions();
int *boardMaker(int *board);
void printBoard(int *board);
void resetBoard(int *board);
void cleanTerm();

int main()
{
	int *board = calloc(PLACES, sizeof(int));
	int boardNumber = 0;

	while (1)
	{
		cleanTerm();
		printf("Board N° %d\n", boardNumber);
		printBoard(boardMaker(board));
		resetBoard(board);
		boardNumber++;
		sleep(2);
	}
	return 0;
}

int *boardMaker(int *board)
{
	int *numbers = minePositions();

	for (int i = 0; i < 10; i++)
	{
		board[numbers[i]] = 1;
	}

	return board;

	free(numbers);
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

void printBoard(int *board) 
{
	int k = 0;

	printf("%*s|---|---|---|---|---|---|---|---|\n", 55, "");
	for (int i = 0; i < 8; i++)
	{
		printf("%*s|", 55, "");
		for (int j = 0; j < 8; j++)
		{
			if (board[k] == 0)
				printf(" %s%d %s", RED, board[k], RESET);
			else 
				printf(" %s%d %s", GREEN, board[k], RESET);
			printf("|");
			k++;
		}
		printf("\n");
		printf("%*s|---|---|---|---|---|---|---|---|\n", 55, "");
	}
}

void resetBoard(int *board) {
	for (int i = 0; i < PLACES; i++) {
		board[i] = 0;
	}
}

void cleanTerm()
{
	system("clear");
}
