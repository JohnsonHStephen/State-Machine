#include <sstream>
#include <string>

#include "app.h"
#include "view.h"

#define TICK_RATE (100./6.)

int main(int argc, char *argv[]) {
  App app;

  View view;
  view.createFile();
  std::stringstream strStream;

  Uint32 lastTime = 0, currentTime;
  lastTime = SDL_GetTicks();
  while(app.isRunning()) {
    currentTime = SDL_GetTicks();

    while(currentTime - lastTime < TICK_RATE) {
      app.handleEvents();
      app.draw(currentTime - lastTime);
      currentTime = SDL_GetTicks();
    }
    currentTime = SDL_GetTicks();
    app.update();
    lastTime = currentTime;
  }

  app.cleanup();

  return 0;
}
