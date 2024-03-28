default:
	gcc -o main main.c 
	./main

test:
	gcc test.c -o test
	./test
