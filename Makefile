jeu:main.o ai.o
	gcc main.o ai.o -o jeu -lm -ldl -lSDL -lSDL_image -lSDL_ttf -lSDL_mixer -g
Main.o:main.c
	gcc -lSDL -lSDL_image -lSDL_ttf -c main.c -w

ai.o:ai.c
	gcc -lSDL -lSDL_image -lSDL_ttf -c ai.c -w

