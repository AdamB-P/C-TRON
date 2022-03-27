TRON: TRON.o tLib.o
	gcc -g TRON.o tLib.o -o TRON -lncurses -g
TRON.o: TRON.c
	gcc -g -c TRON.c -o TRON.o
tLib.o: tLib.c tLib.h
	gcc -g -c tLib.c -o tLib.o
clean:
	rm -rf *.o
	rm TRON