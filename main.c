#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <raylib.h>
#include <stdbool.h>

#define MINES 10
#define ROWS 8
#define COLS 8
#define BOXES (ROWS * COLS)
#define WIDTH 350
#define HEIGHT 400
#define SIZE 25

#define REDC "\033[31m"
#define BLUEC "\033[34m"
#define GREENC "\033[32m"
#define RESET "\033[0m"

int cont = 0;

int *minePositions(void);
int *possiblePos(int pst);
char findMines(char *board, int pst);
char *boardMaker(char *board);
char *newBoardMaker(char *board, int pst);
void resetBoard(char *board);
void panelDrawing(char *board);
void youLose(void);
void printBoard(char *board);
void result(char *text, Color bg, Color fg);
void floodFill(int i, Rectangle box[BOXES], char *board);

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


void panelDrawing(char *board)
{
	SetTargetFPS(60);
  InitWindow(WIDTH, HEIGHT, "Minesweeper");
	int boxClicked[BOXES] = {0};
	int exit = 1;
	char str[3];
	str[0] = ' ';
	str[2] = '\0';

  Color color = GRAY;
  Rectangle box[BOXES];

  for (int i = 0; i < BOXES; i++) {
    box[i].x = 64.5 + (i % COLS) * (SIZE+3);
    box[i].y = 80 +  (i / COLS) * (SIZE+3);
    box[i].width = SIZE;
    box[i].height = SIZE;
  }

	int place; // posicion donde hay un 0
	bool find = false;

  while (!WindowShouldClose() && exit) {
    BeginDrawing();
    ClearBackground(LIGHTGRAY);

    for (int i = 0; i < BOXES; i++) {
      DrawRectangleRec(box[i], color);
			if (board[i] == ' ' && !find) {
				place = i;
				find = true;
			}
		}
		
		DrawRectangleRec(box[place], VIOLET);

    for (int i = 0; i < BOXES; i++) {
			str[1] = board[i];

      if (CheckCollisionPointRec(GetMousePosition(), box[i]) && 
					IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !boxClicked[i]) 
			{
				boxClicked[i] = 1;
				cont++;
				printf("cont: %d\n", cont);
			}

			if (boxClicked[i]) {
				if (str[1] == 'M') {
					DrawText(str, box[i].x, box[i].y, 20, RED);
					exit = 0;
				}
				else if (str[1] == ' ') floodFill(i, box, board);
				else DrawText(str, box[i].x, box[i].y, 20, WHITE);

			}
    }

    EndDrawing();

		if (exit == 0) {
			WaitTime(0.5);
			result("You Lose", RED, GREEN);
		}

		if (cont == 54) {
			WaitTime(0.5);
			exit = 0;
			result("You Win", GREEN, RED);
		}
  }

  CloseWindow();
}

int *minePositions(void)
{
  srand(9);
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

void result(char *text, Color bg, Color fg)
{
  InitWindow(800, 450, text);
	Rectangle exitRect[1];

	int check = 0;
	int exit = 1;

	exitRect[0].x = 375 + (0 % COLS) * (SIZE+3);
	exitRect[0].y = 280 +  (0 / COLS) * (SIZE+3);
	exitRect[0].width = 53;
	exitRect[0].height = 20;

  while (!WindowShouldClose() && exit) {
    BeginDrawing();
    ClearBackground(bg);

		DrawText(text, 330, 200, 30, fg);
		DrawRectangleRec(exitRect[0], LIGHTGRAY);
		DrawText(" Exit", exitRect[0].x, exitRect[0].y, 20, BLACK);

		if (CheckCollisionPointRec(GetMousePosition(), exitRect[0]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
			check = 1;

		if (check) {
			exit = 0;
		}

    EndDrawing();
  }

}

void printBoard(char *board)
{
	int k = 0;

	printf("|---|---|---|---|---|---|---|---|\n");
	for (int i = 0; i < 8; i++)
	{
		printf("|");
		for (int j = 0; j < 8; j++)
		{
			if (board[k] == ' ')
				printf(" %c %s", board[k], RESET);
			else if (board[k] == 'M')
				printf(" %s%c %s", REDC, board[k], RESET);
			else 
				printf(" %s%c %s", BLUEC, board[k], RESET);
			printf("|");
			k++;
		}
		printf("\n");
		printf("|---|---|---|---|---|---|---|---|\n");
	}
}

int *possiblePos(int pst)
{
	int *numsToAdd = calloc(8, sizeof(int));

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

// ugly ass function, i need to rewrite but idk how 
void floodFill(int i, Rectangle box[BOXES], char *board) {
	int *positions = possiblePos(i);
	int length = 0;

	while (positions[length] != 0) length++;

	DrawRectangleRec(box[i], DARKGRAY);

	for (int j = 0; j < length; j++) {
		int i2 = i + positions[j];

		if (board[i2] == ' ') {
			int *positions2 = possiblePos(i2);
			int length2 = 0;

			while (positions2[length2] != 0) length2++;

			DrawRectangleRec(box[i2], DARKGRAY);

			for (int j2 = 0; j2 < length2; j2++) {
				int i3 = i2 + positions2[j2];

				if (board[i3] == ' ') {
					int *positions3 = possiblePos(i3);
					int length3 = 0;

					while (positions3[length3] != 0) length3++;

					DrawRectangleRec(box[i3], DARKGRAY);

					for (int j3 = 0; j3 < length3; j3++) {
						int i4 = i3 + positions3[j3];

						if (board[i4] == ' ') {
							int *positions4 = possiblePos(i4);
							int length4 = 0;

							while (positions4[length4] != 0) length4++;

							DrawRectangleRec(box[i4], DARKGRAY);

							for (int j4 = 0; j4 < length4; j4++) {
								int i5 = i4 + positions4[j4];

								if (board[i5] == ' ') {
									DrawRectangleRec(box[i5], DARKGRAY);
									int *positions5 = possiblePos(i5);
									int length5 = 0;

									while (positions5[length5] != 0) length5++;

									for (int j5 = 0; j5 < length5; j5++) {
										int i6 = i5 + positions5[j5];

										if (board[i6] == ' ') {
											DrawRectangleRec(box[i6], DARKGRAY);
										} else if (board[i6] != 'M') {
												char str[3] = { ' ', board[i6], '\0' };
												DrawText(str, box[i6].x, box[i6].y, 20, WHITE);
										}
									}
								} else if (board[i5] != 'M') {
										char str[3] = { ' ', board[i5], '\0' };
										DrawText(str, box[i5].x, box[i5].y, 20, WHITE);
								}
							}
						} else if (board[i4] != 'M') {
								char str[3] = { ' ', board[i4], '\0' };
								DrawText(str, box[i4].x, box[i4].y, 20, WHITE);
						}
					}
				} else if (board[i3] != 'M') {
						char str[3] = { ' ', board[i3], '\0' };
						DrawText(str, box[i3].x, box[i3].y, 20, WHITE);
				}
			}
		} else {
				char str[3] = { ' ', board[i2], '\0' };
				DrawText(str, box[i2].x, box[i2].y, 20, WHITE);
		}
	}

	free(positions);
}
