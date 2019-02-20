#include <iostream>

#include "app.h"
#include "state.h"

App::App() {
}

App::~App() {
    cleanup();
}

int App::init(const char* title, int width, int height, Uint32 flags) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

    if(window == NULL) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        return 1;
    }

    return 0;
}

int App::cleanup() {
    SDL_DestroyWindow(window);

    if(window != NULL) {
        std::cout << "Error deleting window: " << SDL_GetError() << std::endl;
        return 1;
    }

    SDL_Quit;
    return 0;
}

int App::changeState(State* state) {
    if(!states.empty()) {
        if(states.back()->cleanup()) {
            return 1;
        }
        states.pop_back();
    }

    states.push_back(state);
    return states.back()->init();
}

int App::pushState(State* state) {
    if(!states.empty()) {
        if(states.back()->pause()) {
            return 1;
        }
    }

    states.push_back(state);
    return states.back()->init();
}

int App::popState() {
    if(!states.empty()) {
        if(states.back()->cleanup()) {
            return 1;
        }
        states.pop_back();
    }

    if(!states.empty()) {
        if(states.back()->resume()) {
            return 1;
        }
    }

    return 0;
}

int App::handleEvents() {
  return states.back()->handleEvents(this);
}

int App::update() {
  return states.back()->update(this);
}

int App::draw() {
  return states.back()->draw(this);
}
