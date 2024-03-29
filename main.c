#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define POSITIONS 64
#define MINES 10
/* Colors */
#define RED "\033[31m"
#define BLUE "\033[34m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

char findMines(char *board, int pst);
int *minePositions();
int *possiblePos(char *board, int pst);
char *boardMaker(char *board);
char *newBoardMaker(char *board, int pst);
void printBoard(char *board);
void resetBoard(char *board);
void cleanTerm();

int main()
{
	char *board = calloc(POSITIONS, sizeof(int));
	resetBoard(board);

	cleanTerm();
	boardMaker(board);
	for (int i = 0; i < POSITIONS; i++)
	{
		newBoardMaker(board, i);
	}
	printBoard(board);

	return 0;
	free(board);
}

char findMines(char *board, int pst)
{
	int mines = 0;
	if (board[pst] == 'Q')
		return 'Q';
	else
	{
		for (int i = 0; i < sizeof(possiblePos(board, pst)); i++)
			if (board[pst + possiblePos(board, pst)[i]] == 'Q')
				mines++;
		if (mines == 0)
			return ' ';
		else 
			return mines + '0';
	}
}

char *newBoardMaker(char *board, int pst)
{
	if (board[pst] == ' ')
		board[pst] = findMines(board, pst);
	return board;
}

char *boardMaker(char *board)
{
	int *numbers = minePositions();

	for (int i = 0; i < 10; i++)
		board[numbers[i]] = 'Q';

	return board;
	free(numbers);
}

int* minePositions()
{
	srand(time(0));
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
				printf(" %c %s", board[k], RESET);
			else if (board[k] == 'Q')
				printf(" %s%c %s", RED, board[k], RESET);
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

int *possiblePos(char *board, int pst)
{
	int *numsToAdd = malloc(8 * sizeof(int));

	switch (pst)
	{
		case 0:
			numsToAdd[0] = 1;
			numsToAdd[1] = 8;
			numsToAdd[2] = 9;
			break;
		case 7: 
			numsToAdd[0] = -1;
			numsToAdd[1] = 7;
			numsToAdd[2] = 8;
			break;
		case 56:
			numsToAdd[0] = -8;
			numsToAdd[1] = -7;
			numsToAdd[2] = 1;
			break;
		case 63:
			numsToAdd[0] = -9;
			numsToAdd[1] = -8;
			numsToAdd[2] = -1;
			break;
		case 1:
		case 2:
		case 3:
		case 4: 
		case 5:
		case 6: 
			numsToAdd[0] = -1;
			numsToAdd[1] = 1;
			numsToAdd[2] = 7;
			numsToAdd[3] = 8;
			numsToAdd[4] = 9;
			break;
		case 57:
		case 58:
		case 59:
		case 60:
		case 61:
		case 62:
			numsToAdd[0] = -9;
			numsToAdd[1] = -8;
			numsToAdd[2] = -7;
			numsToAdd[3] = -1;
			numsToAdd[4] = 1;
			break;
		case 8: 
		case 16:
		case 24:
		case 32:
		case 40:
		case 48:
			numsToAdd[0] = -8;
			numsToAdd[1] = -7;
			numsToAdd[2] = 1;
			numsToAdd[3] = 8;
			numsToAdd[4] = 9;
			break;
		case 15:
		case 23:
		case 31:
		case 39:
		case 47:
		case 55: 
			numsToAdd[0] = -9;
			numsToAdd[1] = -8;
			numsToAdd[2] = -1;
			numsToAdd[3] = 7;
			numsToAdd[4] = 8;
			break;
		default:
			numsToAdd[0] = -9;
			numsToAdd[1] = -8;
			numsToAdd[2] = -7;
			numsToAdd[3] = -1;
			numsToAdd[4] = 1;
			numsToAdd[5] = 7;
			numsToAdd[6] = 8;
			numsToAdd[7] = 9;
	}

	return numsToAdd;
	free(numsToAdd);
}
