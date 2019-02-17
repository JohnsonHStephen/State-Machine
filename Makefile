CC = g++

OBJS = main.o app.o
OBJ_FOLDER = src/
HEADER_FOLDER = src/header/

SDL_FLAGS = -ID:\Programs\MinGW\SDL2_mingw_32\include -LD:\Programs\MinGW\SDL2_mingw_32\lib -lSDL2main -lSDL2

HEADER_INCLUDES = -I./src/header

OUTFILE = main.exe

All: $(OBJS)
	$(CC) $(SDL_FLAGS) -o $(OUTFILE) $(OBJS)
	$(document)clear_o

main.o: main.cpp
	$(CC) -c main.cpp

app.o: app.cpp app.h
	$(CC) $(HEADER_INCLUDES) $(SDL_FLAGS) -c app.cpp

clear: clear_o
	del /f *.exe

clear_o:
	del /f *.o
