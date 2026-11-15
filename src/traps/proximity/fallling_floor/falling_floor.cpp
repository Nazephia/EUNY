#include "falling_floor.h"

FallingFloor::FallingFloor() {
    is_falling = false;
    vertical_velocity = 0.0;
    set_process(true);
}

void FallingFloor::_ready(){
    ProximityTrap::_ready();
    initial_position = get_position();
}

FallingFloor::~FallingFloor() {}

void FallingFloor::_bind_methods() {}

void FallingFloor::trigger_effect() {
    if (!is_falling) {
        is_falling = true;
        godot::UtilityFunctions::print("¡Suelo falso pisado!");
    }
}

void FallingFloor::_process(double delta) {
    if (is_falling) {
        vertical_velocity += 980.0 * delta; // Gravedad simulada
        godot::Vector2 current_pos = get_position();
        current_pos.y += vertical_velocity * delta;
        set_position(current_pos);
    }
}

void FallingFloor::reset_trap() {
    ProximityTrap::reset_trap();
    is_falling = false;
    vertical_velocity = 0.0;
    set_position(initial_position);
}