#pragma once

#include "../proximity_trap.h"

class FallingFloor : public ProximityTrap {
    GDCLASS(FallingFloor, ProximityTrap);

protected:
    static void _bind_methods();

    bool is_falling;
    double vertical_velocity;
    godot::Vector2 initial_position;

public:
    FallingFloor();
    ~FallingFloor();

    void _process(double delta) override;
    void trigger_effect() override;
    void reset_trap() override;
    void _ready() override;
};