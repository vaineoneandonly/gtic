all:
	gcc gtic.c -o gtic -Lsrc/Include -Lsrc/lib -lmingw32 -lSDL2main -lSDL2
