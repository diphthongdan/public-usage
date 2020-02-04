all: first
first: first.c
	gcc -g -fsanitize=address -std=c11 -Wall -Werror first.c -o first
clean:
	rm -f first
