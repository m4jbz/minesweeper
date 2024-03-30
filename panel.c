#include <raylib.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ROWS 8
#define COLS 8
#define BOXES (ROWS * COLS)
#define WIDTH 350
#define HEIGHT 400
#define SIZE 25

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "Minesweeper");
	bool boxClicked[BOXES] = {false};

	char MS[BOXES];

	// Semilla para números aleatorios
	srand(time(NULL));

	// Llenar con 'Q'
	for (int i = 0; i < 10; ++i) {
			MS[i] = 'Q';
	}

	// Llenar con números del 1 al 4
	for (int i = 10; i < BOXES; ++i) {
			MS[i] = '0' + (rand() % 4) + 1;
	}

  Color color = RED;
  Rectangle box[BOXES];

  for (int i = 0; i < BOXES; i++) {
    box[i].x = 64.5 + (i % COLS) * (SIZE+3);
    box[i].y = 80 +  (i / COLS) * (SIZE+3); // no hacer caso al warning
    box[i].width = SIZE;
    box[i].height = SIZE;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKPURPLE);

    for (int i = 0; i < BOXES; i++)
      DrawRectangleRec(box[i], color);

    for (int i = 0; i < BOXES; i++) {

			char str[2];
			str[0] = MS[i];
			str[1] = '\0';

      if (CheckCollisionPointRec(GetMousePosition(), box[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
				boxClicked[i] = true;

			if (boxClicked[i])
				DrawText(str, box[i].x, box[i].y, 20, WHITE);
    }

    EndDrawing();
  }

  CloseWindow();

	return 0;
}
