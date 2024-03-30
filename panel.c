#include <raylib.h>
#include <stdio.h>

#define ROWS 8
#define COLS 8
#define BOXES (ROWS * COLS)
#define WIDTH 350
#define HEIGHT 450
#define SIZE 25

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "Minesweeper");

  Color color = LIGHTGRAY;
  Rectangle box[BOXES];

  for (int i = 0; i < BOXES; i++) {
    box[i].x = 64.5 + (i % COLS) * (SIZE+3);
    box[i].y = 100 +  (i / COLS) * (SIZE+3);
    box[i].width = SIZE;
    box[i].height = SIZE;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(GRAY);

    for (int i = 0; i < BOXES; i++)
      DrawRectangleRec(box[i], color);

    for (int i = 0; i < BOXES; i++) {
      if (CheckCollisionPointRec(GetMousePosition(), box[i]) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        printf("La casilla fue presionada\n");
    }

    EndDrawing();
  }

  CloseWindow();

	return 0;
}
