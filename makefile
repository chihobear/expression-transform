jdec:main.o linkedStack.o tree.o
	gcc -Wall main.o linkedStack.o tree.o -o jdec
main.o:main.c linkedStack.h tree.h
	gcc -Wall -c main.c -o main.o
linkedStack.o:linkedStack.c linkedStack.h tree.h
	gcc -Wall -c linkedStack.c -o linkedStack.o
tree.o:tree.c tree.h
	gcc -Wall -c tree.c -o tree.o
.Phony:clean
clean:
	rm -f *.o jdec
