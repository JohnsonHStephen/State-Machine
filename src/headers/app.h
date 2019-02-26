#ifndef APP_H
#define APP_H

#include "SDL.h"
#include <vector>
#include <sstream>

#include "view.h"

class State;

class App {
  public:
    App();
    App(const char* title);
    App(const char* title, int width, int height, Uint32 flags);
    ~App();

    int init(const char* title, int width = 600, int height = 400, Uint32 flags = SDL_WINDOW_SHOWN);
    int cleanup();

    int changeState(State* state);
    int pushState(State* state);
    int popState();

    int handleEvents();
    int update();
    int draw(Uint32 timeBetweenFrames);

    bool isRunning() { return running; };
    void quit() { running = false; };
    SDL_Window* getWindow() { return window; }
  private:
    View view;
    std::stringstream strStream;

    std::vector<State*> states;

    bool running;

    SDL_Window *window;
};

#endif
