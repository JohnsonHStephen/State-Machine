CC = g++

OBJS = main.o app.o
OBJ_FOLDER = src/
HEADER_FOLDER = src/headers/

SDL_FLAGS = -ID:\Programs\MinGW\SDL2_mingw_32\include\SDL2 -LD:\Programs\MinGW\SDL2_mingw_32\lib -lmingw32 -lSDL2main -lSDL2

HEADER_INCLUDES = -I./src/headers

OUTFILE = main.exe

All: $(OBJS)
	$(CC) -o $(OUTFILE) $(OBJS) $(SDL_FLAGS)
	$(MAKE) clean_o

main.o: $(OBJ_FOLDER)main.cpp
	$(CC) -c $(OBJ_FOLDER)main.cpp

app.o: $(OBJ_FOLDER)app.cpp $(HEADER_FOLDER)app.h
	$(CC) $(HEADER_INCLUDES) -c $(OBJ_FOLDER)app.cpp $(SDL_FLAGS)

clean: clean_o
	del /f *.exe

clean_o:
	del /f *.o
