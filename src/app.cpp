#include "app.h"
#include "state.h"

app::app() {
}

app::~app() {
    Cleanup();
}

int app::init(const char* title, int width = 1920, int height = 1080, Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN) {
    SDL_Init(SDL_INIT_VIDEO);

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

    if(window == NULL) {
        std::cout << "Error creating window: " << SDL_GetError() << endl;
        return 1;
    }

    return 0;
}

int app::cleanup() {
    SDL_DestroyWindow(window);

    if(window != NULL) {
        std::cout << "Error deleting window: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Quit;
    return 0;
}

int app::changeState(State* state) {
    if(!states.empty()) {
        if(states.back()->cleanup()) {
            return 1;
        }
        states.pop_back();
    }

    states.pushBack(state);
    return states.back->init();
}

int app:pushState(State* state) {
    if(!states.empty()) {
        if(states.back()->pause()) {
            return 1;
        }
    }

    states.pushBack(state);
    return states.back->init();
}

int app::popStack() {
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

int app::handleEvents() {
  return states.back()->handleEvents(this);
}

int app::update() {
  return states.back()->update(this);
}

int app::draw() {
  return states.back()->draw(this);
}
