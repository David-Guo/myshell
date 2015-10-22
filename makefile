main: 
	gcc -Wall -g -o mysh sh.c
	gcc -Wall -o prog prog.c
clean:
	rm mysh
