#pragma once
#include "character_state.h"

class JumpState : public CharacterMovementState {
public:
    void enter(Character *character) override {}

    void update(Character *character, double delta) override {
        if (character->is_on_floor()) {
            const char *next_state = get_direction() == 0.0 ? "idle" : "walk";
            character->get_state_machine()->change_state(next_state);
        }
    }
};