output: main.o avl.o
	gcc -Wall -Wextra -Werror -Wpedantic main.o avl.o -o output

main.o: main.c
	gcc -Wall -Wextra -Werror -Wpedantic -c main.c

avl.o: avl.c
	gcc -Wall -Wextra -Werror -Wpedantic -c avl.c

clean:
	rm *.o output
