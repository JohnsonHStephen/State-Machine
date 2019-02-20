#ifndef STATE_H
#define STATE_H

#include "app.h"

class State {
public:
    virtual int init() = 0;
    virtual int cleanup() = 0;

    virtual int pause() = 0;
    virtual int resume() = 0;

    virtual int handleEvents(App* game) = 0;
    virtual int update(App* game) = 0;
    virtual int draw(App* game) = 0;

    int changeState(App* game, State* state) {
        return game->changeState(state);
    }

protected: State() { }
};

#endif
