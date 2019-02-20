#ifndef APP_H
#define APP_H

#include "SDL.h"
#include <vector>

class State;

class App {
public:
    App();
    ~App();

    int init(const char* title, int width = 1920, int height = 1080, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
    int cleanup();

    int changeState(State* state);
    int pushState(State* state);
    int popState();

    int handleEvents();
    int update();
    int draw();

    bool isRunning() { return running; };
    void quit() { running = false; };
private:
    std::vector<State*> states;

    bool running;

    SDL_Window *window;
};

#endif
