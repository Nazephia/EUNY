#pragma once
#include "../characters/character.h"

class State {
public:
    virtual ~State() {}

    virtual void enter(Character *character) = 0;
    virtual void exit(Character *character) = 0;
    virtual void update(Character *character, double delta) = 0;
    virtual void physics_update(Character *character, double delta) = 0;
};
