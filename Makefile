CC = gcc

all: mutex

mutex: main.c
	gcc -pthread -o mutex main.c -W -Wall -pedantic

.PHONY: clean run

run:
	./mutex

clean:
	rm -rf mutex