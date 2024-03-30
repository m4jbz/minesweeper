default:
	gcc -o main main.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra
	./main

panel:
	gcc -o panel panel.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -Wall -Wextra
	./panel

.PHONY: panel
