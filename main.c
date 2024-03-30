#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <raylib.h>

#define MINES 10
#define ROWS 8
#define COLS 8
#define BOXES (ROWS * COLS)
#define WIDTH 350
#define HEIGHT 400
#define SIZE 25

int *minePositions(void);
int *possiblePos(int pst);
char findMines(char *board, int pst);
char *boardMaker(char *board);
char *newBoardMaker(char *board, int pst);
void resetBoard(char *board);
void panelDrawing(char *board);

void panelDrawing(char *board)
{
  InitWindow(WIDTH, HEIGHT, "Minesweeper");
	int boxClicked[BOXES] = {0};
	int exit = 1;

  Color color = GRAY;
  Rectangle box[BOXES];

  for (int i = 0; i < BOXES; i++) {
    box[i].x = 64.5 + (i % COLS) * (SIZE+3);
    box[i].y = 80 +  (i / COLS) * (SIZE+3);
    box[i].width = SIZE;
    box[i].height = SIZE;
  }

  while (exit) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int i = 0; i < BOXES; i++)
      DrawRectangleRec(box[i], color);

    for (int i = 0; i < BOXES; i++) {
			char str[3];
			str[0] = ' ';
			str[1] = board[i];
			str[2] = '\0';

      if (CheckCollisionPointRec(GetMousePosition(), box[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				boxClicked[i] = 1;

			if (boxClicked[i]) {
				if (str[1] == 'M') exit = 0;
				else DrawText(str, box[i].x, box[i].y, 20, WHITE);
			}
    }

    EndDrawing();
  }

  CloseWindow();

}

int main(void)
{
	char *board = calloc(BOXES, sizeof(int));

	resetBoard(board);
	boardMaker(board);

	for (int i = 0; i < BOXES; i++)
		newBoardMaker(board, i);
	
	panelDrawing(board);

	free(board);
	return 0;
}

char *boardMaker(char *board)
{
	int *numbers = minePositions();

	for (int i = 0; i < MINES; i++)
		board[numbers[i]] = 'M';

	return board;
	free(numbers);
}

int *minePositions(void)
{
	srand(time(0));
	int *mines = malloc(MINES * sizeof(int));

	for (int i = 0; i < 10; i++) {
		int newNumber;
		int repeated;

		do {
			repeated = 0;  
			newNumber = rand() % BOXES;  

			for (int j = 0; j < i; j++)
				if (mines[j] == newNumber)
				{
					repeated = 1;  
					break;
				}
		} while (repeated);
		mines[i] = newNumber;
	}

	return mines;

	free(mines);
}

char findMines(char *board, int pst)
{
	int mines = 0;
	if (board[pst] != 'M') {
		for (size_t i = 0; i < sizeof(possiblePos(pst)); i++) {
			if (board[pst + possiblePos(pst)[i]] == 'M') mines++;
		}
		if (mines == 0) return ' ';
		else return mines + '0';
	}
	return 'M';
}

char *newBoardMaker(char *board, int pst)
{
	if (board[pst] == ' ')
		board[pst] = findMines(board, pst);
	return board;
}

void resetBoard(char *board) {
	for (int i = 0; i < BOXES; i++)
		board[i] = ' ';
}

int *possiblePos(int pst)
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
			numsToAdd[1] = 1; numsToAdd[2] = 7;
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
