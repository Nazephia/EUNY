#pragma once

#include "../trap.h"
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>


class ProximityTrap : public Trap {
    GDCLASS(ProximityTrap, Trap);

protected:
    static void _bind_methods();
    godot::Area2D *detection_area;
    double activation_delay;

public:
    ProximityTrap();
    ~ProximityTrap();

    void _ready() override;

    // Callback de la señal de proximidad
    void _on_body_entered(godot::Node2D *body);

    void trigger_effect() override;
    void reset_trap() override;

    void set_activation_delay(double p_delay);
    double get_activation_delay() const;
};
