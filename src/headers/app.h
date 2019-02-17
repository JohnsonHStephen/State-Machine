#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <vector>

class state;

class app {
Public:
    app();
    ~app();
    
    int init(const char* title, int width = 1920, int height = 1080, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    int cleanup();
    
    int changeState(State* state);
    int pushState(State* state);
    int popState();
    
    int handleEvents();
    int update();
    int draw();
    
    bool running() { return running; };
    void quit() { running = false; };
Private:
    vector<State*> states;
    
    bool running;
    
    SDL_Window window;
Protected:
    
}

#endif
