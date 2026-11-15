#pragma once
#include "character_state.h"

class WalkState : public CharacterMovementState {
public:
    void enter(Character *character) override {
        if (character->get_animated_sprite()) {
            character->get_animated_sprite()->play("Walk");
        }
    }

    void update(Character *character, double delta) override {
        if (try_jump(character)) {
            return;
        }
        if (get_direction() == 0.0) {
            character->get_state_machine()->change_state("idle");
        }
    }
};