#pragma once
#include "character_state.h"

class IdleState : public CharacterMovementState {
public:
    void enter(Character *character) override {
        if (character->get_animated_sprite()) {
            character->get_animated_sprite()->play("Idle");
        }
    }

    void update(Character *character, double delta) override {
        if (try_jump(character)) {
            return;
        }
        if (get_direction() != 0.0) {
            character->get_state_machine()->change_state("walk");
        }
    }
};