#ifndef STATE_H
#define STATE_H

#include "app.h"
#include "view.h"

class State {
  public:
    virtual int init(App* game) = 0;
    virtual int cleanup() = 0;

    virtual int pause() = 0;
    virtual int resume() = 0;

    virtual int handleEvents(App* game) = 0;
    virtual int update(App* game) = 0;
    virtual int draw(Uint32 timeBetweenFrames) = 0;

    int changeState(App* game, State* state) {
      return game->changeState(state);
    }

  protected:
    State() { }
    View view;
    std::stringstream strStream;
};

#endif
