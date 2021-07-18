myset: myset.o set.o stringanalyzed.o
	gcc -g myset.o set.o stringanalyzed.o -o myset
myset.o: myset.c
	gcc -c -g myset.c -ansi -Wall -pedantic -o myset.o
set.o: set.c set.h
	gcc -c -g set.c -ansi -Wall -pedantic -o set.o
stringanalyzed.o: stringanalyzed.c stringanalyzed.h
	gcc -c -g stringanalyzed.c -ansi -Wall -pedantic -o stringanalyzed.o
