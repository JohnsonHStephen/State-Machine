#include <string>

#include "app.h"
#include "state.h"

App::App() {
  init("No Title");
}

App::App(const char* title) {
  init(title);
}

App::App(const char* title, int width, int height, Uint32 flags) {
  init(title, width, height, flags);
}

App::~App() {
  cleanup();
}

int App::init(const char* title, int width, int height, Uint32 flags) {
  SDL_Init(SDL_INIT_EVERYTHING);

  window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

  if(window == NULL) {
    strStream << "Error creating window: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

    return 1;
  }

  running = true;

  return 0;
}

int App::cleanup() {
  while(!states.empty()) {
    popState();
  }

  SDL_DestroyWindow(window);

  if(window == NULL) {
    strStream << "Error deleting window: " << SDL_GetError();
    view.printToFile(strStream.str());
    strStream.str(std::string());

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
  return states.back()->init(this);
}

int App::pushState(State* state) {
  if(!states.empty()) {
    if(states.back()->pause()) {
      return 1;
    }
  }

  states.push_back(state);
  return states.back()->init(this);
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
  // strStream << "In event handling";
  // view.printToFile(strStream.str());
  // strStream.str(std::string());

  if(states.empty()) {
    return 1;
  }

  return states.back()->handleEvents(this);
}

int App::update() {
  // strStream << "In updating";
  // view.printToFile(strStream.str());
  // strStream.str(std::string());

  if(states.empty()) {
    return 1;
  }

  return states.back()->update(this);
}

int App::draw(Uint32 timeBetweenFrames) {
  // strStream << "In drawing";
  // view.printToFile(strStream.str());
  // strStream.str(std::string());

  if(states.empty()) {
    return 1;
  }

  return states.back()->draw(timeBetweenFrames);
}
