#pragma once

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/core/class_db.hpp>

class DeathZone : public godot::Area2D {
    GDCLASS(DeathZone, Area2D);

protected:
    static void _bind_methods();

public:
    DeathZone();
    ~DeathZone();

    void _ready() override;
    void _on_body_entered(Node2D *body);
};