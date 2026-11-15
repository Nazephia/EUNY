#include "state_machine.h"

StateMachine::StateMachine(Character *p_character) : character(p_character), current_state(nullptr) {}

StateMachine::~StateMachine() {
    for (auto &pair : states) {
        delete pair.second;
    }
    states.clear();
}

void StateMachine::add_state(const std::string &name, State *state) {
    states[name] = state;
}

void StateMachine::change_state(const std::string &name) {
    if (states.find(name) == states.end()) return;

    if (current_state) {
        current_state->exit(character);
    }

    current_state = states[name];
    current_state->enter(character);
}

void StateMachine::update(double delta) {
    if (current_state) {
        current_state->update(character, delta);
    }
}

void StateMachine::physics_update(double delta) {
    if (current_state) {
        current_state->physics_update(character, delta);
    }
}