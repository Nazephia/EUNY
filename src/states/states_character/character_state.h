#pragma once

#include "../state.h"
#include "../state_machine.h"
#include "../../characters/character.h"
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/core/math.hpp>



class CharacterMovementState : public State {
protected:
    static double get_direction() {
        godot::Input *input = godot::Input::get_singleton();
        double direction = 0.0;
        if (input->is_action_pressed("ui_right")) direction += 1.0;
        if (input->is_action_pressed("ui_left")) direction -= 1.0;
        return direction;
    }

    static void update_horizontal_velocity(Character *character, double delta) {
        godot::Vector2 velocity = character->get_velocity();
        double direction = get_direction();
        if (direction != 0.0) {
            velocity.x = direction * character->get_speed();
            if (character->get_animated_sprite()) {
                character->get_animated_sprite()->set_flip_h(direction < 0.0);
            }
        } else {
            velocity.x = godot::Math::move_toward(
                    static_cast<double>(velocity.x), 0.0, character->get_speed() * 8.0 * delta);
        }
        character->set_velocity(velocity);
    }

    static bool try_jump(Character *character) {
        godot::Input *input = godot::Input::get_singleton();
        if (!input->is_action_just_pressed("ui_accept") || !character->is_on_floor()) {
            return false;
        }

        godot::Vector2 velocity = character->get_velocity();
        velocity.y = character->get_jump_velocity();
        character->set_velocity(velocity);
        character->get_state_machine()->change_state("jump");
        return true;
    }

public:
    void exit(Character *character) override {}

    void physics_update(Character *character, double delta) override {
        update_horizontal_velocity(character, delta);
    }
};


