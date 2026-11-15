#pragma once
#include <unordered_map>
#include <string>
#include "state.h"

class Character;

class StateMachine {
private:
    std::unordered_map<std::string, State*> states;
    State *current_state;
    Character *character;

public:
    StateMachine(Character *p_character);
    ~StateMachine();

    void add_state(const std::string &name, State *state);
    void change_state(const std::string &name);
    
    void update(double delta);
    void physics_update(double delta);
};