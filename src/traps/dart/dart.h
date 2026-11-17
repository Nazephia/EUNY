#pragma once

#include "../trap.h"
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

class Dart : public Trap {
    GDCLASS(Dart, Trap);

protected:
    static void _bind_methods();

    godot::Area2D *kill_area;
    godot::Vector2 direction;
    double speed;
    double lifetime;
    double elapsed_time;

public:
    Dart();
    ~Dart();

    void _ready() override;
    void _process(double delta) override;

    void trigger_effect() override;
    void reset_trap() override;

    void _on_body_entered(Node2D *body);

    void set_direction(godot::Vector2 dir);
    godot::Vector2 get_direction() const;

    void set_speed(double spd);
    double get_speed() const;
};