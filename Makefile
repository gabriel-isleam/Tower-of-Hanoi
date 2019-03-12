build: main.o functions.o header.h
	gcc -Wall main.o functions.o -o tema2

main.o: main.c
	gcc -Wall -c main.c

functions.o: functions.c
	gcc -Wall -c functions.c

run: tema2
	./tema2 test.in test.out

clean: 
	rm tema2 main.o functions.o test.out
