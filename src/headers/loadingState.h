#ifndef LOADINGSTATE_H
#define LOADINGSTATE_H

#include "SDL.h"

#include "state.h"

class LoadingState : public State {
  public:
    int init(App* game);
    int cleanup();

    int pause();
    int resume();

    int handleEvents(App* game);
    int update(App* game);
    int draw(Uint32 timeBetweenFrames);

    static LoadingState* Instance() {
      return &instance;
    }

  protected:
    LoadingState() { }

  private:
    static LoadingState instance;

    SDL_Renderer *renderer = NULL;
    SDL_Texture* playButtonTexture = NULL;
    SDL_Texture* playButtonPressedTexture = NULL;

    bool clickingPlay = false;
};


#endif
